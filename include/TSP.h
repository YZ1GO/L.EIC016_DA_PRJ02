#ifndef FEUP_DA_02_TSP_H
#define FEUP_DA_02_TSP_H

#include "DataParser.h"
#include <stack>

class TSP {
private:
    Graph<int> tspGraph;

    void backtrackingAlgorithmAux(Vertex<int>* currVertex, double currDistance, std::vector<Vertex<int>*> &path, std::vector<bool> &visited, double &minDistance, std::vector<Vertex<int>*> &bestPath);

    /***  TRIANGULAR APPROXIMATION RELATED FUNCTIONS  ***/
    Graph<int> getMST(const Graph<int>& graph);
    void traverseMST(Vertex<int>* start, std::vector<Vertex<int>*>& path);
    double pathDistance(const std::vector<Vertex<int>*>& path);
public:
    TSP(const Graph<int> &graph);
    void backtrackingAlgorithm();
    void triangularApproximationAlgorithm();
};


#endif //FEUP_DA_02_TSP_H
