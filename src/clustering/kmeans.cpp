#include "clustering/kmeans.hpp"
#include "components/helpers.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <iostream>


DataBelonging get_group_belonging(Data data,
                                  Centroids centroids,
                                  double (&dist_fn)(DataPoint, DataPoint)) {

    int centroid_number = centroids.size();
    DataBelonging data_belonging(data.size());
    double distance_to_centroid;
    for (auto d = 0; d < data.size(); d++) {
        int nearest_centroid_index = 0;
        double distance_to_nearest_centroid = dist_fn(data[d], centroids[0]);
        for (auto i = 1; i < centroid_number; i++) {
            distance_to_centroid = dist_fn(data[d], centroids[i]);
            if (distance_to_nearest_centroid > distance_to_centroid) {
                distance_to_nearest_centroid = distance_to_centroid;
                nearest_centroid_index = i;
            }
        }
        data_belonging[d] = nearest_centroid_index;
    }

    return data_belonging;
}

ClusterIndices get_specific_cluster_indices(DataBelonging data_belonging,
                                            int cluster_number) {
    std::vector<int> cluster_indices;
    for (auto i = 0; i < data_belonging.size(); i++) {
        if (data_belonging[i] == cluster_number) {
            cluster_indices.push_back(i);
        }
    }
    return cluster_indices;
}

Centroid get_new_cluster_centroid(Data data,
                                  const ClusterIndices &cluster_belonging_data_indices) {

    Centroid new_centroid(data[0].size(), 0);
    int cluster_indices_size = cluster_belonging_data_indices.size();
    for (auto &cluster_belonging_index: cluster_belonging_data_indices) {
        for (auto i = 0; i < new_centroid.size(); i++) {
            new_centroid[i] += data[cluster_belonging_index][i];
        }
    }

    for (auto &new_centroid_factor: new_centroid) {
        new_centroid_factor /= cluster_indices_size;
    }
    return new_centroid;
}

Centroids get_new_centroids(Data data,
                            const DataBelonging &data_belonging, int k) {

    Centroids centroids(k, Centroid(data[0].size()));
    for (auto i = 0; i < k; i++) {
        auto cluster_belonging_data_indices = get_specific_cluster_indices(data_belonging, i);
        centroids[i] = get_new_cluster_centroid(data, cluster_belonging_data_indices);
    }
    return centroids;
}


DataBelonging get_random_belonging(Data data, K k) {
    int data_size = data.size();
    DataBelonging data_belonging(data_size, 0);
    for (auto &d : data_belonging) {
        d = urand(k);
    }
    return data_belonging;
}

bool is_convergence_example(const Data data,
                            K k,
                            const CentroidsHistory centroid_history,
                            DataBelongingHistory data_belonging_history) {
    auto data_belonging_history_size = data_belonging_history.size();
    if (data_belonging_history_size < 2) {
        return false;
    }
    return data_belonging_history[data_belonging_history_size - 1] ==
           data_belonging_history[data_belonging_history_size - 2];

}

Centroids initialize_centroids_example(Data data, int k) {
    auto data_belonging = get_random_belonging(data, k);
    auto centroids = get_new_centroids(data, data_belonging, k);

    return centroids;
}


KMeansResult k_means(const Data &data,
                     int k,
                     Centroids (&initialize_centroids)(Data, int),
                     double (&dist_fn)(DataPoint, DataPoint),
                     bool (&is_converge)(const Data, K, const CentroidsHistory, DataBelongingHistory)) {

    DataBelonging data_belonging;
    CentroidsHistory centroids_history;
    DataBelongingHistory data_belonging_history;

    auto centroids = initialize_centroids(data, k);
    centroids_history.push_back(centroids);
    while (!is_converge(data, k, centroids_history, data_belonging_history)) {
        data_belonging = get_group_belonging(data, centroids, dist_fn);
        centroids = get_new_centroids(data, data_belonging, k);
        centroids_history.push_back(centroids);
        data_belonging_history.push_back(data_belonging);
    }
    KMeansResult k_means_result{data, centroids_history, data_belonging_history};
    return k_means_result;
}
