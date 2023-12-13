#include <iostream>
#include "src/malta.h"

//Compile with g++ main.cpp src/malta.cpp -o malta

double integrand(double x) {
    return x * x;
}

int main() {
    Malta malta;
    double result = malta.integrate(integrand);
    std::cout << "Endergebniss:\t" << result << std::endl;
    return 0;
}