#ifndef MATH_H
#define MATH_H

#include <vector>
class Math {
    public:
        std::vector<int> static *get_random_points(int lower_limit, int upper_limit, int N);
        std::vector<double> static *get_random_points(double lower_limit, double upper_limit, int N);
        double static get_random_point(double lower_limit, double upper_limit);
        int static get_random_point(int lower_limit, int upper_limit);
        double static abs(double x);
};

#endif