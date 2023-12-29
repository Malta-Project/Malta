#include <cstdlib>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "malta.h"
#include "malta_math.h"
Malta::Malta(int N_points, int N_intervals, int max_iterations) {
    this->N_points = N_points;
    this->N_intervals = N_intervals;
    this->max_iterations = max_iterations;
    srand(42); //Replace with time(NULL) & #include <ctime> for the final application
    this->delta_sigma_break = 1e-6;
}

Malta::~Malta() {
    // Destructor
}

void Malta::integrate(double (*integrand)(double)) {
    this->sigma_iterations = std::vector<double>();
    this->integral_iterations = std::vector<double>();
    this->sigma_result = std::vector<double>();
    this->integral_result = std::vector<double>();
    this->chi_2_dof = std::vector<double>();
    this->i_iteration = 0;
    this->total_weight = 0.0;
    this->interval_borders = std::vector<double>(this->N_intervals+1);
    this->interval_values = std::vector<double>(this->N_intervals);
    this->interval_abs_values = std::vector<double>(this->N_intervals);
    this->interval_weights = std::vector<double>(this->N_intervals, 0.0);
    double dx = 1.0 / this->N_intervals;
    this->dx_i = std::vector<double>(this->N_intervals, dx);
    for (int i = 0; i <= this->N_intervals; i++) {
        this->interval_borders[i] = dx * i;
    }
    for (int i = 0; i < this->N_intervals; i++) {
        this->interval_values[i] = 0.0;
        this->interval_abs_values[i] = 0.0;
    }
    //this->sample_points();
    this->montecarlo(integrand);
    this->calculate_integral();
    this->calculate_erros();
    for(int i=1; i<=this->max_iterations; i++) {
        this->i_iteration = i;
        this->calculate_mi();
        this->alter_intervals();
        //this->sample_points();
        this->calculate_integral();
        this->calculate_erros();
        std::cout << "it=" << i << "; X^2/dof: " << this->chi_2_dof[i-1] << "; I=" << this->integral_result[i] << std::endl;
        if(Math::abs(this->sigma_iterations[i] - this->sigma_iterations[i-1]) < this->delta_sigma_break) {
            //break;
        }
    }
}

// double Malta::integrate(double (*integrand)(double), double lower_limit, double upper_limit) {
//     /* double (new_integrand)(double)  = [lower_limit, upper_limit, integrand](double x) {
//         return integrand(x * (upper_limit - lower_limit) + lower_limit) * (upper_limit-lower_limit);
//     };
//     return this->integrate(&new_integrand); */
// }

void Malta::calculate_mi() {
    // We calculate the m_i value for each interval
    this->total_weight = 0;
    double weight_factor = 0.0;
    for (int i=0 ; i<this->N_intervals; i++) {
        weight_factor += this->interval_abs_values[i] * this->dx_i[i];
    }
    for (int i=0 ; i<this->N_intervals; i++) {
        this->interval_weights[i] = this->interval_abs_values[i] * this->dx_i[i] / weight_factor;
        //this->interval_weights[i] = pow((((this->interval_weights[i]) -1)/log(this->interval_weights[i])), 1.42); // damping is used for... ähm...
        this->total_weight += this->interval_weights[i];
    }
}

void Malta::alter_intervals() {
    // We alter the borders of the intervals and also recalculate dx
    double weight_per_interval = this->total_weight / this->N_intervals;
    int interval_idx = 0;
    double delta = 0.0;
    for (int i = 0; i < this->N_intervals; i++) {
        // We go from the left to the right
        delta += this->interval_weights[i];
        if (delta > weight_per_interval) {
            while (delta > weight_per_interval) {
                delta -= weight_per_interval;
                this->interval_borders[interval_idx+1] = this->interval_borders[i+1] - this->dx_i[i] * delta / this->interval_weights[i];
                interval_idx++;
            }
        }
    }
    //Por debugging
    for (int i = 0; i <= this->N_intervals; i++) {
        std::cout << "Borders: " << this->interval_borders[i] << std::endl;
    }

    // We recalculate the dx
    for (int i = 0; i < this->N_intervals; i++) {
        this->dx_i[i] = this->interval_borders[i + 1] - this->interval_borders[i];
    }
}

    void Malta::calculate_integral() {
        double integral = 0.0;
        this->S_2 = 0.0;
        for (int i = 0; i < this->N_intervals; i++) {
            double val = this->interval_values[i] * this->dx_i[i] * this->N_intervals;
            integral += val;
            S_2 += val * val;
        }
        this->S_2 /= (double) this->N_points;
        this->integral_iterations.push_back(integral / (double) this->N_points);
    }

