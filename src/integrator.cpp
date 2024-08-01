/*
Implementation of Radau IIA collocation schemes. Contains schemes for s = 1,2,...,7 steps
with corresponding orders 2s-1. The coefficients are calculated to 53 exact decimal places via
https://github.com/linuslangenkamp/ConstructionRadauIIA. The theoretical values
a_{s,s} = 1/s^2 and ainv_{s,s} = 1/2 (1 + s^2) hold.
*/

#include "integrator.h"
#include "util.h"

Integrator::Integrator(const std::vector<double>& c,
                       const std::vector<std::vector<double>>& A,
                       const std::vector<std::vector<double>>& Ainv,
                       const std::vector<double>& invRowSum,
                       int steps)
        : c(c), A(A), Ainv(Ainv), b(A.back()), invRowSum(invRowSum), steps(steps),  c0([&c]() {
        std::vector<double> temp(1, 0.0);
        temp.insert(temp.end(), c.begin(), c.end());
        return temp;
        }()),
          interpolationFirstLagrangeBasis(interpolationFirstBasisPolynomial()), interpolationLagrangeBasis(interpolationBasisPolynomial()),
          lagrangeBasisDiff(basisPolynomialDiff()), lagrangeBasisDiff2(basisPolynomialDiff2()){
}

Integrator Integrator::radauIIA(IntegratorSteps steps) {

    switch (steps) {
        case IntegratorSteps::Steps1:
            return {{1.0},
                    {{1.0}},
                    {{1.0}},
                    {1.0},
                    1};

        case IntegratorSteps::Steps2:
            return {{0.33333333333333333333333333333333333333333333333333333,
                     1.0},
                    {{0.41666666666666666666666666666666666666666666666666667,
                      -0.083333333333333333333333333333333333333333333333333333},
                     {0.75,
                      0.25}},
                    {{1.5,
                      0.5},
                     {-4.5,
                      2.5}},
                    {2.0,
                     -2.0},
                    2};

        case IntegratorSteps::Steps3:
            return {{0.15505102572168219018027159252941086080340525193433299,
                     0.64494897427831780981972840747058913919659474806566701,
                     1.0},
                    {{0.19681547722366042586838614299182988960066213232056475,
                      -0.065535425850198388108522782569608691801247291239431807,
                      0.023770974348220152420408232107189663003990410853200046},
                     {0.3944243147390872769974116714584975806901361801283207,
                      0.29207341166522846302050274589705899928822675656832414,
                      -0.041548752125997930198186009884967440781768188630977824},
                     {0.37640306270046727505007544236928079466761256998175916,
                      0.51248582618842161383881344651960809422127631890712973,
                      0.11111111111111111111111111111111111111111111111111111}},
                    {{3.2247448713915890490986420373529456959829737403283351,
                      1.1678400846904054949240412722156950122337492313014478,
                      -0.2531972647421808261859424199215710378575859948417787},
                     {-3.5678400846904054949240412722156950122337492313014478,
                      0.77525512860841095090135796264705430401702625967166494,
                      1.0531972647421808261859424199215710378575859948417787},
                     {5.531972647421808261859424199215710378575859948417787,
                      -7.531972647421808261859424199215710378575859948417787,
                      5.0}},
                    {4.1393876913398137178367408896470696703591369767880042,
                     -1.7393876913398137178367408896470696703591369767880042,
                     3.0},
                    3};

        case IntegratorSteps::Steps4:
            return {{0.088587959512703947395546143769456196885729331922749565,
                     0.40946686444073471086492625206882989405190489528056231,
                     0.78765946176084705602524188987599962334808005851097384,
                     1.0},
                    {{0.11299947932315618599385005301138850067913740568412958,
                      -0.040309220723522205735549888393159894934301463237376109,
                      0.025802377420336391035940091595814208628665823985676253,
                      -0.0099046765072664238986941124445866174877724345096801584},
                     {0.23438399574740025657366167396747336651267721676706014,
                      0.20689257393535890010464509882215952378815196012225114,
                      -0.047857128048540718850008491142788494911184024427801351,
                      0.016047422806516273036627970421985498662259742819052381},
                     {0.21668178462325034184405249707184429789299458455904694,
                      0.40612326386737331122519857754221593372076885360703844,
                      0.18903651817005634247293341959502340410413920562219071,
                      -0.024182104899832939516942604333084012369822585277302252},
                     {0.22046221117676837527547847203718598905291672812308731,
                      0.38819346884317188078023230689001717919805986428946713,
                      0.32884431998005974394428922107279683174902340758744555,
                      0.0625}},
                    {{5.644107875950089475185873124339281335672433066622399,
                      1.9235072770547126769093816468912122910567322657618139,
                      -0.58590148210381629237279924720338790191192823257954322,
                      0.173878352574245724838471938326822229815036247290691},
                     {-5.0492146383914088704391618182421498718004811125604763,
                      1.2211000288946917859217661231785599879578385259371315,
                      1.7546809887608367951746006753330255576106533072682203,
                      -0.43479146121258140124098537962014610273705185547935655},
                     {3.4924661586254374098092524962991231135553949939080352,
                      -3.9845178957824964129588247734859864538164936707776417,
                      0.63479209515521873889236075248215867636972840744046948,
                      1.8221375984342540437494522168035279545546686694131553},
                     {-6.9234882564454545085379164050904687434608362466030704,
                      6.5952376696281438984433544702783024129703695528704059,
                      -12.171749413182689389905438065187833669509533306267336,
                      8.5}},
                    {7.1555920234752315845609274623539279546322733470953607,
                     -2.5082250819484616905837803993507104289690411348344811,
                     1.9648779564324137794922406920988232906632983999840183,
                     -4.0},
                    4};

        case IntegratorSteps::Steps5:
            return {{0.057104196114517682193121192554115621235077945598750164,
                     0.27684301363812382768004599768562514111088916969503047,
                     0.58359043236891682005669766866291724869343263989677164,
                     0.8602401356562194478479129188751197667383780225872255,
                     1.0},
                    {{0.072998864317903324305568533778137426004163039777915462,
                      -0.026735331107945571877697965352751601211787338539051682,
                      0.018676929763984354412247354802088259852773575327219285,
                      -0.012879106093306439853646949838298551565502926670061495,
                      0.0050428392338820152066502191649400881554315957027285942},
                     {0.1537752314791824686681235708817509749471679470925086,
                      0.14621486784749350664968724512404244842221927972758767,
                      -0.036444568905128089526650202198483305919654211399984219,
                      0.021233063119304719421507662919772852230792907023363807,
                      -0.0079355799027287775326222790414578285696367527484453929},
                     {0.14006304568480987151375573681448726712481337595319959,
                      0.29896712949128347939830345517875687328015051590253048,
                      0.1675850701352489634420614091615786059678990371149808,
                      -0.033969101686617746571922141643423777169061257085196568,
                      0.010944288744192252274499209151518279489630968011257334},
                     {0.14489430810953475753660064709320210901047840637513627,
                      0.27650006876015922755593438832926660305873502019195033,
                      0.32579792291042102998492897281091929529418345389727753,
                      0.12875675325490976115823836749179707516127419893507162,
                      -0.015708917378805328387789456850065315786293056812210251},
                     {0.14371356079122594132341221985411022715892296173188092,
                      0.28135601514946206019217265034065989120000299266737412,
                      0.31182652297574125408185491157664052198806076863409074,
                      0.22310390108357074440256021822858935965301327696665422,
                      0.04}},
                    {{8.7559239779383616676316605948280129286294559510094293,
                      2.8919426153801174043574566762273863428433494645241648,
                      -0.87518639620026502641628259863084315801220143590404407,
                      0.39970520793996548262165669488093419847690646338941591,
                      -0.13370616384921583567170203247263043089510538175514382},
                     {-7.1613807201453870273924702520815443894890064069403878,
                      1.8060777240836443635298784400424424075067329356074042,
                      2.3637971760686083694221034157998740208395673245106841,
                      -0.86590078028313451913953460046404766819935085988433146,
                      0.27433807777519420217376681143726552604467955996295104},
                     {4.1221652462433737810440351521134408860546612735013581,
                      -4.4960171258133947198488371212252391107080076134884667,
                      0.85676524539717760508619340926917996198812400730817318,
                      2.5183209492110643749371350228669372592745431546235781,
                      -0.65706275713436010625523042356520856731380128981001713},
                     {-3.8786632197240103336352796096359369350009482678789439,
                      3.3931519180649541686929538961408237817301698138719797,
                      -5.1883409064071868791971204894348579301416445015458572,
                      0.58123305258081636375226755586036470187568710607499334,
                      2.8099836552797123296022740122274596175688910347846516},
                     {8.4124242235942886564071743291339200507160318683094498,
                      -6.9702561166566609670322722579966004226790792261914369,
                      8.7771142041504732392140266302693783625882386155582994,
                      -18.219282311088100928588928701406697990625191257676312,
                      13.0}},
                    {11.038679241208963692522789334832859881042405061263822,
                     -3.5830685225010746114062561852660101032973774467436799,
                     2.3441715579038609349632960394591104292955195321346255,
                     -2.2826355002057143507849046348421467639678448146931765,
                     5.0},
                    5};

        case IntegratorSteps::Steps6:
            return {{0.039809857051468742340806690093333167704262654228385162,
                     0.19801341787360817253579213679529623603818635883378888,
                     0.43797481024738614400501252000522885251679027421474013,
                     0.69546427335363609451461482372116716139400155499864836,
                     0.9014649142011735738765011021122473096194864304517102,
                     1.0},
                    {{0.050950010994640609251478059633024629369673958557677095,
                      -0.01890730655429213909330279381391824985374130772961073,
                      0.013686071433088228819012995720112285258120537385948149,
                      -0.010370038766046045839009537968545118512361729041913256,
                      0.0073606563966398039365575429778365553030154189796668449,
                      -0.0029095364525617147339295764551769338604442239233829409},
                     {0.10822165891905866038457804818157049157131605614756006,
                      0.1069755199373326038028487086967073418899396739945163,
                      -0.02753902335539242032882486237869312367300372479006481,
                      0.017496747141228161531087490197110541281123440201632982,
                      -0.011653721891195586803761017683165506213203011975440927,
                      0.0045122371225767539498637697817664911820139252555852759},
                     {0.097779670092645354659821461618397355292240570325780052,
                      0.22317225063689583566719958767108380482274346965384028,
                      0.13631467927305188653151585886467910012672516478677295,
                      -0.029646965988196216350882814027078247408353061629894783,
                      0.016358578843437159707327494725790347334132545244331019,
                      -0.0060034026104478762099690688476435076506984141660893962},
                     {0.10212237561293384100253249087632606054417775295883935,
                      0.20297595737309107918373442944059116349390035078791908,
                      0.27639913638074783302191977602414971750729661532819317,
                      0.13100602313604298035265996255951640534967825807269894,
                      -0.024876303199822286536339815419573239269286280557463102,
                      0.0078370840506426474901079802401570537682348584084609123},
                     {0.10033100138496080156934198475643763175703379375978034,
                      0.21024730855333846180365503705179494054249856988659109,
                      0.25608537205033761639808891688573084503296586073935844,
                      0.25336593470456565097236321199032658663712429116967294,
                      0.092430534335699596829174177922840200031659712265102393,
                      -0.010995236827728553696122226494882894381795797368795005},
                     {0.10079419262674042010460037787456778185867395449789905,
                      0.20845066715595386947970319137132312166770750468809401,
                      0.26046339159478749128511470328476850990576171084535868,
                      0.24269359423448495807991395779344483399396758406210209,
                      0.15982037661025548327288999189811797479611146812876839,
                      0.027777777777777777777777777777777777777777777777777778}},
                    {{12.559703476291508856759225323318919640126066983227192,
                      4.0758259888762954817494547350310031084559828136333489,
                      -1.2172038084642605067756078471975154474206452337894571,
                      0.56623186694414246978895797080943530510368604261548696,
                      -0.30710421225684079606678497609961579490782742404808152,
                      0.10908601078800727722498517452926118161961723801904724},
                     {-9.802838712568015725430576296432169103898720439175253,
                      2.5250814079637252342587724377988110897880930503688667,
                      3.1322258626473415014042153373119208621803921946250046,
                      -1.15740999277438078512889218677646560344542555490633,
                      0.58338219245411039183172756459011968403064216982877826,
                      -0.20254769846905339924617680916382095594946547313636292},
                     {5.1821578385587184440708706750085706358225125762139946,
                      -5.5445229095274380714672964262288208670165126604878414,
                      1.1416181668474940003456533020510892139965016163086566,
                      2.9749762538212511590574537403794484610221624813709364,
                      -1.1780193270588294076914652845195970848553247005300839,
                      0.38454236200917257054424072994860409015756384565849774},
                     {-4.1082390934588070618728720380988041801704871600155788,
                      3.4915029091138618093779521480414734084304675779622959,
                      -5.0698787509936073376174817968996188766316071992611356,
                      0.7189441918977704032300544771680751155747395353105827,
                      3.4600417960862668741334283116160765543103522914038251,
                      -0.92644311040313188933928587402238278891840767180972239},
                     {4.3857850634009341783689495573834079048320364882380611,
                      -3.4640050474514886335832004466308863737534057478240779,
                      3.9515424565876116401460504195060788809893581478921864,
                      -6.810539438891445229513105959783181559137332039744986,
                      0.55465275699950150540629445966310494051459881478470182,
                      4.0171328069513117040496224764065831285104038295903763},
                     {-9.9429774219288117999498665906756735228996958761164766,
                      7.6760621572330476372635031261993167796467900371892296,
                      -8.2327371282184064914111138450625431732021683135542693,
                      11.638707277368019864812077128557949247047967186213534,
                      -25.639054884453849210714599819019049330592893033732018,
                      18.5}},
                    {15.786539322178852782680230380391487992976880419657537,
                     -4.9221069407462727823109299526716040272944840523952964,
                     2.96075238465036869485945673663929444912690315853416,
                     -2.4340720577576472020882047721951807674049426264097331,
                     2.6345685975964251648746105065451069219556594929362616,
                     -6.0},
                    6};

        case IntegratorSteps::Steps7:
            return {{0.029316427159784891972050276913164910373730392563714928,
                     0.14807859966848429184997685249597921223024877480859446,
                     0.33698469028115429909705297208077570519756875002847335,
                     0.55867151877155013208139334180552194007436828896540783,
                     0.76923386203005450091688336011564545183714214332229542,
                     0.92694567131974111485187396581968201105617241954228325,
                     1.0},
                    {{0.037546264993921331333686127624105551409844147085068844,
                      -0.014039334556460401537626568603936253927078900617187738,
                      0.010352789600742300936755479003273124789107137783342182,
                      -0.0081583225402750119092045435772132783491910230755902428,
                      0.0063884138795346849437559514864056804089198993395115866,
                      -0.0046023267791486554993520258547685217738229482397358601,
                      0.0018289425614706437040358568352986078159520802883061566},
                     {0.080147596515618967795215595316188773478794694453718857,
                      0.081062063985891536679584719357221980974798332396676237,
                      -0.021237992120711034937085469604419103836950630324491706,
                      0.014000291238817118983742204835134926788498535743388827,
                      -0.010234185730090163829199816607636044633616515605306449,
                      0.007153465151364590498062382166962141175250761062293536,
                      -0.0028126393724067233403427629674734617165264029176848412},
                     {0.07206384694188190211336252656113759677969535477532081,
                      0.17106835498388661942435250400905030280034964311372014,
                      0.10961456404007210923322040746184569082289243085783282,
                      -0.024619871728984053862318864441100561088846246683740384,
                      0.014760377043950817073195348981742706482163192669641625,
                      -0.0095752593967914005563287247266417134307882145349237161,
                      0.0036726783971383056715697742347416828321025898306220496},
                     {0.07570512581982442042464122949633892196989112138481471,
                      0.15409015514217114464633168204648291517195590999535673,
                      0.2271077366732023864112812879493663500980933111865218,
                      0.11747818703702478198791268067393216144249387082062452,
                      -0.023810827153044173582047929325774334375960893931640326,
                      0.012709985533661205633610757619788395064712864489453302,
                      -0.0046088442812896334403363666546124692968178949797229061},
                     {0.073912342163191846540806321243016399213366859606730632,
                      0.16135560761594243218622014590309481037382829152280328,
                      0.20686724155210419781957884643767073090996149315046441,
                      0.23700711534269423476224677295732751474653439325044346,
                      0.10308679353381344662410584574572164064619759515728231,
                      -0.018854139152580448840052190417863035124650910366617283,
                      0.0058589009748887918239776182466773910719044210011886013},
                     {0.074705562059796230172292559361766628755621292318113064,
                      0.15830722387246870065847938451462871657405874299230082,
                      0.21415342326720003110869745785686139661908996932591373,
                      0.21987784703186003998748735549076677110629790633147806,
                      0.1987521216806352698018264691845345047604737396975395,
                      0.069265501605509133230972165761976742364684141735890462,
                      -0.0081160081977282901078814263508527491240533728589523822},
                     {0.074494235556010317933248780209166920975326449423939424,
                      0.15910211573365074087243521723493418210816301632787095,
                      0.21235188950297780419915401957510412235603856069467639,
                      0.22355491450728323474967447682122101798551083778481214,
                      0.19047493682211557690296917393806276186714739147125247,
                      0.11961374461265620289353874038477630083026272388928535,
                      0.020408163265306122448979591836734693877551020408163265}},
                    {{17.05528430442165547204579642034083780888205214325746,
                      5.475299512185491994676800899743790661694096123625029,
                      -1.6185811051907870418899553007451353388271347374659842,
                      0.74965412823850668850491844742883582038955113973561324,
                      -0.42189137598301601657201429347890055079720112051254486,
                      0.25105021424639275958421508258089146987272419318329378,
                      -0.092324819353684120483745385055840934611110670217170266},
                     {-12.948988698811522838417544038234250134109206460643835,
                      3.3765851454524219949642189304290401504829598822571352,
                      4.0540135039255858096372954903548449368706589108170772,
                      -1.4863139760065445882329543471186873554627224575114947,
                      0.77285447377889712203592563914347622257886147402734922,
                      -0.44494694720106998080918994469810679432968261199877167,
                      0.16177470033538139708000483891161673219516479615364295},
                     {6.526797433701593265807091002677945510912942632119839,
                      -6.9123049254818286208625019958749232412140981143299303,
                      1.4837469310040114035333882918594762758689645536432831,
                      3.5946033544558913525948024579087116471046062762826014,
                      -1.4502156012225290720704503172900510191032479607216679,
                      0.76703844918135737734695440443835594705472124480929198,
                      -0.27142848561987243331733726208810377318882687511385898},
                     {-4.760415643167770722198704938659524225422839716575759,
                      3.9908603180959220483520785478925699593287423065066363,
                      -5.6606883336578349990157348154290945210884134799171998,
                      0.89498029378594137694918736471055816628551012397764606,
                      3.7358993915001522189560233616953434967286748794491962,
                      -1.5419785025493503741138694073293970924266006322890017,
                      0.51171265709971559630608267601898576641190078356699465},
                     {4.3294510166386911992045676853881052735979315578101732,
                      -3.3535280016779187466093442341122706449601156094285698,
                      3.6906179318627216466058448517411724962533713381312738,
                      -6.0373091872657883034087805835175670069758435130884262,
                      0.64999738659511150452787195865729196787050793370250812,
                      4.5773009414145603763362186836666257585549835924946567,
                      -1.2440566466772534062303354271343926998077724212343848},
                     {-4.9436238335075610107028853287883198617437547439125381,
                      3.7048026760270510564173063237046792148437285810782569,
                      -3.7457284313738156326396742436169456788459196400906784,
                      4.7816656257626148804236647526944901821873165710711102,
                      -8.7833887559250444565719593995150273548072814730043042,
                      0.53940593874085824797953703400279563061000536316196769,
                      5.4436801880591441407021829888061655578658018476396449},
                     {11.495455205116665280685125422978974749301958391963172,
                      -8.5170724230566246267841241250747749244347087224848887,
                      8.3810313019648246041827000766142290589383021290242083,
                      -10.033441651950400990948927924890487427656361455462868,
                      15.094393942991166540634498819845945045313276722359653,
                      -34.420366375065630807769272269473886501462467065399276,
                      25.0}},
                    {21.398490858564559735866015870814478936602977071605697,
                     -6.5150217985268510837422434312120662417739664668988965,
                     3.7382371560186232730319465816314113474350617566895583,
                     -2.8296298188932248547649372111005584501830257352814873,
                     2.612473440890124270426042934688965144533062878387231,
                     -3.0031865922167527743918278727121623098901034940565411,
                     7.0},
                    7};
    }
}

