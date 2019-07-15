#include "gtest/gtest.h"
#include "components/data.h"
#include "components/distances.cpp"

TEST(Distances, Euclidean) {
    DataPoint data_point_1{0.0, 0.0};
    DataPoint data_point_2{3.0, 4.0};

    auto actual = euclidean(data_point_1, data_point_2);
    auto expected = 5.0;

    ASSERT_EQ(actual, expected);
}


TEST(Distances, Manhattan) {
    DataPoint data_point_1{0.0, 0.0};
    DataPoint data_point_2{1.0, 2.0};

    auto actual = manhattan(data_point_1, data_point_2);
    auto expected = 3.0;

    ASSERT_EQ(actual, expected);
}

TEST(Distances, Chebyshev){
    DataPoint data_point_1{0.0,0.0};
    DataPoint data_point_2{1.0,2.0};

    auto actual = chebyshev(data_point_1, data_point_2);
    auto expected = 2.0;

    ASSERT_EQ(actual, expected);
}