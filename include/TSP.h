#ifndef FEUP_DA_02_TSP_H
#define FEUP_DA_02_TSP_H

#include "DataParser.h"

class TSP {
private:
    Graph<int> tspGraph;
    void backtrackingAlgorithmAux(Vertex<int>* currVertex, double currDistance, std::vector<Vertex<int>*> &path, std::vector<bool> &visited, double &minDistance, std::vector<Vertex<int>*> &bestPath);
public:
    TSP(const Graph<int> &graph);
    void backtrackingAlgorithm();
};


#endif //FEUP_DA_02_TSP_H