// First and second derivative of the Lagrange interpolating polynomial on the nominal interval [0, 1]
// Will be used for detecting discontinuities, corners, sections that are steep or have a huge curvature
// use this for every interval, but the 0-th control interval

double Integrator::integrate(std::vector<double>& f) {
    // input: vector of f(c_j) excluding c_0 = 0
    // integrates according to Radau scheme
    double integral = 0;
    for (int j = 0; j < sz(b); j++) {
        integral += b[j] * f[j];
    }
    return integral;
}

std::vector<std::vector<double>> Integrator::basisPolynomialDiff() {
    // returns vector of the lagrange basis coeffs diff for all grid points 0, c_1, ...
    // i.e. w_j(c_i) where c_i are the collocation points including 0
    std::vector<std::vector<double>> lagr;
    for (int i = 0; i < sz(c0); i++){
        std::vector<double> lagrC = {};
        for (int j = 0; j < steps + 1; j++) {
            double sum = 0;
            for (int d = 0; d < sz(c0); d++) {
                if (d != j) {
                    double factor = 1;
                    for (int m = 0; m < sz(c0); m++) {
                        if (m != d && m != j) {
                            factor *= (c0[i] - c0[m]);
                        }
                    }
                    sum += factor;
                }
            }
            double factor = 1;
            for (int m = 0; m < sz(c0); m++) {
                if (m != j) {
                    factor *= (c0[j] - c0[m]);
                }
            }
            sum /= factor;
            lagrC.push_back(sum);
        }
        lagr.push_back(lagrC);
    }
    return lagr;
}

