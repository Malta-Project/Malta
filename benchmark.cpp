#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>
#include "src/malta.h"

using namespace std;

double integrand(std::vector<double> x) {
    return std::sqrt(std::pow(x[0], 3) + std::pow(x[1], 2));
}

int main() {
    Malta malta = Malta(2, 1e5, 30, 5, false);
    int n_tests = 10;

    std::vector<int> values_intervals(n_tests);
    std::iota(std::begin(values_intervals), std::end(values_intervals), 3);
    std::vector<double> results_intervals(n_tests);
    for(int i=0; i<n_tests; i++) {
        malta.set_N_intervals(values_intervals[i]);
        malta.integrate(integrand, {{0.0, 2.0}, {1.0, 4.0}});
        cout << "result I=" << malta.get_result() << endl;
    }
    return 0;
}

#endif