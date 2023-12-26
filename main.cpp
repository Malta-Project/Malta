#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include "malta.h"

using namespace std;

double integrand(double x) {
    return x * x;
}

int main() {
    Malta malta = Malta(1000, 10, 100);
    malta.integrate(&integrand);
    cout << malta.get_results() << endl;
    return 0;
}

//g++.exe -o main.exe src/math.cpp src/malta.cpp main.cpp -I "C:\Users\nabil\OneDrive\Dokumente\Uni\Module\5. Semester\CiS Projekt\Malta\src"

#endif