std::vector<double> Integrator::evalLagrangeDiff(std::vector<double>& coefficients) {
    // evaluates the diff of the lagrange polynomial of given coefficients at c0 = 0, c1, c2, ...
    std::vector<double> lagrangeDiff;
    for (int i = 0; i < sz(lagrangeBasisDiff); i++) {
        double diffC = 0;
        for (int j = 0; j < sz(coefficients); j++) {
            diffC += lagrangeBasisDiff[i][j] * coefficients[j];
        }
        lagrangeDiff.push_back(diffC);
    }
    return lagrangeDiff;
}

std::vector<std::vector<double>> Integrator::basisPolynomialDiff2() {
    // returns vector of the lagrange basis coeffs 2nd diff for all grid points 0, c_1, ...
    // i.e. w_j(c_i) where c_i are the collocation points including 0
    std::vector<std::vector<double>> lagr;
    for (int i = 0; i < sz(c0); i++){
        std::vector<double> lagrC = {};
        for (int j = 0; j < steps + 1; j++) {
            double sum = 0;
            for (int d = 0; d < steps + 1; d++) {
                if (d != j) {
                    for (int l = 0; l < steps + 1; l++) {
                        if (l != j && l != d) {
                            double factor = 1;
                            for (int m = 0; m < steps + 1; m++) {
                                if (m != j && m != d && m != l) {
                                    factor *= (c0[i] - c0[m]);
                                }
                            }
                            sum += factor;
                        }
                    }
                }
            }
            double factor = 1;
            for (int m = 0; m < steps + 1; m++) {
                if (m != j) {
                    factor *= (c0[j] - c0[m]);
                }
            }
            sum /= factor;
            lagrC.push_back(sum);

        }
        lagr.push_back(lagrC);
    }
    return lagr;
}

