//
// Created by Shuhei Kishi on 2019-07-06.
//

#include <vector>
#include "components/data.h"

typedef std::vector<int> DataBelonging;
typedef DataPoint Centroid;
typedef Data Centroids;
typedef std::vector<Centroids> CentroidsHistory;
typedef std::vector<DataBelonging> DataBelongingHistory;
typedef DataBelonging ClusterIndices;
typedef int K;

// Generalize data type by template
struct KMeansResult {
    Data data;
    CentroidsHistory centroid_history;
    DataBelongingHistory data_belonging_history;
};


KMeansResult k_means(const Data &data,
                     int k,
                     Centroids (&initialize_centroids)(Data, K),
                     double (&dist_fn)(DataPoint, DataPoint),
                     bool (&is_converge)(const Data, K, const CentroidsHistory, DataBelongingHistory));


DataBelonging get_group_belonging(Data data,
                                  Centroids centroids,
                                  double (&dist_fn)(DataPoint, DataPoint));

Centroids get_new_centroids(Data data, const DataBelonging &data_belonging, int k);

double calculate_euclidean_distance(DataPoint data_point_1,
                                    DataPoint data_point_2);


ClusterIndices get_specific_cluster_indices(DataBelonging data_belonging,
                                            int cluster_number);

Centroid get_new_cluster_centroid(Data data,
                                  const ClusterIndices &cluster_belonging_data_indices);

bool is_convergence_example(const Data data,
                            K k,
                            const CentroidsHistory centroid_history,
                            DataBelongingHistory data_belonging_history);

Centroids initialize_centroids_example(Data data, int k);

DataBelonging get_random_belonging(Data data, K k);

double urand(int ceil_number);
