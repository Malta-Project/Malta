#ifndef MALTA_H
#define MALTA_H

#include "math.h"

class Malta {
    public:
        Malta();
        ~Malta();
        double integrate(double (*integrand)(double));
        double integrate(double (*integrand)(double), double lower_limit, double upper_limit);
};

#endif