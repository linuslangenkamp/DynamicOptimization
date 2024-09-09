import numpy as np

RADAU_C = [[1.0], [0.3333333333333333, 1.0], [0.1550510257216822, 0.6449489742783178, 1.0], [0.08858795951270394, 0.4094668644407347, 0.787659461760847, 1.0], [0.05710419611451768, 0.2768430136381238, 0.5835904323689168, 0.8602401356562195, 1.0], [0.03980985705146874, 0.19801341787360818, 0.43797481024738616, 0.6954642733536361, 0.9014649142011736, 1.0], [0.029316427159784893, 0.1480785996684843, 0.3369846902811543, 0.5586715187715501, 0.7692338620300545, 0.9269456713197411, 1.0], [0.022479386438712497, 0.11467905316090424, 0.26578982278458946, 0.45284637366944464, 0.6473752828868303, 0.8197593082631076, 0.9437374394630779, 1.0], [0.01777991514736345, 0.09132360789979396, 0.21430847939563075, 0.37193216458327233, 0.5451866848034267, 0.7131752428555694, 0.8556337429578544, 0.9553660447100302, 1.0], [0.014412409648876549, 0.07438738970919605, 0.1761166561629953, 0.3096675799276378, 0.46197040108101095, 0.618117234695294, 0.7628230151850396, 0.8819210212100013, 0.9637421871167905, 1.0], [0.011917613432415597, 0.061732071877148124, 0.14711144964307024, 0.26115967600845624, 0.39463984688578685, 0.5367387657156606, 0.6759444616766651, 0.8009789210368988, 0.9017109877901468, 0.9699709678385136, 1.0], [0.010018280461680407, 0.052035451127180554, 0.12461922514444307, 0.22284060704383785, 0.3400081579146652, 0.468137613089584, 0.5984972797671392, 0.722203284890968, 0.8308248996228186, 0.9169583865525949, 0.9747263796024797, 1.0], [0.008539054988427419, 0.04444646315540772, 0.10685449088347666, 0.19215105452985404, 0.29538088426258025, 0.41054508120145766, 0.5309508493128177, 0.649600650277255, 0.759598889525227, 0.8545525437649358, 0.928942101264411, 0.9784379368341496, 1.0], [0.0073646510260893215, 0.03839813873967835, 0.09259522469900264, 0.16725101139155774, 0.2586235407057625, 0.3621313972822388, 0.47258438600411773, 0.5844439640213405, 0.6921010017196016, 0.7901570282734375, 0.8736948213066894, 0.938524459100731, 0.9813896349890121, 1.0], [0.006416760792818457, 0.03350140453201314, 0.08098549968195519, 0.14680486768121373, 0.228084270649258, 0.32127174398893615, 0.42229465730757026, 0.526737861339873, 0.6300366883704039, 0.7276764528892646, 0.8153897394434746, 0.8893428088195156, 0.9463027000602754, 0.9837752340986002, 1.0], [0.00564068897251171, 0.029482298647942485, 0.07141295311515884, 0.12983102555359105, 0.20249275505010406, 0.28660608625752704, 0.37893868864697805, 0.4759423084632349, 0.5738891609066858, 0.6690151950299599, 0.7576647390313427, 0.8364309606056102, 0.902286700679378, 0.9527004099058333, 0.9857305452631743, 1.0], [0.004997299663771921, 0.026143513681394052, 0.06343094558383675, 0.11559843757981594, 0.18087055965788368, 0.25702480784517084, 0.34146792754782307, 0.4313243435956254, 0.5235341160251683, 0.6149571518764895, 0.702480137925041, 0.7831225539648681, 0.8541381477752107, 0.9131083765371413, 0.9580244176904754, 0.9873530206260416, 1.0], [0.004457993567787392, 0.023340094123774274, 0.056707968769078236, 0.10355543293519706, 0.16246000342813655, 0.23163212577717218, 0.3089701177521959, 0.3921241347220957, 0.4785675968530796, 0.5656739668866343, 0.6507965584533822, 0.7313489527340514, 0.8048835785249665, 0.8691660595674137, 0.9222430345922984, 0.9625011978233501, 0.9887140406322438, 1.0], [0.004001479383867387, 0.02096364839376648, 0.05099404158789055, 0.09328039592854495, 0.14667010367761796, 0.20970703958884296, 0.2806717900601717, 0.3576286499766346, 0.43847844922413814, 0.5210158208707761, 0.6029893605598321, 0.6821630391136516, 0.7563771934061506, 0.8236074297748696, 0.8820198253620791, 0.9300208896996932, 0.9663007519456326, 0.9898668482025972, 1.0], [0.003611642818556893, 0.018931837031588218, 0.046097933048431086, 0.08444722278420982, 0.1330361885580988, 0.19066859490476334, 0.25592540348210296, 0.3271998007638117, 0.4027367861650771, 0.4806763935785519, 0.559099492649032, 0.6360750448792709, 0.7097076516539024, 0.7781842229767616, 0.8398186157087111, 0.893093134981845, 0.9366958480743651, 0.9695526370802209, 0.9908518052709557, 1.0], [0.003276106669050099, 0.017181218145255715, 0.041871431117765194, 0.07680083708962197, 0.12118986732367606, 0.17404711263554218, 0.2341918863135922, 0.30028067683595017, 0.3708371805843969, 0.4442852869630112, 0.5189842887035737, 0.5932655334835065, 0.6654696989055137, 0.7339838582356595, 0.7972775083365947, 0.8539367530358905, 0.9026958717934537, 0.9424655423631864, 0.9723569466474369, 0.9916999557929327, 1.0], [0.0029852372832130628, 0.015662280557573547, 0.038198288245073556, 0.0701396190623258, 0.1108366733203635, 0.15946112944406526, 0.21502318535802029, 0.27639177909378315, 0.3423176329587308, 0.4114586915619052, 0.4824074446124389, 0.5537195807282936, 0.6239433897212819, 0.6916493150129622, 0.755459054449687, 0.8140736165126974, 0.8662997589709566, 0.9110742658026157, 0.9474855444063973, 0.9747919756603657, 0.9924354907256214, 1.0], [0.0027314460088842295, 0.014335933483699706, 0.03498632835121645, 0.06430264113215889, 0.10173934345216393, 0.14659920015766542, 0.19804660411818262, 0.25512320697168694, 0.31676578871044725, 0.3818260692567502, 0.44909210098681734, 0.5173108459509911, 0.5852115179512991, 0.6515292548958145, 0.7150286804747624, 0.7745269160648226, 0.8289156136217265, 0.87718159746542, 0.9184257249898493, 0.9518795932297199, 0.9769196632371289, 0.9930774850443482, 1.0], [0.0025086896389827445, 0.013170985000368889, 0.03216172768263549, 0.059160284613890765, 0.09370523422563984, 0.13520563098638086, 0.18295143477620673, 0.23612571946996597, 0.2938186667005872, 0.3550431384266733, 0.41875156920453116, 0.4838538912019968, 0.5492361859337144, 0.6137797438222284, 0.6763802055359521, 0.7359664575449969, 0.7915189583921992, 0.8420871815760148, 0.8868058750607934, 0.9249098542075925, 0.9557470550763801, 0.9787895175170725, 0.9936411423413659, 1.0], [0.0023121076177984915, 0.012142303771074897, 0.029664814214068847, 0.05460726328354278, 0.08657678275502653, 0.12506931209983138, 0.1694778408374138, 0.2191020363269966, 0.2731593030949705, 0.3307971297342993, 0.39110653542718576, 0.4531364059378609, 0.515908493620298, 0.5784328451129381, 0.6397234134973043, 0.6988136087122555, 0.7547715409190972, 0.8067147162308662, 0.8538239525472524, 0.895356294621761, 0.9306567200768073, 0.9591684333956145, 0.9804414867720773, 0.9941387002099848, 1.0], [0.002137754840779325, 0.01122946060565249, 0.027446943464319775, 0.050557380369212625, 0.08022422091233478, 0.11601496458748702, 0.15740773838866595, 0.20379895758313782, 0.2545121408770103, 0.3088077795622951, 0.365894122984637, 0.4249387248171482, 0.4850805823554159, 0.5454426920332588, 0.6051448381551349, 0.6633164283801916, 0.7191091887702756, 0.7717095332090876, 0.8203504266385679, 0.8643225686575713, 0.9029847330954238, 0.9357731085313031, 0.9622094865907312, 0.9819080873346961, 0.9945800980399754, 1.0], [0.001982402312500992, 0.010415712035092527, 0.025468147750456013, 0.0469395479727239, 0.07453996747497746, 0.10789625871486705, 0.14655736897811106, 0.19000048705998282, 0.23763812593281705, 0.2888260716927312, 0.3428720970842849, 0.39904532340024124, 0.4565861046963798, 0.514716300858142, 0.5726498006750369, 0.6296031526463668, 0.6848061597563768, 0.7375122949172582, 0.7870087961593148, 0.8326263048793097, 0.8737479163770056, 0.9098175190772665, 0.9403473057218672, 0.9649243392355685, 0.9832159998661838, 0.9949734758572125, 1.0], [0.001843386661593832, 0.009687231019540806, 0.023695348239150107, 0.043694735804558, 0.06943427879893221, 0.1005903811326854, 0.13677126821055244, 0.1775219573659193, 0.22232999118307128, 0.27063188584038284, 0.32182021876716727, 0.37525126799976294, 0.4302531076729568, 0.48613405803158183, 0.5421913837761863, 0.5977201313878155, 0.6520219943065595, 0.7044140944718857, 0.7542375697640191, 0.8008658592874873, 0.8437125821466905, 0.8822389102341397, 0.9159603411903557, 0.9444527826987508, 0.9673578569938135, 0.9843872802327865, 0.9953255513271093, 1.0], [0.0017184952934022467, 0.009032518495310017, 0.022100981357786813, 0.04077361101977503, 0.06483185036310753, 0.09399372568531336, 0.12791736994972228, 0.16620507152150776, 0.20840794782456448, 0.2540312117051822, 0.30253997377549535, 0.35336551412264616, 0.4059119503245875, 0.459563223773905, 0.5136903224747329, 0.5676586556635289, 0.6208354938051186, 0.6725973867373375, 0.7223374729826939, 0.7694725945042181, 0.8134501334282395, 0.8537544904322089, 0.8899131284723935, 0.9215021099473594, 0.9481510589669756, 0.9695474769380219, 0.9854402875829232, 0.9956419077642228, 1.0], [0.0016058778525400944, 0.008441948804031173, 0.020661933636159154, 0.03813469699711213, 0.06066914207658227, 0.08801845813988722, 0.11988302768489704, 0.15591374708438294, 0.19571586157012352, 0.23885329363336638, 0.2848534221035185, 0.33321226086401434, 0.38339998090610705, 0.4348667153860257, 0.4870485841530377, 0.5393738717727237, 0.5912692913707834, 0.6421662656731861, 0.6915071564230855, 0.7387513739119413, 0.7833812996605872, 0.8249079573005494, 0.8628763693862447, 0.8968705411002962, 0.9265180152719408, 0.951493945616477, 0.971524630855992, 0.9863904025392899, 0.9959272163607105, 1.0], [0.001503977326638774, 0.00790741531996209, 0.01935870848902584, 0.03574292537490614, 0.05689225853525517, 0.08258976331894716, 0.1125717741109366, 0.1465306454397049, 0.18411791831743823, 0.22494789906742613, 0.2686016183001324, 0.3146311306484368, 0.36256411155259194, 0.41190870408132424, 0.4621585661189247, 0.5127980661561917, 0.5633075743824563, 0.6131687947901147, 0.6618700835772074, 0.7089116992693157, 0.7538109306754932, 0.7961070500327451, 0.8353660404570976, 0.8711850490619495, 0.9031965197235615, 0.9310719621711364, 0.9545253157432502, 0.9733158613935449, 0.9872505879667329, 0.9961854092532896, 1.0], [0.0014114759654438001, 0.007422051826455696, 0.018174769095265803, 0.03356848869388058, 0.05345525785126261, 0.07764362749241416, 0.10590067435078988, 0.13795427748555525, 0.17349574784677543, 0.21218280408880402, 0.25364287008646663, 0.2974766635554076, 0.34326204160227936, 0.39055806631605955, 0.43890925130751685, 0.48784994832762435, 0.5369088317321096, 0.5856134376099926, 0.6334947138634949, 0.6800915374180713, 0.724955155054066, 0.7676535050807022, 0.8077753782079415, 0.8449343774921062, 0.8787726390975521, 0.908964277736526, 0.9352185227478345, 0.9572825118149126, 0.974943704254424, 0.9880318304951723, 0.9964198154713466, 1.0], [0.0013272524833751707, 0.006980011699868168, 0.017096016178822625, 0.03158592471873246, 0.05031879377055245, 0.07312504264229501, 0.09979815691249203, 0.1300965899920618, 0.16374595896330207, 0.20044153222357686, 0.23985099027130619, 0.2816174357206426, 0.3253626256484468, 0.37069039713817303, 0.4171902550556914, 0.464441089591379, 0.5120149899140457, 0.5594811194054443, 0.6064096173829943, 0.6523754919761545, 0.6969624688997337, 0.7397667612636281, 0.7804007262678021, 0.8184963756438731, 0.853708708002669, 0.8857188327955328, 0.9142368573118105, 0.9390045097612431, 0.959797472057249, 0.976427390681336, 0.9887434908817415, 0.9966332685901788, 1.0], [0.0012503479333373965, 0.006576291598856023, 0.016110370006833557, 0.02977338070833352, 0.04744901872833748, 0.06898654489476065, 0.09420222980162644, 0.1228809508309533, 0.15477803536984355, 0.18962135089669585, 0.22711362774522129, 0.2669349957541165, 0.3087457135021203, 0.352189066972796, 0.39689441297261474, 0.4424803413613204, 0.48855792912716467, 0.5347340585500795, 0.5806147711460179, 0.6258086287785659, 0.6699300532612757, 0.7126026159558951, 0.7534622492954564, 0.7921603528219582, 0.8283667672172581, 0.8617725909071304, 0.8920928151009255, 0.9190687545159036, 0.9424702522891587, 0.9620976377901373, 0.9777834107481249, 0.9893935840781973, 0.9968281926225657, 1.0], [0.0011799383006742459, 0.006206589701785595, 0.015207433539524673, 0.028112018487386783, 0.04481669252580171, 0.06518701898596117, 0.08905900793790963, 0.11624046437619028, 0.14651254308065986, 0.1796315131055634, 0.21533072112447305, 0.2533227387900465, 0.2933016771414238, 0.3349456495468724, 0.37791936340242205, 0.4218768197426598, 0.46646409903904545, 0.5113222107616352, 0.5560899837639233, 0.6004069742202446, 0.6439163677027391, 0.6862678520309705, 0.7271204377611021, 0.7661452036005386, 0.8030279446334174, 0.8374717020144321, 0.86919915371936, 0.8979548470021975, 0.9235072543301339, 0.9456506355273283, 0.9642066887995598, 0.9790259680238579, 0.9899890046528766, 0.9970066710330797, 1.0], [0.001115312346476135, 0.005867190971315927, 0.014378219244114263, 0.02658553045987382, 0.04239645404976722, 0.06169071558721557, 0.08432149294222681, 0.11011655998786123, 0.1388796043547207, 0.17039172382542975, 0.2044130932256341, 0.2406847900387533, 0.27893076515473464, 0.31885994386933253, 0.36016844119213415, 0.402541874625253, 0.44565775682152037, 0.48918794991786774, 0.5328011628676262, 0.5761654727668085, 0.6189508509859325, 0.6608316748816228, 0.7014892059710989, 0.740614015706566, 0.7779083403829385, 0.8130883472469975, 0.8458862945420755, 0.8760525690074397, 0.9033575852301974, 0.9275935321542591, 0.9485759527780752, 0.9661451428124316, 0.98016734884404, 0.9905357094079098, 0.9971705025603133, 1.0]]

def generate_radau_knots(timeHorizon, steps, scheme):
    base_grid_points = np.linspace(timeHorizon[0], timeHorizon[1], steps + 1)
    RADAU_SCHEME = np.array(RADAU_C[scheme - 1])
    all_knots = []

    for i in range(len(base_grid_points) - 1):
        t0 = base_grid_points[i]
        t1 = base_grid_points[i + 1]
        scaled_radau_nodes = t0 + (t1 - t0) * RADAU_SCHEME
        all_knots.extend(scaled_radau_nodes)

    return np.array(all_knots)#
