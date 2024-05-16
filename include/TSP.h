/**
 * @file TSP.h
 * @brief Contains the declaration of the TSP class.
 *
 * This header file contains the declaration of the TSP class which is responsible for solving the Travelling Salesman Problem.
 */

#ifndef FEUP_DA_02_TSP_H
#define FEUP_DA_02_TSP_H

#include "DataParser.h"
#define DOUBLE_INF std::numeric_limits<double>::max()
#define LONG_LONG_INF std::numeric_limits<long long>::max()
#define MAX_ITERATIONS 5

/***
 * @class TSP
 * @brief Solves the Travelling Salesman Problem.
 */
class TSP {
private:
    /***
     * @brief Graph to perform the TSP on.
     */
    Graph<int> tspGraph;
    std::vector<std::vector<double>> pheromones;
    double alpha = 1.0;
    double beta = 5.0;
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

    static std::vector<Vertex<int>*> applyThreeOptSwap(const std::vector<Vertex<int>*>& path, int i, int j, int k);

    void initializePheromones(double initialPheromoneLevel);
    static double calculateHeuristic(Vertex<int>* s, Vertex<int>* t);
    std::vector<Vertex<int>*> constructSolution(Vertex<int>* start);
    void updatePheromones(const std::vector<std::vector<Vertex<int>*>>& allTours, const std::vector<long long>& distances);

public:
    TSP();
    explicit TSP(const Graph<int> &graph);
    Graph<int> getTspGraph();

    void backtrackingAlgorithm();
    void heldKarp(const int& origin);
    void triangularApproximationMSTAlgorithm(int origin, bool fullyConnected);
    void nearestNeighborAlgorithm(const int& origin);
    void kNearestNeighborAlgorithm(const int& origin, int k);
    void twoOptAlgorithm(const int& origin);
    void threeOptAlgorithm(const int& origin);
    
    //std::vector<std::vector<Vertex<int>*>> kMeansClustering(int k);

    void antColonyOptimization(const int& origin, int numAnts, int numIterations, bool fullyConnected);
};


#endif //FEUP_DA_02_TSP_H
