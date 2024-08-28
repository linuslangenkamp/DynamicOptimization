from sympy import *
from sympy import Integer

x, y, t = symbols("x y t")

def calcL2(f, var):
    return integrate(diff(f, var)**2, (var, 0, 1))

# hier annahme, dass das polynom auf dem interval [0, 1] == [t_i, t_i + h] sich nicht verändert
# bei sprüngen wird das integral eh nie verschwinden. Überlege Sprungfunktion auf kleiner werdenden interval mit e.g.
# kubischer interpolation, steigung wird nur noch höher

f = x**2 + 3*x

# [t_i + j/2**k * h, t_i + (j+1)/2**k * h] -> [0, 1] ohne einschränkung
# ableitung des transformierten polynom p: d/dt p(t)
# berechne (d/dt p(t)) ** 2
# berechne int_0^1 (d/dt p(t)) ** 2 dt

# hier einfach t_i = 0, h = 1
sumLast = 0
for k in range(5):
    step = 2**k
    sumNow = 0
    # f += 1 / 10 * x + 5/24 * x**5  # error testing
    for j in range(step):
        inner = t / Integer(step) + Integer(j) / Integer(step)
        fbar = f.subs(x, inner)
        L2 = calcL2(fbar, t)
        sumNow = max(L2, sumNow)    # += L2 für summe, max(L2, sumNow) für tatsächlich konvergenzrate
        print(f"L2({inner}) = {float(L2)}") #  sum L2 * step = L2 iteration 0
        # jede iteration halbiert mindestens den L2 score, falls das polynom sich nicht mehr ändert!!
        # if the solution is similar enough the convergence is extremely fast
        # if not it's not, assume jump or p(x) on [t_i, t_i + h] and in next iteration its p(x) rescaled to [t_i, t_i + h/2]
        # and p(t_i + h/2) const on [t_i + h/2, t_i + h]
    if k > 0:
        print(f"sumNow / sumLast = {float(sumLast / sumNow)}")
    print()
    sumLast = sumNow

"""
* initiale Optimierung -> refinement: sprünge, steepness, knicke, osz
* density function als indirekte inspiration
-> "local" density refinement
* interval I_i = [t_i, t_i + h = t_{i+1}]: interpoliere u_h(t) exakt
* idee steepness auf I_i ist determiniert durch integral_0^1 norm(u_h'(t)) dt
* interval [0, 1] da so nur die werte eine rolle spielen, sonst doppelt gemoppelt -> h soll dadurch ja angepasst werden
  und insbesondere verändert sich diese kriterium dadurch :D
* L2 = integral_0^1 u_h'(t)^2 dt, weil
    * integral lässt sich mit Radau Formeln schnell evaluieren
    * falls das polynom im nächsten schritt gleich ist, resultiert mindestens lineare konvergenz mit faktor 1/2, bis zu 1/4
    -> garantiert schnelle konvergenz, wenn die lösung gut ist
    * sprünge und veränderungen des polynom können trotzdem so behandelt werden

"""