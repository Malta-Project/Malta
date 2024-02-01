#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <chrono>
#include <cmath>
#include <math.h>
#include "src/malta.h"
#include "matrix_element_top.cpp"

using namespace std;

double kaellen(double x, double y, double z) {
    return sqrt(abs(x*x + y*y + z*z - 2*x*y - 2*x*z - 2*y*z)); //KEINE WURZEL?
}

double pi = 3.14159265358979323846;
double S = 14e3; //GeV
double m_t = 173; //GeV
double m_j = 0; //GeV
double K_a1a2 = 1/36;
double pT_min = 25; //GeV
double pT_max = 425; //GeV

double integrand(vector<double> x) {
    //initial state a1, a2 = quark, anti-quark
    double pT = x[0],
           s_tt = x[1],
           z = x[2],
           x1 = x[3];
    
    double mT_j = sqrt(pow(pT,2) + pow(m_j,2));
    double mT_stt = sqrt(pow(pT,2) + pow(s_tt,2));
    double z_min = pow(mT_j + mT_stt, 2) / S;
    double x2 = z_min / (x1*z); //WARUM??
    double s = x1*x2*S;

    double phist = pi;
    double thetast = pi/2; //WARUM??

    double phist_min = 0;
    double phist_max = 2 * pi;
    double thetast_min = 0;
    double thetast_max = pi;
    double costheta = (s+pow(m_j,2) - s_tt) / (2*sqrt(s)*mT_j);
    double sintheta = sqrt(pow(costheta, 2) -1);
    double pzj = mT_j * sintheta;
    double m2 = pow(m_t, 2);
    double Etst = sqrt(s_tt)/2;
    double ptst = sqrt(kaellen(s_tt, m2, m2)) / (2*sqrt(s_tt));
    double Ett = (s+s_tt-pow(m_j,2)) / (2*sqrt(s));
    double gamm = Ett / sqrt (s_tt);
    double ptt0 = Ett;
    double pttx = 0;
    double ptty = -pT;
    double pttz = -pzj;
    double bx = pttx/Ett;
    double by = ptty/Ett;
    double bz = pttz/Ett;
    double b2 = pow(bx, 2) + pow(by, 2) + pow(bz, 2);
    double Et = gamm*Etst - gamm*bx*ptst*cos(phist)*sin(thetast) 
                -gamm*by*ptst*sin(phist)*sin(thetast)
                -gamm*bz*ptst*cos(thetast);
    double Etbar = gamm*Etst+ gamm*bx*ptst*cos(phist)*sin(thetast);
                   +gamm*by*ptst*sin(phist)*sin(thetast)
                   +gamm*bz*ptst*cos(thetast);
    double ptz = -gamm*bz*Etst;
                 +(gamm-1)*ptst*cos(phist)*sin(thetast )*bx*bz/b2
                 +(gamm-1)*ptst*sin(phist)*sin(thetast )*by*bz/b2
                 +((gamm-1)*pow(bz, 2)/b2+1)*ptst*cos(thetast );
    double ptzbar = -gamm*bz* Etst
                    -(gamm-1)*ptst*cos(phist)*sin(thetast)*bx*bz/b2
                    -(gamm-1)*ptst*sin(phist)*sin(thetast)*by*bz/b2
                    -((gamm-1)*pow(bz, 2)/b2+1)*ptst*cos(thetast);
    double T = m2-sqrt(s)*(Et-ptz);
    double U = m2-sqrt(s)*(Et+ptz);
    double T14 = m2-sqrt(s)*(Etbar-ptzbar);
    double T24 = m2-sqrt(s)*(Etbar+ptzbar);
    double S34 = s_tt;
    double S = s;
    double MT = m_t;
    double Nc = 3;
    double alphas = 0.118;
    double GS = sqrt(alphas*4*pi);

    double integrand_val = -(1/z) * (z_min/(x1*z)) * (pT/(16*pow(pi, 2)*s_tt))
                       * sqrt(kaellen(s_tt, m2, m2)/kaellen(s, s_tt, pow(mT_j, 2)))
                       * (K_a1a2/(4*pi*s)) * matrix_element_top(S, T, U, T14, T24, S34, MT, GS, Nc);

    return integrand_val;
}

int main() {
    Malta malta = Malta(4, 1000, 100, 50);
    //integration variable dependent boundaries:
    double pT = (pT_min + pT_max)/2;
    double s_tt = S / 2;
    double z = 0.5;
    
    double mT_j = sqrt(pow(pT,2) + pow(m_j,2));
    double mT_stt = sqrt(pow(pT,2) + pow(s_tt,2));
    double z_min = pow(mT_j + mT_stt, 2) / S;
    std::vector<std::pair<double, double>> boundaries = {
        {pT_min, pT_max},
        {4*pow(m_t, 2), S + pow(m_j, 2) - 2*sqrt(S)*mT_j},
        {z_min, 1},
        {0, 1}
    };

    cout << integrand({
        (boundaries[0].first+boundaries[0].second)/2,
        (boundaries[1].first+boundaries[1].second)/2,
        (boundaries[2].first+boundaries[2].second)/2,
        (boundaries[3].first+boundaries[3].second)/2
    }) << endl;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    malta.integrate(integrand, boundaries);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "the result is I = " << malta.get_result() << endl;
    cout << "the error is sigma = " << malta.get_error() << endl;
    cout << "Integration time = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]" << std::endl;
    return 0;
}

#endif