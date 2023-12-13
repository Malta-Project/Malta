#ifndef MALTA_H
#define MALTA_H

#include "math.h"



class Malta {
    public:
        Malta();
        ~Malta();
        double integrate(double (*integrand)(double), int n, int n_step, int m);

    private:
        double chi_square(double *integrals, double *errors, int current_step, double avg_integral);
};

#endif