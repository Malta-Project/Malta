#ifndef MALTA_H
#define MALTA_H

#include <vector>
#include <functional>

using IntgFn = std::function<double(std::vector<double>)>;
class Malta {
    public:
        Malta(int dimensions, int N_points, int N_intervals, int max_iterations);
        double integrate(IntgFn integrand);
        double integrate(IntgFn integrand, std::vector<std::pair<double, double>> limits);
        void set_N_intervals(int N_intervals);
        int get_N_intervals();
        void set_N_points(int N_points);
        int get_N_points();
        void set_seed(int seed);
        double get_result();
        double get_error();
    private:
        int dimensions;
        int N_intervals;
        int N_points;
        int i_iteration;
        int max_iterations;
        double S_2;
        double delta_sigma_break = 1e-6;
        double avg_mi;
        std::vector<std::vector<double>> intervals;
        std::vector<std::vector<double>> dx_ij;
        std::vector<double> sigma_iterations;
        std::vector<double> integral_iterations;
        std::vector<double> sigma_result;
        std::vector<double> integral_result;
        std::vector<double> chi_2_dof;
        std::vector<double> mi;
        std::vector<double> mi_width;
        std::vector<double> function_values;
        std::vector<double> function_values_sq;
        std::vector<double> function_values_abs;
        std::vector<double> p_x;
        void sample_points(IntgFn integrand);
        void calculate_integral();
        void calculate_errors();
        void calculate_mi();
        void alter_intervals();
};

#endif