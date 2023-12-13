#ifndef MALTA_H
#define MALTA_H

#include <vector>

class Malta {
    public:
        Malta(int N_points, int N_intervals, int max_iterations);
        ~Malta();
        double integrate(double (*integrand)(double));
        double integrate(double (*integrand)(double), double lower_limit, double upper_limit);
        void set_N_intervals(int N_intervals);
        int get_N_intervals();
        void set_N_points(int N_points);
        int get_N_points();
        void set_seed(int seed);
        double get_results();
        void set_K(int K);
        int get_K();
    private:
        int N_intervals;
        int N_points;
        int i_iteration;
        int max_iterations;
        int K = 1000;
        double S_2;
        double delta_sigma_break = 1e-3;
        std::vector<double> intervals;
        std::vector<double> points;
        std::vector<double> dx_i;
        std::vector<double> sigma_iterations;
        std::vector<double> integral_iterations;
        std::vector<double> sigma_result;
        std::vector<double> integral_result;
        std::vector<double> chi_2_dof;
        std::vector<int> mi;
        std::vector<double> mi_width;
        void sample_points();
        void calculate_integral(double (*integrand)(double));
        double p(double x);
        void calculate_erros();
        void calculate_mi(double (*integrand)(double));
        void alter_intervals();
};

#endif