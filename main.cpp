#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <chrono>
#include "src/malta.h"
#include <cmath>

using namespace std;

// g++ -I ./src main.cpp ./src/math.cpp ./src/malta.cpp -o malta

double integrand(std::vector<double> x) {
    return std::sqrt(std::pow(x[0], 3) + std::pow(x[1], 2));
}

int main() {
    Malta malta = Malta(2, 10000, 100, 50);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    malta.integrate(integrand, {{0.0, 2.0}, {1.0, 4.0}});
    //malta.integrate(integrand); // if no custom integration bounds used
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "the result is I=" << malta.get_result() << endl;
    cout << "the error is sigma=" << malta.get_error() << endl;
    std::cout << "Integration time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " [ms]" << std::endl;
    return 0;
}

#endif