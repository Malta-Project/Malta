#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <chrono>
#include "malta.h"

using namespace std;

double integrand(std::vector<double> x) {
    return x[0]*x[0];
}

int main() {
    Malta malta = Malta(1, 10000, 1000, 100);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //malta.integrate(integrand, {{0.0, 1.0}});
    malta.integrate(integrand);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "the result is I=" << malta.get_result() << endl;
    cout << "the error is sigma=" << malta.get_error() << endl;
    std::cout << "Integration time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " [ms]" << std::endl;
    return 0;
}

#endif