std::vector<double> Integrator::evalLagrangeDiff2(std::vector<double>& coefficients) {
    // evaluates the 2nd diff of the lagrange polynomial of given coefficients at c0 = 0, c1, c2, ...
    std::vector<double> lagrangeDiff;
    for (int i = 0; i < sz(lagrangeBasisDiff2); i++) {
        double diffC = 0;
        for (int j = 0; j < sz(coefficients); j++) {
            diffC += lagrangeBasisDiff2[i][j] * coefficients[j];
        }
        lagrangeDiff.push_back(diffC);
    }
    return lagrangeDiff;
}

// Interpolation methods for bisection of an interval

// use this for first control interval
std::vector<std::vector<double>> Integrator::interpolationFirstBasisPolynomial() {
    std::vector<double> newGrid;
    for (int k = 0; k < 2; k++) {
        for (int idx = 0; idx < sz(c); idx++) {
            newGrid.push_back(0.5 * (k + c[idx]));
        }
    }

    std::vector<std::vector<double>> lagr;
    for (auto coll : newGrid){
        std::vector<double> lagrC = {};
        for (int k = 0; k < steps; k++) {
            double factor = 1;
            for (int d = 0; d < steps; d++) {
                if (d != k)
                    factor *= (coll - c[d]) / (c[k] - c[d]);
            }
            lagrC.push_back(factor);
        }
        lagr.push_back(lagrC);
    }
    return lagr;
}

