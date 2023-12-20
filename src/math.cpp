#include "malta_math.h"
#include <cstdlib>

std::vector<int> *Math::get_random_points(int lower_limit, int upper_limit, int N) { //limts inclusive
    std::vector<int>* random_numbers = new std::vector<int>(N);
    for (int i = 0; i < N; i++) {
        (*random_numbers)[i] = rand() % (upper_limit - lower_limit + 1) + lower_limit;
    }
    return random_numbers;
}

std::vector<double> *Math::get_random_points(double lower_limit, double upper_limit, int N) {
    std::vector<double>* random_numbers = new std::vector<double>(N);
    for (int i = 0; i < N; i++) {
        (*random_numbers)[i] = ((double) rand()) / RAND_MAX * (upper_limit - lower_limit) + lower_limit;
    }
    return random_numbers;
}

double Math::get_random_point(double lower_limit, double upper_limit) {
    return ((double) rand()) / RAND_MAX * (upper_limit - lower_limit) + lower_limit;
}

double Math::abs(double x) {
    return x < 0 ? -x : x;
}