#ifndef MALTA_H
#define MALTA_H

#include <vector>
#include <functional>

using IntgFn = std::function<double(std::vector<double>)>;
using vec2d = std::vector<std::vector<double>>;
using vec1d = std::vector<double>;
class Malta {
    public:
        Malta(int dimensions, int N_points, int N_intervals, int max_iterations, bool log=true);
        double integrate(IntgFn integrand);
        double integrate(IntgFn integrand, std::vector<std::pair<double, double>> limits);
        void set_N_intervals(int N_intervals);
        int get_N_intervals();
        void set_N_points(int N_points);
        int get_N_points();
        void set_seed(int seed);
        double get_result();
        double get_error();
        double get_integration_time_ms();
    private:
        bool log;
        int dimensions;
        int N_intervals;
        int N_points;
        int i_iteration;
        int max_iterations;
        double S_2;
        double delta_sigma_break = 1e-6;
        double integration_time_ms;
        vec1d avg_m_ij;
        vec2d intervals;
        vec2d dx_ij;
        vec1d sigma_iterations;
        vec1d integral_iterations;
        vec1d sigma_result;
        vec1d integral_result;
        vec1d chi_2_dof;
        vec2d m_ij;
        vec1d function_values;
        vec1d p_x;
        vec2d p_ij_inv;
        vec2d points_x;
        void sample_points(IntgFn integrand);
        void calculate_integral();
        void calculate_errors();
        void calculate_mij();
        void alter_intervals();
};

#endif