#ifndef FEUP_DA_02_TSP_H
#define FEUP_DA_02_TSP_H

#include "DataParser.h"
#include <stack>
#define INF std::numeric_limits<double>::max()

class TSP {
private:
    Graph<int> tspGraph;
    void printPath(double distance, const std::vector<Vertex<int>*> &path);
    void backtrackingAlgorithmAux(Vertex<int>* currVertex, double currDistance, std::vector<Vertex<int>*> &path, std::vector<bool> &visited, double &minDistance, std::vector<Vertex<int>*> &bestPath);

    /***  TRIANGULAR APPROXIMATION RELATED FUNCTIONS  ***/
    Graph<int> getMST(const Graph<int>& graph);
    void traverseMST(Vertex<int>* start, std::vector<Vertex<int>*>& path);
    double pathDistance(const std::vector<Vertex<int>*>& path);
  
public:
    explicit TSP(const Graph<int> &graph);
    void backtrackingAlgorithm();
    void triangularApproximationAlgorithm();
    void heldKarp();
};


#endif //FEUP_DA_02_TSP_H
