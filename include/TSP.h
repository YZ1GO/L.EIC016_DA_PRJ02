#ifndef FEUP_DA_02_TSP_H
#define FEUP_DA_02_TSP_H

#include "DataParser.h"
#define INF std::numeric_limits<double>::max()

class TSP {
private:
    Graph<int> tspGraph;
    void printPath(double distance, const std::vector<Vertex<int>*> &path);
    void backtrackingAlgorithmAux(Vertex<int>* currVertex, double currDistance, std::vector<Vertex<int>*> &path, std::vector<bool> &visited, double &minDistance, std::vector<Vertex<int>*> &bestPath);
public:
    explicit TSP(const Graph<int> &graph);
    void backtrackingAlgorithm();
    void heldKarp();
};


#endif //FEUP_DA_02_TSP_H
