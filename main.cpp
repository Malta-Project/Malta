#include <iostream>
#include "src/malta.h"
#include <cmath>

//Compile with g++ main.cpp src/malta.cpp -o malta

double integrand(double x) {
    return x * x;
    //return x *x * x;
    //return exp(x);
    //return log(x);
}

int main() {
    Malta malta;
    double result = malta.integrate(integrand, 5, 42, 10000);
    std::cout << "Endergebnis:\t" << result << std::endl;
    return 0;
}