#ifndef MALTA_H
#define MALTA_H

#include <vector>
#include <functional>

using IntgFn = std::function<double(double)>;
class Malta {
    public:
        Malta(int N_points, int N_intervals, int max_iterations);
        ~Malta();
        double integrate(IntgFn integrand);
        double integrate(IntgFn integrand, double lower_limit, double upper_limit);
        void set_N_intervals(int N_intervals);
        int get_N_intervals();
        void set_N_points(int N_points);
        int get_N_points();
        void set_seed(int seed);
        double get_results();
    private:
        int N_intervals;
        int N_points;
        int i_iteration;
        int max_iterations;
        double S_2;
        double delta_sigma_break = 1e-6;
        std::vector<double> intervals;
        std::vector<double> points;
        std::vector<double> dx_i;
        std::vector<double> sigma_iterations;
        std::vector<double> integral_iterations;
        std::vector<double> sigma_result;
        std::vector<double> integral_result;
        std::vector<double> chi_2_dof;
        std::vector<double> mi;
        std::vector<double> mi_width;
        void sample_points();
        void calculate_integral(IntgFn);
        double p(double x);
        void calculate_erros();
        void calculate_mi(IntgFn);
        void alter_intervals();
};

#endif