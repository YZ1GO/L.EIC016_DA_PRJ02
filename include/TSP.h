#ifndef FEUP_DA_02_TSP_H
#define FEUP_DA_02_TSP_H

#include "DataParser.h"
#include <stack>
#define INF std::numeric_limits<double>::max()

class TSP {
private:
    Graph<int> tspGraph;

    void printPath(long long distance, const std::vector<Vertex<int>*> &path);
    void backtrackingAlgorithmAux(Vertex<int>* currVertex, double currDistance, std::vector<Vertex<int>*> &path, std::vector<bool> &visited, double &minDistance, std::vector<Vertex<int>*> &bestPath);

    /***  TRIANGULAR APPROXIMATION RELATED FUNCTIONS  ***/
    static void dfsTraversal(Vertex<int>* current, std::vector<Vertex<int>*>& path);
    static void traverseMST(const Graph<int>& graph, Vertex<int>* start, std::vector<Vertex<int>*>& path);
    bool pathDistanceNotFullyConnected(const std::vector<Vertex<int>*>& path, long long& distance);
    long long pathDistanceFullyConnected(const std::vector<Vertex<int>*>& path);

    /*** NEAREST NEIGHBOR ALGORITHM ***/
    bool findPathToOrigin(Vertex<int>* origin, std::vector<Vertex<int>*>& tour);
    std::vector<Vertex<int>*> nearestNeighborPath(Vertex<int>* origin);
    std::vector<Vertex<int>*> kNearestNeighborPath(Vertex<int>* origin, int numNeighbors);

public:
    TSP();
    explicit TSP(const Graph<int> &graph);
    Graph<int> getTspGraph();

    void backtrackingAlgorithm();
    void christofidesAlgorithm(int origin, bool fullyConnected);
    void heldKarp();
    void nearestNeighborAlgorithm(const int& origin);
    void kNearestNeighborAlgorithm(const int& origin, int k);
};


#endif //FEUP_DA_02_TSP_H
