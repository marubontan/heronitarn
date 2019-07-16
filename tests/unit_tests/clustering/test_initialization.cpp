#include "gtest/gtest.h"
#include "clustering/initialization.h"

TEST(Initialization, CalculatePickUpProbabilityByDistance) {
    DistanceToNearestCentroid distance_to_nearest_centroid{1.0, 4.0};
    auto actual = calculate_pick_up_probability_by_distance(distance_to_nearest_centroid);
    auto expected = PickUpProbabilities{0.2, 0.8};
    ASSERT_EQ(expected, actual);
}
