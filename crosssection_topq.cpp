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
    return x*x + y*y + z*z - 2*x*y - 2*x*z - 2*y*z;
}

double pi = 3.14159265358979323846,
       S = pow(14e3, 2), //GeV
       m_t = 173, //GeV
       m_j = 0, //GeV
       K_a1a2 = 1/36,
       pT_min = 25, //GeV
       pT_max = 425, //GeV
       phist_min = 0,
       phist_max = 2 * pi,
       thetast_min = 0,
       thetast_max = pi;

double integrand(vector<double> x) {
    //initial state a1, a2 = quark, anti-quark
    double phist = x[0],
           thetast = x[1],
           pT = x[2],
           s_tt = x[3],
           z = x[4],
           x1 = x[5];  

    double mT_j = sqrt(pow(pT,2) + pow(m_j,2));
    double mT_stt = sqrt(pow(pT,2) + pow(s_tt,2));
    double z_min = pow(mT_j + mT_stt, 2) / S;
    double x2 = z_min / (x1*z);
    double s = x1*x2*S;

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

double integrand_transformed(std::vector<double> x) { //integrand is jacobi-transformed to unit hypercube
    double phist = x[0],
           thetast = x[1],
           pT = x[2],
           s_tt = x[3],
           z = x[4],
           x1 = x[5];
    //non-transformed integration variables for jacobi-determinant:
    double pT_ = pT * (pT_max - pT_min) + pT_min;
    double mT_j_ = sqrt(pow(pT_,2) + pow(m_j,2));
    double s_tt_ = s_tt * (S + pow(m_j, 2) - 2*sqrt(S)*mT_j_ - 4*pow(m_t, 2)) + 4*pow(m_t, 2);
    double mT_stt_ = sqrt(pow(pT_,2) + s_tt_);
    double z_min_ = pow(mT_j_ + mT_stt_, 2) / S;
    std::vector<std::pair<double, double>> boundaries = {
        {phist_min, phist_max},
        {thetast_min, thetast_max},
        {pT_min, pT_max},
        {4*pow(m_t, 2), S + pow(m_j, 2) - 2*sqrt(S)*mT_j_},
        {z_min_, 1},
        {z_min_/z, 1}
    };

    std::vector<double> x_orig(x.size());
    double jac_det = 1;
    for(size_t i = 0; i < x.size(); ++i) {
        jac_det *= (boundaries[i].second - boundaries[i].first);
        x_orig[i] = x[i] * (boundaries[i].second - boundaries[i].first) + boundaries[i].first;
    }

    return jac_det * integrand(x_orig);
}

int main() {
    //std::cout << integrand_transformed({0.5, 0.5, 0.5, 0.5, 0.5, 0.5}) << std::endl;
    Malta malta = Malta(4, 1000, 100, 50);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    malta.integrate(integrand_transformed);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "the result is I = " << malta.get_result() << endl;
    cout << "the error is sigma = " << malta.get_error() << endl;
    cout << "Integration time = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]" << std::endl;
    return 0;
}

#endif