// double Malta::p(double x) {
//     for(int i=0; i<this->N_intervals; i++) {
//         if(x >= this->intervals[i] && x <= this->intervals[i+1]) {
//             return 1.0 / (this->dx_i[i] * this->N_intervals);
//         }    
//     }
// }

void Malta::calculate_erros() {
    // This function calculates the error using Lepage's formula as well as the overall
    // integral and error. The second part calculates the Chi^2
    double sigma_sq = (this->S_2 - std::pow(this->integral_iterations[this->i_iteration], 2)) / (this->N_points - 1);
    this->sigma_iterations.push_back(sigma_sq);
    double result_1 = 0.0;
    double result_2 = 0.0;
    for(int i=0; i<=this->i_iteration; i++) {
        double val = this->integral_iterations[i] / this->sigma_iterations[i];
        val *= val;
        result_1 += this->integral_iterations[i] * val;
        result_2 += val;
    }
    double result = result_1 / result_2;
    double sigma_res = result / std::sqrt(result_2);
    this->sigma_result.push_back(sigma_res);
    this->integral_result.push_back(result);

    //This part calculates the Chi^2
    if (this->i_iteration == 0) return;
    double chi_2 = 0.0;
    for(int i=0; i<=this->i_iteration; i++) {
        chi_2 += std::pow(this->integral_iterations[i]-result, 2)/this->sigma_iterations[i];
    }
    chi_2 /= this->i_iteration;
    this->chi_2_dof.push_back(chi_2);
}

// void Malta::sample_points() {
//     this->points = std::vector<double>(this->N_points);
//     std::vector<int>* interval_ixs = Math::get_random_points(1, this->N_intervals, this->N_points);
//     std::sort(interval_ixs->begin(), interval_ixs->end());
//     int i=0;
//     for(auto &ix : *interval_ixs) {
//         double interval_lower = this->intervals[ix-1];
//         double interval_upper = this->intervals[ix];
//         double point = Math::get_random_point(interval_lower, interval_upper);
//         this->points[i] = point;
//         i++;
//     }
//     delete interval_ixs;
// }

void Malta::montecarlo(double (*integrand)(double)) {
    //Performs the Monte Carlo step; chooses random interval, generates random point
    //evalutes the integrand and records the function values and absolute values
    int interval_idx;
    double x, y;
    for (int i = 0; i < this->N_points; i++) {
        interval_idx = Math::get_random_point(0, this->N_intervals-1);
        x = Math::get_random_point(this->interval_borders[interval_idx], this->interval_borders[interval_idx+1]);
        y = integrand(x);
        this->interval_values[interval_idx] += y; //We do not check for singularities
        this->interval_abs_values[interval_idx] += Math::abs(y);
    }
}

void Malta::set_N_points(int N_points) {
    this->N_points = N_points;
}

int Malta::get_N_points() {
    return N_points;
}

void Malta::set_seed(int seed) {
    srand(seed);
}

void Malta::set_N_intervals(int N_intervals) {
    this->N_intervals = N_intervals;
}

int Malta::get_N_intervals() {
    return N_intervals;
}

double Malta::get_results() {
    return this->integral_iterations[this->i_iteration];
}

void Malta::set_K(int K) {
    this->K = K;
}

int Malta::get_K() {
    return this->K;
}