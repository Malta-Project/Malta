#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <chrono>
#include "malta.h"

using namespace std;

double integrand(double x) {
    return x * x;
}

int main() {
    Malta malta = Malta(10000, 50, 100);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    malta.integrate(&integrand);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << malta.get_results() << endl;
    std::cout << "calculation time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    return 0;
}

//g++.exe -o main.exe src/math.cpp src/malta.cpp main.cpp -I "C:\Users\nabil\OneDrive\Dokumente\Uni\Module\5. Semester\CiS Projekt\Malta\src"

#endif