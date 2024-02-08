#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <cmath>
#include <iomanip>
#include "src/malta.h"

using namespace std;

double integrand(std::vector<double> x) {
    return std::sqrt(std::pow(x[0], 3) + std::pow(x[1], 2));
}

int main() {
    Malta malta = Malta(2, 1e5, 30, 100);
    malta.set_threads(8);
    malta.integrate(integrand, {{0.0, 2.0}, {1.0, 4.0}});
    cout << "result I=" <<  std::setprecision(15) << malta.get_result() << endl;
    cout << "error sigma=" << malta.get_error() << endl;
    std::cout << "time = " << malta.get_integration_time_ms() << " [ms]" << std::endl;
    return 0;
}

#endif