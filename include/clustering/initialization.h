#include "components/data.h"
#include <vector>

typedef std::vector<double> DistanceToNearestCentroid;
typedef DistanceToNearestCentroid PickUpProbabilities;

Centroids kmeans_plus_plus(Data data, K k, double (&dist_fn)(DataPoint, DataPoint));

PickUpProbabilities calculate_pick_up_probability_by_distance(DistanceToNearestCentroid distance_to_nearest_centroid);

int pick_up_one_data_point_with_probability(PickUpProbabilities pick_up_probabilities);

