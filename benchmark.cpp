#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>
#include <iomanip>
#include "src/malta.h"

using namespace std;

double integrand(std::vector<double> x) {
    return std::sqrt(std::pow(x[0], 3) + std::pow(x[1], 2));
}

int main() {
    Malta malta = Malta(2, 1e4, 20, 20, false);
    malta.set_threads(8);

    std::string mode = "threads";

    if (mode == "intervals") {
        int n_tests = 100;
        malta.set_threads(4);
        std::ofstream outputFile("benchmarks/test_intervals.txt");
        int n_vals_intervals = 50;
        std::vector<int> values_intervals(n_vals_intervals);
        std::iota(std::begin(values_intervals), std::end(values_intervals), 1);
        for(int i=0; i<n_vals_intervals; i++) {
            malta.set_N_intervals(values_intervals[i]);
            cout << "test value = " << values_intervals[i] << endl;
            for(int j=0; j<n_tests; j++) {
                malta.integrate(integrand, {{0.0, 2.0}, {1.0, 4.0}});
                outputFile << std::setprecision(15) << values_intervals[i] << ", " << malta.get_result() << ", " << malta.get_error() << endl;
            }
        }
        outputFile.close();
        malta.set_N_intervals(20);
    } else if (mode == "points") {
        int n_tests = 50;
        std::ofstream outputFile("benchmarks/test_points.txt");
        std::vector<int> values_points = {(int) 1e2, (int) 1e3, (int) 1e4, (int) 1e5, (int) 1e6};
        for(auto &n_points : values_points) {
            malta.set_N_points(n_points);
            cout << "test value = " << n_points << endl;
            for(int j=0; j<n_tests; j++) {
                malta.integrate(integrand, {{0.0, 2.0}, {1.0, 4.0}});
                outputFile << std::setprecision(15) << n_points << ", " << malta.get_result() << ", " << malta.get_error() << endl;
            }
        }
        outputFile.close();
        malta.set_N_points(1e4);
    } else if (mode == "threads") {
        malta.set_N_points(1e4);
        malta.set_N_iterations(40);
        int n_tests = 50;
        std::ofstream outputFile("benchmarks/test_threads.txt");
        int n_vals_threads = 16;
        std::vector<int> values_threads(n_vals_threads);
        std::iota(std::begin(values_threads), std::end(values_threads), 1);
        for(int i=0; i<n_vals_threads; i++) {
            malta.set_threads(values_threads[i]);
            cout << "test value = " << values_threads[i] << endl;
            for(int j=0; j<n_tests; j++) {
                malta.integrate(integrand, {{0.0, 2.0}, {1.0, 4.0}});
                outputFile << std::setprecision(15) << values_threads[i] << ", " << malta.get_integration_time_ms() << ", " << malta.get_result() << endl;
            }
        }
        outputFile.close();
        malta.set_threads(8);
    }

    return 0;
}

#endif