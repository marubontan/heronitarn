#include "gtest/gtest.h"
#include "clustering/initialization.h"
#include "components/helpers.h"

TEST(Initialization, CalculatePickUpProbabilityByDistance) {
    DistanceToNearestCentroid distance_to_nearest_centroid{1.0, 4.0};
    auto actual = calculate_pick_up_probability_by_distance(distance_to_nearest_centroid);
    auto expected = PickUpProbabilities{0.2, 0.8};
    ASSERT_EQ(expected, actual);
}

TEST(Initialization, PickUpOneDataPointWithProbability) {
    PickUpProbabilities pick_up_probability{0.2, 0.8};
    auto actual = pick_up_one_data_point_with_probability(pick_up_probability);
    ASSERT_TRUE(actual == 0 | actual == 1);
}

TEST(Initialization, KmeansPlusPlus) {
    DataPoint data_point_1{1.0, 1.0};
    DataPoint data_point_2{2.0, 2.0};
    DataPoint data_point_3{3.0, 3.0};
    Data data{data_point_1, data_point_2, data_point_3};
    int k = 2;
    auto actual = kmeans_plus_plus(data, k, calculate_euclidean_distance);
    ASSERT_TRUE(actual.size() == k);
    ASSERT_TRUE(actual[0] == data_point_1 | actual[0] == data_point_2 | actual[0] == data_point_3);
    ASSERT_TRUE(actual[1] == data_point_1 | actual[1] == data_point_2 | actual[1] == data_point_3);

}