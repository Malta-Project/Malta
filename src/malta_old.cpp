#include "malta_old.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <cmath>

typedef struct Interval {
    double left_border;
    double right_border;
    double f;
    double avg_f;
    double weight;
} Interval;

Malta::Malta() {
    // Constructor
}

Malta::~Malta() {
    // Destructor
}

double Malta::integrate(double (*integrand)(double), int n, int n_step, int m) {
    // Integrate the given function from 0 to 1
    // n is the number of intervals
    // n_step is the number of steps
    // m is the number of points
    // The f space shall be first restricted between 100 and -100

    Interval *intervals = new Interval[n];
    double *integrals = new double[n_step];
    double *errors = new double[n_step];
    double avg_integral;
    double avg_error;
    



    // FIRST STEP

    //initialize the borders
    double delta_n = 1.0 / (float) n;
    for (int i = 0; i < n; i++) {
        intervals[i].left_border = i*delta_n;
        intervals[i].right_border = i*delta_n + delta_n;
        intervals[i].f = 0.0;
        intervals[i].weight;
        intervals[i].avg_f = 0.0;
    }

    //the monte carlo step
    std::srand(42); //for ints
    std::mt19937 gen(42); //for doubles
    std::uniform_real_distribution<> dis(0.0, 1.0);
    int randomInt;
    for(int i = 0; i < m; i++) {
        randomInt = std::rand() % n;
        double x = intervals[randomInt].left_border + dis(gen) * (intervals[randomInt].right_border - intervals[randomInt].left_border);
        double y = integrand(x);
        if (y > 100 || y < -100) {
            std::cout << "Error 1: Function out of range!" << std::endl;
            return 0.0;
        }
        intervals[randomInt].f += y;
        if (y > 0) {
            intervals[randomInt].avg_f += y;
        } else {
            intervals[randomInt].avg_f -= y;
        }
        
    }
    // evalutation of the integral and of the error
    double integral = 0.0;
    double error = 0.0;
    for (int i = 0; i < n; i++) {
        double s = intervals[i].f *(n * (intervals[i].right_border-intervals[i].left_border));
        integral += s;
        error += s*s;
    }
    error -= integral*integral;
    integral /= (float)m;
    error /= (float)(m*(m-1));
    //append the integrals and errors
    integrals[0] = integral;
    errors[0] = error;
    avg_integral = integral;
    avg_error = error;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "End of first iteration. Integral:\t" << avg_integral << std::endl << std::endl;
    std::cout << "Estimated error:\t" << avg_error << std::endl;

    //Set new borders

    double total_weight = 0;
    double weight_factor = 0.0;
    for (int i=0 ; i<n; i++) {
        weight_factor += intervals[i].avg_f * (intervals[i].right_border-intervals[i].left_border);
    }
    for (int i=0 ; i<n; i++) {
        intervals[i].weight = intervals[i].avg_f * (intervals[i].right_border-intervals[i].left_border) / weight_factor;
        //intervals[i].weight = pow((((intervals[i].weight) -1)/log(intervals[i].weight)), 1.42); // damping!
        total_weight += intervals[i].weight;
    }
    

    double weight_per_interval = total_weight / n;
    int index_of_interval = 0;
    double delta = 0.0;
    for (int i = 0; i < n; i++) {
        // We go from the left to the right
        delta += intervals[i].weight;
        if (delta > weight_per_interval) {
            while (delta > weight_per_interval) {
                delta -= weight_per_interval;
                intervals[index_of_interval].right_border = intervals[i].right_border - (intervals[i].right_border - intervals[i].left_border) * delta / intervals[i].weight;
                intervals[index_of_interval+1].left_border = intervals[index_of_interval].right_border;
                index_of_interval++;
            }
        }
    }
    std::cout << "------------------------------------------------------------" << std::endl;
    for (int i = 0; i< n; i++) {
        std::cout << "Interval: " << i << "\tLeft interval: " << intervals[i].left_border << "\t Right border:\t" << intervals[i].right_border << std::endl << std::endl;
    }
    

    // FIRST STEP OVER, begin the iterations

    for (int k = 1; k<n_step; k++) {    

        // Preparing the intervals for iterations
        for (int i = 0; i < n; i++) {
            intervals[i].f = 0.0;
            intervals[i].avg_f = 0.0;
        }

        // The Monte-Carlo Step
        for(int i = 0; i < m; i++) {
            randomInt = std::rand() % n;
            double x = intervals[randomInt].left_border + dis(gen) * (intervals[randomInt].right_border - intervals[randomInt].left_border);
            double y = integrand(x);
            if (y > 100 || y < -100) {
                std::cout << "Error 1: Function out of range!" << std::endl;
                return 0.0;
            }
            intervals[randomInt].f += y;
            if (y > 0) {
                intervals[randomInt].avg_f += y;
            } else {
                intervals[randomInt].avg_f -= y;
            }
        }


        // evalutation of the integral and of the error
        double integral = 0.0;
        double error = 0.0;
        for (int i = 0; i < n; i++) {
            double s = intervals[i].f *(n * (intervals[i].right_border-intervals[i].left_border));
            integral += s;
            error += s*s;
        }
        error -= integral*integral/m;
        integral /= (float)m;
        error /= (float)(m*(m-1));
        //append the integrals and errors
        integrals[k] = integral;
        errors[k] = error;

        //calculate the avg_error (more complicated than for the first step)
        avg_error = 0.0;
        for (int i = 0; i<=k; i++) {
            avg_error += 1/(errors[i]);
        }
        avg_error = 1/(avg_error);

        //calculate the avg_integral (more complicated than for the first step)
        avg_integral = 0.0;
        for (int i = 0; i<=k; i++) {
            avg_integral += integrals[i]/(errors[i]);
        }
        avg_integral *= avg_error;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "End of " << k+1 << "-th Iteration.\n\nIntegral:\t" << avg_integral << std::endl << std::endl;
        std::cout << "Estimated error:\t" << avg_error << std::endl << std::endl;

        // Xi^2 Test
        double chi = chi_square(integrals, errors, k, avg_integral);
        std::cout << "Chi^2:\t" << chi << std::endl << std::endl;

        //Set new borders

        double total_weight = 0;
        double weight_factor = 0.0;
        for (int i=0 ; i<n; i++) {
            weight_factor += intervals[i].avg_f * (intervals[i].right_border-intervals[i].left_border);
        }
        for (int i=0 ; i<n; i++) {
            intervals[i].weight = intervals[i].avg_f * (intervals[i].right_border-intervals[i].left_border) / weight_factor;
            //intervals[i].weight = pow((((intervals[i].weight) -1)/log(intervals[i].weight)), 1.42); // damping!
            total_weight += intervals[i].weight;
        }

        double weight_per_interval = total_weight / n;

        int index_of_interval = 0;
        double delta = 0.0;
        for (int i = 0; i < n; i++) {
            // We go from the left to the right
            delta += intervals[i].weight;
            if (delta > weight_per_interval) {
                while (delta > weight_per_interval) {
                    delta -= weight_per_interval;
                    intervals[index_of_interval].right_border = intervals[i].right_border - (intervals[i].right_border - intervals[i].left_border) * delta / intervals[i].weight;
                    intervals[index_of_interval+1].left_border = intervals[index_of_interval].right_border;
                    index_of_interval++;
                }
            }
        }
    }
    std::cout << "------------------BORDER-DEBUG------------------------------------------" << std::endl;
    for (int i = 0; i< n; i++) {
            std::cout << "Interval: " << i << "\tLeft interval: " << intervals[i].left_border << "\t Right border:\t" << intervals[i].right_border << std::endl << std::endl;
        }


    // CLEANUP
        delete [] intervals;
        delete [] integrals;
        delete [] errors;

    return avg_integral;
}

double Malta::chi_square(double *integrals, double *errors, int current_step, double avg_integral) {
    // calculate the chi square
    double chi = 0;
    for (int i = 1; i<=current_step; i++) {
        chi += (integrals[i]-avg_integral)*(integrals[i]-avg_integral)/(errors[i]);
    }
    return chi;
}