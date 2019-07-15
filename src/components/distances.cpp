#include "components/data.h"
#include <cmath>


double euclidean(DataPoint data_point_1, DataPoint data_point_2) {
    int data_size = data_point_1.size();
    double value_sum = 0.0;
    for (auto i = 0; i < data_size; i++) {
        value_sum += std::pow(data_point_1[i] - data_point_2[i], 2);
    }
    return std::sqrt(value_sum);
}

double manhattan(DataPoint data_point_1, DataPoint data_point_2) {
    int data_size = data_point_1.size();
    double value_sum = 0.0;
    for (auto i = 0; i < data_size; i++) {
        value_sum += std::abs(data_point_1[i] - data_point_2[i]);
    }
    return value_sum;
}

double chebyshev(DataPoint data_point_1, DataPoint data_point_2) {
    int data_size = data_point_1.size();
    double max_difference = 0.0;
    double value_difference;
    for (auto i = 0; i < data_size; i++) {
        value_difference = std::abs(data_point_1[i] - data_point_2[i]);
        if (max_difference < value_difference) {
            max_difference = value_difference;
        }
    }
    return max_difference;
}
