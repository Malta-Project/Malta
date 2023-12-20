#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "malta.h"
#include "malta_math.h"

Malta::Malta(int N_points, int N_intervals, int max_iterations) {
    this->N_points = N_points;
    this->N_intervals = N_intervals;
    this->max_iterations = max_iterations;
    srand(time(NULL));
    this->K = 1000;
    this->delta_sigma_break = 1e-3;
}

Malta::~Malta() {
    // Destructor
}

double Malta::integrate(double (*integrand)(double)) {
    this->sigma_iterations = std::vector<double>();
    this->integral_iterations = std::vector<double>();
    this->sigma_result = std::vector<double>();
    this->integral_result = std::vector<double>();
    this->chi_2_dof = std::vector<double>();
    this->i_iteration = 0;
    this->intervals = std::vector<double>(this->N_intervals+1);
    double dx = 1.0 / this->N_intervals;
    this->dx_i = std::vector<double>(this->N_intervals, dx);
    for (int i = 0; i <= this->N_intervals; i++) {
        this->intervals[i] = dx * i;
    }
    this->sample_points();
    this->calculate_integral(integrand);
    this->calculate_erros();
    for(int i=1; i<=this->max_iterations; i++) {
        //std::cout << "test2" << std::endl;
        this->i_iteration = i;
        this->calculate_mi(integrand);
        this->alter_intervals();
        this->sample_points();
        this->calculate_integral(integrand);
        this->calculate_erros();
        std::cout << "test1" << std::endl;
        /* if(Math::abs(this->sigma_iterations[i] - this->sigma_iterations[i-1]) < this->delta_sigma_break) {
            break;
        } */
    }
}

double Malta::integrate(double (*integrand)(double), double lower_limit, double upper_limit) {
    /*auto new_integrand = [lower_limit, upper_limit, integrand](double x) {
        return integrand(x * (upper_limit - lower_limit) + lower_limit) * (upper_limit-lower_limit);
    };*/
    //return this->integrate(new_integrand);
}

void Malta::calculate_mi(double (*integrand)(double)) {
    std::vector<double> fi(this->N_intervals, 0.0);
    this->mi = std::vector<int>(this->N_intervals);
    this->mi_width = std::vector<double>(this->N_intervals);
    int interval_ix = 0;
    // assuminig points semi-sorted up to intervals
    for(int i=0; i<this->N_points; i++) {
        if(this->points[i] >= this->intervals[interval_ix+1]) {
            interval_ix++;
        }
        double integrand_val = integrand(this->points[i]);
        fi[interval_ix] += Math::abs(integrand_val);
    }
    double norm_factor = 0.0;
    for(int i=0; i<this->N_intervals; i++) {
        norm_factor += fi[i] * this->dx_i[i];
    }
    for(int i=0; i<this->N_intervals; i++) {
        this->mi[i] = 1 + (int) this->K * fi[i] * dx_i[i] / norm_factor;
        this->mi_width[i] = this->dx_i[i] / this->mi[i];
    }
}

void Malta::alter_intervals() {
    int all_subintervals = std::accumulate(this->mi.begin(), this->mi.end(), 0);
    int new_N_subintervals = (int) all_subintervals / this->N_intervals;
    int N_remaining_subintervals = all_subintervals - new_N_subintervals * this->N_intervals;
    /* todo:
     - allocate N_remaining_subintervals
     - optimize new interval calculation: don't iterate over all subintervals
     */
    double new_dx = 0.0;
    int interval_ix = 0;
    int mi_index = 0;
    for(int i=0; i<all_subintervals; i++) {
        new_dx += this->mi_width[mi_index];
        if(i>=mi[interval_ix]) mi_index++;
        if(i % new_N_subintervals == 0 && i != 0) {
            this->dx_i[interval_ix] = new_dx;
            interval_ix++;
            this->intervals[interval_ix+1] = this->intervals[interval_ix] + new_dx; 
            new_dx = 0.0;
        }
    }
}

void Malta::calculate_integral(double (*integrand)(double)) {
    double I = 0.0;
    this->S_2 = 0.0;
    for (int i = 0; i < this->N_points; i++) {
        double val = integrand(this->points[i]) / this->p(this->points[i]);
        //std::cout << "not" ? val == 0.0 : this->points[i] << std::endl;
        I += val;
        S_2 += val * val;
    }
    this->S_2 /= (double) this->N_points;
    std::cout << "integral: " << I / (double) this->N_points << std::endl;
    this->integral_iterations.push_back(I / (double) this->N_points);
}

double Malta::p(double x) {
    for(int i=0; i<this->N_intervals; i++) {
        if(x >= this->intervals[i] && x <= this->intervals[i+1]) {
            return 1.0 / (this->dx_i[i] * this->N_intervals);
        }    
    }
}

void Malta::calculate_erros() {
    double sigma_sq = (this->S_2 - this->integral_iterations[this->i_iteration]) / (this->N_points - 1);
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
    /* std::cout << "sigma_iterations: " << sigma_sq << std::endl;
    std::cout << "result: " << result << std::endl;
    std::cout << "sigma_result: " << sigma_res << std::endl; */
    if (this->i_iteration == 0) return;
    double chi_2 = 0.0;
    for(int i=0; i<=this->i_iteration; i++) {
        chi_2 += std::pow(this->integral_iterations[i]-result, 2)/this->sigma_iterations[i];
    }
    chi_2 /= this->i_iteration;
    this->chi_2_dof.push_back(chi_2);
    std::cout << "chi_2: " << chi_2 << std::endl;
}

void Malta::sample_points() {
    this->points = std::vector<double>(this->N_points);
    std::vector<int>* interval_ixs = Math::get_random_points(1, this->N_intervals, this->N_points);
    std::sort(interval_ixs->begin(), interval_ixs->end());
    int i=0;
    for(auto &ix : *interval_ixs) {
        double interval_lower = this->intervals[ix-1];
        double interval_upper = this->intervals[ix];
        double point = Math::get_random_point(interval_lower, interval_upper);
        //std::cout << "point" << point << std::endl;
        //std::cout << ix << std::endl;
        this->points[i] = point;
        i++;
    }
    delete interval_ixs;
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