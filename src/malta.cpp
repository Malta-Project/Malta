#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "malta.h"
#include "malta_math.h"

Malta::Malta(int dimensions, int N_points, int N_intervals, int max_iterations) : 
dimensions{dimensions},
N_points{N_points},
N_intervals{N_intervals},
max_iterations{max_iterations} {
    srand(time(NULL));
}

double Malta::integrate(IntgFn integrand) {
    this->sigma_iterations = std::vector<double>();
    this->integral_iterations = std::vector<double>();
    this->sigma_result = std::vector<double>();
    this->integral_result = std::vector<double>();
    this->chi_2_dof = std::vector<double>();
    this->i_iteration = 0;
    this->intervals = std::vector<std::vector<double>>(this->dimensions, std::vector<double>(this->N_intervals+1));
    this->function_values = std::vector<double>(this->N_points);
    this->function_values_sq = std::vector<double>(this->N_points);
    this->function_values_abs = std::vector<double>(this->N_points);
    this->p_x = std::vector<double>(this->N_points);
    double dx = 1.0 / this->N_intervals;
    this->dx_ij = std::vector<std::vector<double>>(this->dimensions, std::vector<double>(this->N_intervals, dx));
    for (int i=0; i<this->dimensions; i++) {
        for(int j=0; j<=this->N_intervals; j++) {
            this->intervals[i][j] = dx * j;
        }
    }
    this->sample_points(integrand);
    this->calculate_integral();
    this->calculate_errors();
    for(int i=1; i<=this->max_iterations; i++) {
        this->i_iteration = i;
        this->calculate_mi();
        this->alter_intervals();
        this->sample_points(integrand);
        this->calculate_integral();
        this->calculate_errors();
        std::cout << "it=" << i << "; X^2/dof: " << this->chi_2_dof[i-1] << "; std=" << this->sigma_iterations[i] << "; I=" << this->integral_result[i] << std::endl;
        /* if(Math::abs(this->sigma_iterations[i] - this->sigma_iterations[i-1]) < this->delta_sigma_break) {
            break;
        } */
    }
}

double Malta::integrate(IntgFn integrand, std::vector<std::pair<double, double>> limits) {
    return integrate([integrand, limits](std::vector<double> x) -> double {
        return integrand({
            x[0] * (limits[0].second - limits[0].first) + limits[0].first
        }) * (limits[0].second-limits[0].first);
    });
}

void Malta::calculate_mi() {
    double total_weight = 0.0;
    this->mi = std::vector<double>(this->N_intervals);
    this->avg_mi = 0.0;
    for(int i=0; i<this->N_intervals; i++) {
        total_weight += this->function_values_abs[i] * this->dx_ij[0][i];
    }
    double mi;
    for(int i=0; i<this->N_intervals; i++) {
        mi = this->function_values_abs[i] * dx_ij[0][i] / total_weight;
        mi = std::pow((mi-1)/std::log(mi+1e-8), 1.42);
        this->avg_mi += mi;
        this->mi[i] = mi;

    }
    this->avg_mi /= (double) this->N_intervals;
}

void Malta::alter_intervals() {
    std::vector<std::vector<double>> new_intervals(this->dimensions, std::vector<double>(this->N_intervals+1, this->intervals[0][this->N_intervals]));
    new_intervals[0] = this->intervals[0];
    double delta = 0.0;
    int i_intv = 1;
    for(int i=0; i<this->N_intervals; i++) {
        delta += this->mi[i];
        while (delta >= this->avg_mi) {
            if(i_intv>this->N_intervals-1) break;
            delta -= this->avg_mi;
            double new_interval = this->intervals[0][i+1] - (this->dx_ij[0][i] * delta / this->mi[i]);
            new_intervals[0][i_intv] = new_interval;
            i_intv++;
        }
    }
    for(int i=0; i<this->N_intervals; i++) {
        this->dx_ij[0][i] = new_intervals[0][i+1] - new_intervals[0][i];
        this->intervals[0][i+1] = new_intervals[0][i+1];
    }
}

void Malta::calculate_integral() {
    double I = 0.0,
           val = 0.0;
    this->S_2 = 0.0;
    for(int i=0; i<this->N_points; i++) {
        val = this->function_values[i] / this->p_x[i];
        I += val;
        this->S_2 += val * val;
    }
    this->S_2 /= (double) this->N_points;
    this->integral_iterations.push_back(I / (double) this->N_points);
}

void Malta::calculate_errors() {
    double sigma_sq = (this->S_2 - std::pow(this->integral_iterations[this->i_iteration], 2)) / (this->N_points - 1);
    this->sigma_iterations.push_back(std::sqrt(sigma_sq));
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
        chi_2 += std::pow(this->integral_iterations[i]-result, 2)/sigma_sq;
    }
    chi_2 /= (this->i_iteration-1);
    this->chi_2_dof.push_back(chi_2);
}

void Malta::sample_points(IntgFn integrand) {
    double y;
    int interval_ix;
    std::fill(this->function_values.begin(), this->function_values.end(), 0.0);
    std::fill(this->function_values_sq.begin(), this->function_values_sq.end(), 0.0);
    std::fill(this->function_values_abs.begin(), this->function_values_abs.end(), 0.0);
    std::vector<int> *interval_ixs = new std::vector<int>(this->dimensions);
    std::vector<double> x(this->dimensions);
    double p_x;
    for(int i=0; i<this->N_points; i++) {
        p_x = 1;
        interval_ixs = Math::get_random_points(0, this->N_intervals-1, this->dimensions);
        for(int j=0; j<this->dimensions; j++) {
            interval_ix = (*interval_ixs)[j];
            p_x /= this->N_intervals * this->dx_ij[j][interval_ix];
            x[j] = Math::get_random_point(this->intervals[j][interval_ix], this->intervals[j][interval_ix+1]);
        }
        this->p_x[i] = p_x;
        y = integrand(x);
        this->function_values[i] += y;
        this->function_values_sq[i] += y*y;
        this->function_values_abs[i] += Math::abs(y);
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

double Malta::get_result() {
    return this->integral_iterations[this->i_iteration];
}

double Malta::get_error() {
    return this->sigma_result[this->i_iteration];
}