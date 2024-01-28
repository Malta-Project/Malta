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
    this->sigma_iterations = vec1d();
    this->integral_iterations = vec1d();
    this->sigma_result = vec1d();
    this->integral_result = vec1d();
    this->chi_2_dof = vec1d();
    this->i_iteration = 0;
    this->intervals = vec2d(this->dimensions, vec1d(this->N_intervals+1));
    this->function_values = vec1d(this->N_points);
    this->p_x = vec1d(this->N_points);
    this->p_ij_inv = vec2d(this->dimensions, vec1d(this->N_points));
    this->points_x = vec2d(this->N_points, vec1d(this->dimensions));
    this->m_ij = vec2d(this->dimensions, vec1d(this->N_intervals));
    this->avg_m_ij = vec1d(this->dimensions);
    double dx = 1.0 / this->N_intervals;
    this->dx_ij = vec2d(this->dimensions, vec1d(this->N_intervals, dx));
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
        this->calculate_mij();
        this->alter_intervals();
        this->sample_points(integrand);
        this->calculate_integral();
        this->calculate_errors();
        std::cout << "it=" << i << "; X^2/dof: " << this->chi_2_dof[i-1] << "; std=" << this->sigma_iterations[i] << "; I=" << this->integral_result[i] << std::endl;
    }
    return Malta::get_result();
}

double Malta::integrate(IntgFn integrand, std::vector<std::pair<double, double>> limits) {
    return integrate([integrand, limits](std::vector<double> x) -> double {
        std::vector<double> new_x;
        double factor = 1.0;
        for (size_t i = 0; i < x.size(); ++i) {
            double a = limits[i].first;
            double b = limits[i].second;
            new_x.push_back(x[i] * (b - a) + a);
            factor *= (b - a);
        }
        return integrand(new_x) * factor;
    });
}


void Malta::calculate_mij() {
    vec2d f_ij(this->dimensions, vec1d(this->N_intervals));
    std::vector<int> selected_points = std::vector<int>();
    double sum_1, prd_2, sum_3, sum_4, norm_val, m_ij, avg_m_ij;
    for(int i=0; i<this->dimensions; i++) {
        for(int j=0; j<this->N_intervals; j++) {
            selected_points.clear();
            for(int k=0; k<this->N_points; k++) {
                if(this->points_x[k][i] < this->intervals[i][j+1] && this->points_x[k][i] >= this->intervals[i][j]) {
                    selected_points.push_back(k);
                }
            }
            sum_1 = 0;
            for(auto &k : selected_points) {
                sum_4 = 0;
                for(int l=0; l<this->dimensions; l++) {
                    sum_4 += this->p_ij_inv[l][k] * this->p_ij_inv[l][k];
                }
                sum_1 += this->function_values[k] * this->function_values[k] / sum_4;
            }
            prd_2 = 1;
            for(int l=0; l<this->dimensions; l++) {
                sum_3 = 0;
                for(auto &k : selected_points) {
                    sum_3 += this->p_ij_inv[l][k] * this->p_ij_inv[l][k];
                }
                prd_2 *= sum_3;
            }
            sum_1 *= prd_2;
            f_ij[i][j] = std::sqrt(sum_1);
        }
        norm_val = 0;
        for(int j=0; j<this->N_intervals; j++) {
            norm_val += f_ij[i][j] * this->dx_ij[i][j];
        }
        avg_m_ij = 0;
        for(int j=0; j<this->N_intervals; j++) {
            m_ij = f_ij[i][j] * this->dx_ij[i][j] / norm_val;
            m_ij = std::pow((m_ij-1)/std::log(m_ij+1e-8), 1.42);
            this->m_ij[i][j] = m_ij;
            avg_m_ij += m_ij;
        }
        this->avg_m_ij[i] = avg_m_ij / (double) this->N_intervals;
    }
}

void Malta::alter_intervals() {
    double delta;
    int i_intv;
    vec2d new_intervals(this->dimensions, vec1d(this->N_intervals+1));
    for(int d=0; d<this->dimensions; d++) {
        new_intervals[d][0] = this->intervals[d][0];
        new_intervals[d][this->N_intervals] = this->intervals[d][this->N_intervals];
        delta = 0.0;
        i_intv = 1;
        for(int i=0; i<this->N_intervals; i++) {
            delta += this->m_ij[d][i];
            while (delta >= this->avg_m_ij[d]) {
                if(i_intv>this->N_intervals-1) break;
                delta -= this->avg_m_ij[d];
                double new_interval = this->intervals[d][i+1] - (this->dx_ij[d][i] * delta / this->m_ij[d][i]);
                new_intervals[d][i_intv] = new_interval;
                i_intv++;
            }
        }
        for(int i=0; i<this->N_intervals; i++) {
            this->dx_ij[d][i] = new_intervals[d][i+1] - new_intervals[d][i];
            this->intervals[d][i+1] = new_intervals[d][i+1];
        }
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
    std::vector<int> *interval_ixs = new std::vector<int>(this->dimensions);
    double p_x;
    for(int i=0; i<this->N_points; i++) {
        p_x = 1;
        interval_ixs = Math::get_random_points(0, this->N_intervals-1, this->dimensions);
        for(int j=0; j<this->dimensions; j++) {
            interval_ix = (*interval_ixs)[j];
            this->p_ij_inv[j][i] = this->N_intervals * this->dx_ij[j][interval_ix];
            p_x /= this->p_ij_inv[j][i];
            this->points_x[i][j] = Math::get_random_point(this->intervals[j][interval_ix], this->intervals[j][interval_ix+1]);
        }
        this->p_x[i] = p_x;
        y = integrand(points_x[i]);
        this->function_values[i] = y;
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