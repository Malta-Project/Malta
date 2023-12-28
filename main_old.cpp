#include <iostream>
#include "src/malta_old.h"
#include <cmath>

//Compile with g++ main_old.cpp src/malta_old.cpp -o malta

double integrand(double x) {
    return x * x;
    //return x *x * x;
    //return exp(x);
    //return log(x);
}

int main() {
    Malta malta;
    double result = malta.integrate(integrand, 10, 10, 1000);
    std::cout << "Endergebnis:\t" << result << std::endl;
    return 0;
}