#ifndef MALTA_MATH_H
#define MALTA_MATH_H

#include <vector>
class Math {
    public:
        std::vector<int> static *get_random_points(int lower_limit, int upper_limit, int N);
        std::vector<double> static *get_random_points(double lower_limit, double upper_limit, int N);
        double static get_random_point(double lower_limit, double upper_limit);
        int static get_random_point(int lower_limit, int upper_limit);
        double static abs(double x);
        double static max(double x, double y);
        double static min(double x, double y);
        int static max(int x, int y);
        int static min(int x, int y);
};

#endif