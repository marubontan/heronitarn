#include "components/data.h"
#include "components/helpers.h"
#include "random"

double urand(int ceil_number) {
    std::mt19937 mt{std::random_device{}()};
    std::uniform_real_distribution<> dist(0.0, static_cast<double>(ceil_number));
    return dist(mt);
}
double calculate_euclidean_distance(DataPoint data_point_1,
                                    DataPoint data_point_2) {
    int data_size = data_point_1.size();
    double value_sum = 0.0;
    for (auto i = 0; i < data_size; i++) {
        value_sum += std::pow(data_point_1[i] - data_point_2[i], 2);
    }
    return std::sqrt(value_sum);
}
