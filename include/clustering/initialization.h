#include "components/data.h"
#include "kmeans.hpp"
#include <vector>
typedef std::vector<double> DistanceToNearestCentroid;
typedef DistanceToNearestCentroid PickUpProbabilities;

Centroids kmeans_plus_plus(Data data, K k);
PickUpProbabilities calculate_pick_up_probability_by_distance(DistanceToNearestCentroid distance_to_nearest_centroid);
int pick_up_one_data_point_with_probability(DistanceToNearestCentroid distance_to_nearest_centroid);