// use this for every interval, but the 0-th control interval
std::vector<std::vector<double>> Integrator::interpolationBasisPolynomial() {
    std::vector<double> newGrid;
    for (int k = 0; k < 2; k++) {
        for (int idx = 0; idx < sz(c0); idx++) {
            if (k != 1 || idx != 0)
                newGrid.push_back(0.5 * (k + c0[idx]));
        }
    }

    std::vector<std::vector<double>> lagr;
    for (auto coll : newGrid){
        std::vector<double> lagrC = {};
        for (int k = 0; k < steps + 1; k++) {
            double factor = 1;
            for (int d = 0; d < steps + 1; d++) {
                if (d != k)
                    factor *= (coll - c0[d]) / (c0[k] - c0[d]);
            }
            lagrC.push_back(factor);
        }
        lagr.push_back(lagrC);
    }
    return lagr;
}

// output values at c_0/2, c_1/2, ..., c_m/2 = 1/2, 1/2 + c_0/2, 1/2 + c_1/2, ..., 1
std::vector<double> Integrator::interpolateFirstControl(std::vector<double>& uValues) {
    std::vector<double> vals;
    for (auto coeffs: interpolationFirstLagrangeBasis) {
        double sum = 0;
        for (int k = 0; k < steps; k++) {
            sum += uValues[k] * coeffs[k];
        }
        vals.push_back(sum);
    }
    return vals;
}

// output values at c_0/2, c_1/2, ..., c_m/2 = 1/2, 1/2 + c_0/2, 1/2 + c_1/2, ..., 1
std::vector<double> Integrator::interpolate(std::vector<double>& values) {
    std::vector<double> vals;
    for (int j = 1; j < sz(interpolationLagrangeBasis); j++) {
        double sum = 0;
        for (int k = 0; k < steps + 1; k++) {
            sum += values[k] * interpolationLagrangeBasis[j][k];
        }
        vals.push_back(sum);
    }
    return vals;
}
