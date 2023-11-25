## Vegas Algorithm Pseudocode


p(x):
    find interval of x: x_i - dxi <= x <= x_i
    return 1/(N*dx_i)
   

vegas(N):

dx_i = 1/N

intervallgrenzen berechnen [array]
p(x) anpassen mit neuen intervallgrenzen
intervallpunkte [array] aus p(x) holen
monte-carlo integration mit intervallpunkte
sigma_i berechnen
sigma_I berechnen
I_quer berechnen
Chi^2 test

iterate over iterations M:
    f_i berechnen [array]
    m_i berechnen

    neue intervalle = mehr oder weniger gleichmäßig aufgeteilte subintervalle #ggf. strategie der aufteilung anpassen
    p(x) anpassen mit neuen intervallgrenzen
    intervallpunkte [array] aus p(x) holen
    monte-carlo integration mit intervallpunkte
    sigma_i berechnen
    sigma_I berechnen
    I_quer berechnen
    Chi^2 test



-----------------------------------------
step()

iterationen:
    f_i berechen
    m_i berechnen
    step()