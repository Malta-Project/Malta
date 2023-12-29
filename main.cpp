#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include "malta.h"

using namespace std;

double integrand(double x) {
    return x * x;
}

int main() {
    Malta malta = Malta(2000, 100, 200);
    malta.integrate(integrand, 0, 2);
    cout << "the result is I=" << malta.get_results() << endl;
    return 0;
}

#endif