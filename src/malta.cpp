#include "malta.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <cmath>

typedef struct Interval {
    double left_border;
    double right_border;
    double avg_f;
    double weight;
    int count;
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
    long double *integrals = new long double[n_step];
    long double *errors = new long double[n_step];
    long double avg_integral;
    long double avg_error;
    



    // FIRST STEP

    //initialize the borders
    double delta_n = 1.0 / (float) n;
    for (int i = 0; i < n; n++) {
        intervals[i].left_border = i*delta_n;
        intervals[i].right_border = i*delta_n + delta_n;
        intervals[i].count = 0;
        intervals[i].weight;
        intervals[i].avg_f = 0.0;
    }

    //the monte carlo step
    std::srand(42); //for ints
    std::mt19937 gen(42); //for doubles
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for(int i = 0; i < m; i++) {
        int randomInt = std::rand() % n;
        double x = intervals[randomInt].left_border + dis(gen) * (intervals[randomInt].right_border - intervals[randomInt].left_border);
        double y = dis(gen)/(float) n * 200 - 100;
        double y_th = integrand(x);
        if (y_th > 100 || y_th < -100) {
            std::cout << "Error 1: Function out of range!" << std::endl;
            return 0.0;
        }
        if else (y_th > 0 || y_th < y) {
            intervals[randomInt].count++;
        }
        if else (y_th < 0 || y_th < y) {
            intervals[randomInt].count--;
        }
        intervals[randomInt].avg_f += abs(y_th);
    }

    // evalutation of the integral and of the error
    long double integral = 0.0;
    long double error = 0.0;
    for (int i = 0; i < n; i++) {
        double s = intervals[i].count /(n * (intervals[i].right_border-intervals[i].left_border));
        integral += s;
        error += s*s - integral;
    } 
    integral /= (float)m;
    error /= (float)(m*(m-1));
    //append the integrals and errors
    integrals[0] = integral;
    errors[0] = error;
    avg_integral = integral;
    avg_error = error;
    std::cout << "End of first iteration. Integral:\t" << avg_integral << std::endl;
    std::cout << "Estimated error:\t" << avg_error << std::endl;

    // Xi^2 Test
    double chi = chi_square(integrals, errors, n_step);
    std::cout << "Chi^2:\t" << chi << std::endl;

    //Set new borders

    double total_weight = 0;
    for (int i=0 ; i<n; i++) {
        double tmp_sum = 0.0;
        for (int j=0; j<n; j++) {
            if (i != j) {
                tmp_sum += intervals[j].avg_f * (intervals[j].right_border-intervals[j].left_border);
            }
        }
        intervals[i].weight = intervals[i].avg_f * (intervals[i].right_border-intervals[i].left_border) / tmp_sum;
        intervals[i].weight = pow((((intervals[i].weight) -1)/log(intervals[i].weight)), 1.42);
        total_weight += intervals[i].weight;
    }

    double weight_per_interval = total_weight / n;

    for (int i=0; i<n-1; i++) {
        // We go from the left to the right
        double factor = intervals[i].weight/weight_per_interval;
        if (factor > 1) {
            intervals[i].right_border = intervals[i].left_border + (intervals[i].right_border-intervals[i].left_border)/factor;
            intervals[i+1].left_border = intervals[i].right_border;
            intervals[i+1].weight += (intervals[i].weight - intervals[i].weight / factor);
        }
        else {
            if (intervals[i].weight + intervals[i+1].weight > weight_per_interval) {
                double factor2 = intervals[i+1].weight/weight_per_interval;
                intervals[i].right_border = intervals[i].right_border + (intervals[i].left_border - intervals[i].right_border)/factor2;
                intervals[i+1].left_border = intervals[i].right_border;
                intervals[i+1].weight -= (intervals[i+1].weight - intervals[i+1].weight / factor2);
            }
            else {
                // Should guarantee (one-directional) stability, but slower convergence (in one direction)
                intervals[i].right_border = intervals[i].right_border + 0.9*(intervals[i].left_border - intervals[i].right_border);
                intervals[i+1].left_border = intervals[i].right_border;
                intervals[i+1].weight = intervals[i+1].weight*0.1;
            }
        }
    }

    // FIRST STEP OVER, begin the iterations

    for (int k = 1; k<n_step; k++) {    

        // Preparing the intervals for iterations
        for (int i = 0; i < n; n++) {
            intervals[i].count = 0;
            intervals[i].avg_f = 0.0;
        }

        // The Monte-Carlo Step
        for(int i = 0; i < m, i++) {
            int randomInt = std::rand() % n;
            double x = intervals[randomInt].left_border + dis(gen) * (intervals[randomInt].right_border - intervals[randomInt].left_border);
            double y = dis(gen)/(float) n * 200 - 100;
            double y_th = integrand(x);
            if (y_th > 100 || y_th < -100) {
                std::cout << "Error 1: Function out of range!" << std::endl;
                return 0.0;
            }
            else if (y_th > 0 || y_th < y) {
                intervals[randomInt].count++;
            }
            else if (y_th < 0 || y_th < y) {
                intervals[randomInt].count--;
            }
            intervals[randomInt].avg_f += abs(y_th);
        }


        // evalutation of the integral and of the error
        integral = 0.0;
        error = 0.0;
        for (int i = 0; i < n; i++) {
            double s = intervals[i].count /(n * (intervals[i].right_border-intervals[i].left_border));
            integral += s;
            error += s*s - integral;
        } 
        integral /= (float)m;
        error /= (float)(m*(m-1));
        //append the integrals and errors
        integrals[k] = integral;
        errors[k] = error;

        //calculate the avg_error (more complicated than for the first step)
        avg_error = 0.0;
        for (int i = 0; i<=k; i++) {
            avg_error += 1/(errors[i]*errors[i]);
        }
        avg_error = 1/sqrt(avg_error);

        //calculate the avg_integral (more complicated than for the first step)
        avg_integral = 0.0;
        for (int i = 0; i<=k; i++) {
            avg_integral += integrals[i]/errors[i];
        }
        avg_integral *= avg_error*avg_error;
        std::cout << "End of first iteration. Integral:\t" << avg_integral << std::endl;
        std::cout << "Estimated error:\t" << avg_error << std::endl;

        // Xi^2 Test
        double chi = chi_square(integrals, errors, n_step, avg_integral);
        std::cout << "Chi^2:\t" << chi << std::endl;

        //Set new borders

        double total_weight = 0;
        for (int i=0 ; i<n; i++) {
            double tmp_sum = 0.0;
            for (int j=0; j<n; j++) {
                if (i != j) {
                    tmp_sum += intervals[j].avg_f * (intervals[j].right_border-intervals[j].left_border);
                }
            }
            intervals[i].weight = intervals[i].avg_f * (intervals[i].right_border-intervals[i].left_border) / tmp_sum;
            intervals[i].weight = pow((((intervals[i].weight) -1)/log(intervals[i].weight)), 1.42);
            total_weight += intervals[i].weight;
        }

        double weight_per_interval = total_weight / n;

        for (int i=0; i<n-1; i++) {
            // We go from the left to the right
            double factor = intervals[i].weight/weight_per_interval;
            if (factor > 1) {
                intervals[i].right_border = intervals[i].left_border + (intervals[i].right_border-intervals[i].left_border)/factor;
                intervals[i+1].left_border = intervals[i].right_border;
                intervals[i+1].weight += (intervals[i].weight - intervals[i].weight / factor);
            }
            else {
                if (intervals[i].weight + intervals[i+1].weight > weight_per_interval) {
                    double factor2 = intervals[i+1].weight/weight_per_interval;
                    intervals[i].right_border = intervals[i].right_border + (intervals[i].left_border - intervals[i].right_border)/factor2;
                    intervals[i+1].left_border = intervals[i].right_border;
                    intervals[i+1].weight -= (intervals[i+1].weight - intervals[i+1].weight / factor2);
                }
                else {
                    // Should guarantee (one-directional) stability, but slower convergence (in one direction)
                    intervals[i].right_border = intervals[i].right_border + 0.9*(intervals[i].left_border - intervals[i].right_border);
                    intervals[i+1].left_border = intervals[i].right_border;
                    intervals[i+1].weight = intervals[i+1].weight*0.1;
                }
            }
        }
    }


    // CLEANUP
        delete [] intervals;
        delete [] integrals;
        delete [] errors;

    return avg_integral;
}

double Malta::chi_square(double *integrals, double *errors, int current_step, long double avg_integral) {
    // calculate the chi square
    double chi = 0;
    for (int i = 0; i<=current_step; i++) {
        chi += (integrals[i]-avg_integral)*(integrals[i]-avg_integral)/(errors[i]*errors[i]);
    }
    return chi;
}