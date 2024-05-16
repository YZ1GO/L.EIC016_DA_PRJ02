#ifndef FEUP_DA_02_TSP_H
#define FEUP_DA_02_TSP_H

#include "DataParser.h"
#include <stack>
#define INF std::numeric_limits<double>::max()

class TSP {
private:
    Graph<int> tspGraph;

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
};


#endif //FEUP_DA_02_TSP_H
