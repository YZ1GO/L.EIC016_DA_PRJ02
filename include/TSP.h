#ifndef FEUP_DA_02_TSP_H
#define FEUP_DA_02_TSP_H

#include "DataParser.h"
#include <stack>
#define DOUBLE_INF std::numeric_limits<double>::max()
#define LONG_LONG_INF std::numeric_limits<long long>::max()

class TSP {
private:
    Graph<int> tspGraph;
    std::vector<std::vector<double>> pheromones;
    double alpha = 1.0;
    double beta = 2.0;
    double evaporationRate = 0.5;

    template <typename T>
    void printPath(T distance, const std::vector<Vertex<int>*> &path);
    void backtrackingAlgorithmAux(Vertex<int>* currVertex, double currDistance, std::vector<Vertex<int>*> &path, std::vector<bool> &visited, double &minDistance, std::vector<Vertex<int>*> &bestPath);


    static void dfsTraversal(Vertex<int>* current, std::vector<Vertex<int>*>& path);
    static void traverseMST(const Graph<int>& graph, Vertex<int>* start, std::vector<Vertex<int>*>& path);
    bool pathDistanceNotFullyConnected(const std::vector<Vertex<int>*>& path, long long& distance);
    long long pathDistanceFullyConnected(const std::vector<Vertex<int>*>& path);


    bool findPathToOrigin(Vertex<int>* origin, std::vector<Vertex<int>*>& tour);
    std::vector<Vertex<int>*> nearestNeighborPath(Vertex<int>* origin);
    std::vector<Vertex<int>*> kNearestNeighborPath(Vertex<int>* origin, int numNeighbors);

    void initializePheromones(double initialPheromoneLevel);
    double calculateHeuristic(Vertex<int>* s, Vertex<int>* t);
    std::vector<Vertex<int>*> constructSolution(Vertex<int>* start);
    void updatePheromones(const std::vector<std::vector<Vertex<int>*>>& allTours, const std::vector<long long>& distances);

public:
    TSP();
    explicit TSP(const Graph<int> &graph);
    Graph<int> getTspGraph();

    void backtrackingAlgorithm();
    void christofidesAlgorithm(int origin, bool fullyConnected);
    void heldKarp(const int& origin);
    void nearestNeighborAlgorithm(const int& origin);
    void kNearestNeighborAlgorithm(const int& origin, int k);
    void twoOptNearestNeighborAlgorithm(const int& origin);
    //std::vector<std::vector<Vertex<int>*>> kMeansClustering(int k);

    void antColonyOptimization(const int& origin, int numAnts, int numIterations);
};


#endif //FEUP_DA_02_TSP_H
