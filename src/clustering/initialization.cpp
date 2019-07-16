#include "clustering/initialization.h"

PickUpProbabilities calculate_pick_up_probability_by_distance(DistanceToNearestCentroid distance_to_nearest_centroid){
    auto distance_sum = 0.0;
    for (auto distance : distance_to_nearest_centroid){
        distance_sum += distance;
    }

    for (auto &distance : distance_to_nearest_centroid){
        distance /= distance_sum;
    }
    return PickUpProbabilities(distance_to_nearest_centroid);
}