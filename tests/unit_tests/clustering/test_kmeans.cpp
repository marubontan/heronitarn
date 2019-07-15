#include "gtest/gtest.h"
#include "clustering/kmeans.cpp"

#include <vector>


TEST(Kmeans, UpdateGroupBelonging) {
    Data data{{1.0, 2.0, 3.0},
              {4.0, 5.0, 6.0}};
    Data centroids{{1.2, 2.1, 3.1},
                   {3.9, 5.1, 6.1}};
    auto actual = get_group_belonging(data, centroids, calculate_euclidean_distance);
    DataBelonging expected{0, 1};
    EXPECT_EQ(actual, expected);

}

TEST(Kmeans, CalculateEuclideanDistance) {
    DataPoint data_1{0.0, 0.0};
    DataPoint data_2{3.0, 4.0};

    auto actual = calculate_euclidean_distance(data_1, data_2);
    auto expected = 5.0;
    ASSERT_EQ(actual, expected);
}

TEST(Kmeans, GetSpecificClusterIndices) {
    DataBelonging data_belonging{0, 0, 1, 1};
    auto cluster_number = 0;

    auto actual = get_specific_cluster_indices(data_belonging, cluster_number);
    auto expected = ClusterIndices{0, 1};

    ASSERT_EQ(actual, expected);
}

TEST(Kmeans, GetNewClusterCentroid) {
    Data data{{0.0, 1.0},
              {2.0, 3.0}};
    ClusterIndices cluster_indices{0, 1};

    auto actual = get_new_cluster_centroid(data, cluster_indices);
    Centroid expected = {1.0, 2.0};

    ASSERT_EQ(actual, expected);
}

TEST(Kmeans, GetNewCentroids) {
    DataPoint data_point_1{0.0, 2.0};
    DataPoint data_point_2{0.0, 4.0};
    DataPoint data_point_3{2.0, 4.0};
    DataPoint data_point_4{2.0, 6.0};

    Data data{data_point_1, data_point_2, data_point_3, data_point_4};
    DataBelonging data_belonging{0, 0, 1, 1};

    auto actual = get_new_centroids(data, data_belonging, 2);
    Centroids expected{{0.0, 3.0},
                       {2.0, 5.0}};

    ASSERT_EQ(actual, expected);

}

TEST(Kmeans, IsConvergenceExample) {
    DataPoint data_point_1{0.0, 2.0};
    DataPoint data_point_2{0.0, 4.0};
    DataPoint data_point_3{2.0, 4.0};
    DataPoint data_point_4{2.0, 6.0};

    Data data{data_point_1, data_point_2, data_point_3, data_point_4};
    int k = 2;
    Centroid centroid_1{1.0, 2.0};
    Centroid centroid_2{1.0, 2.0};

    CentroidsHistory centroids_history{Centroids{centroid_1, centroid_2}, Centroids{centroid_1, centroid_2}};

    DataBelonging data_belonging_1{0, 1};
    DataBelonging data_belonging_2{0, 1};
    DataBelongingHistory data_belonging_history{data_belonging_1, data_belonging_2};

    auto actual = is_convergence_example(data,
                                         k,
                                         centroids_history,
                                         data_belonging_history);
    auto expected = true;

    ASSERT_EQ(actual, expected);
}