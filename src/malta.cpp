#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "malta.h"
#include "malta_math.h"

Malta::Malta(int N_points, int N_intervals, int max_iterations) : 
N_points{N_points},
N_intervals{N_intervals},
max_iterations{max_iterations} {
    srand(time(NULL));
}

Malta::~Malta() {
    // Destructor
}

double Malta::integrate(IntgFn integrand) {
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
        this->i_iteration = i;
        this->calculate_mi(integrand);
        this->alter_intervals();
        this->sample_points();
        this->calculate_integral(integrand);
        this->calculate_erros();
        std::cout << "it=" << i << "; X^2/dof: " << this->chi_2_dof[i-1] << "; I=" << this->integral_result[i] << std::endl;
        if(Math::abs(this->sigma_iterations[i] - this->sigma_iterations[i-1]) < this->delta_sigma_break) {
            //break;
        }
    }
}

double Malta::integrate(IntgFn integrand, double lower_limit, double upper_limit) {
    return integrate([integrand, lower_limit, upper_limit](double x) -> double {
        return integrand(x * (upper_limit - lower_limit) + lower_limit) * (upper_limit-lower_limit);
    });
}

void Malta::calculate_mi(IntgFn integrand) {
    std::vector<double> fi(this->N_intervals, 0.0);
    this->mi = std::vector<double>(this->N_intervals);
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
    double damping_factor = 1.42;
    for(int i=0; i<this->N_intervals; i++) {
        double mi = fi[i] * dx_i[i] / norm_factor;
        this->mi[i] = std::pow((mi-1)/std::log(mi+1e-8), damping_factor);
        this->mi_width[i] = this->dx_i[i] / this->mi[i];

    }
}

void Malta::alter_intervals() {
    double avg_mi = std::accumulate(this->mi.begin(), this->mi.end(), 0.0) / (double) this->N_intervals;
    std::vector<double> new_intervals(this->N_intervals+1, this->intervals[this->N_intervals]);
    new_intervals[0] = this->intervals[0];
    double delta = 0.0;
    int i_intv = 1;
    for(int i=0; i<this->N_intervals; i++) {
        delta += this->mi[i];
        while (delta >= avg_mi) {
            if(i_intv>this->N_intervals-1) break;
            delta -= avg_mi;
            double new_interval = this->intervals[i+1] - (this->dx_i[i] * delta / this->mi[i]);
            new_intervals[i_intv] = new_interval;
            i_intv++;
        }
    }
    for(int i=0; i<this->N_intervals; i++) {
        this->dx_i[i] = new_intervals[i+1] - new_intervals[i];
        this->intervals[i+1] = new_intervals[i+1];
    }
}

void Malta::calculate_integral(IntgFn integrand) {
    double I = 0.0;
    this->S_2 = 0.0;
    for (int i = 0; i < this->N_points; i++) {
        double val = integrand(this->points[i]) / this->p(this->points[i]);
        I += val;
        S_2 += val * val;
    }
    this->S_2 /= (double) this->N_points;
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
    if (this->i_iteration == 0) return;
    double chi_2 = 0.0;
    for(int i=0; i<=this->i_iteration; i++) {
        chi_2 += std::pow(this->integral_iterations[i]-result, 2)/this->sigma_iterations[i];
    }
    chi_2 /= this->i_iteration;
    this->chi_2_dof.push_back(chi_2);
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