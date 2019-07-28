#include "clustering/initialization.h"
#include "components/helpers.h"
#include <cmath>

PickUpProbabilities calculate_pick_up_probability_by_distance(DistanceToNearestCentroid distance_to_nearest_centroid) {
    auto distance_sum = 0.0;
    for (auto distance : distance_to_nearest_centroid) {
        distance_sum += distance;
    }

    for (auto &distance : distance_to_nearest_centroid) {
        distance /= distance_sum;
    }
    return PickUpProbabilities(distance_to_nearest_centroid);
}

int pick_up_one_data_point_with_probability(PickUpProbabilities pick_up_probabilities) {
    auto random_float = urand(1);

    double cum_sum = 0.0;
    for (int i = 0; i < pick_up_probabilities.size(); i++) {
        cum_sum += pick_up_probabilities[i];
        if (random_float <= cum_sum) {
            return i;
        }
    }
}

Centroids kmeans_plus_plus(Data data,
                           K k,
                           double (&dist_fn)(DataPoint, DataPoint)) {
    Centroid first_centroid = data[static_cast<int>(floor(urand(data.size())))];
    Centroid latest_centroid = first_centroid;
    DistanceToNearestCentroid distance_to_nearest_centroid(data.size(), 0.0);
    Centroids centroids(k);
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < data.size(); j++) {
            auto distance_between_latest_centroid_and_data_point = calculate_euclidean_distance(latest_centroid,
                                                                                                data[j]);
            if (distance_between_latest_centroid_and_data_point < distance_to_nearest_centroid[j]) {
                distance_to_nearest_centroid[j] = distance_between_latest_centroid_and_data_point;
            }
        }
        PickUpProbabilities pick_up_probabilities = calculate_pick_up_probability_by_distance(
                distance_to_nearest_centroid);
        int new_centroid_index = pick_up_one_data_point_with_probability(pick_up_probabilities);
        latest_centroid = data[new_centroid_index];
        centroids[i] = latest_centroid;
    }
    return centroids;
}