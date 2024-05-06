#include "TSP.h"
using namespace std;

TSP::TSP(const Graph<int> &graph) {
    tspGraph = graph;
}

void TSP::backtrackingAlgorithmAux(Vertex<int>* currVertex, double currDistance, vector<Vertex<int>*> &currPath, vector<bool> &visited, double &minDistance, vector<Vertex<int>*> &bestPath) {
    /*cout << "Current vertex: " << currVertex->getInfo() << endl;
    cout << "Current path: ";
    for (auto vertex : currPath) {
        cout << vertex->getInfo() << " ";
    }
    cout << "Current distance: " << currDistance << endl;
    cout << endl;*/

    if (currPath.size() == tspGraph.getVertexSet().size()) {
        for (auto edge: currVertex->getAdj()) {
            if (edge->getDest() == currPath.front()) {
                double totalDistance = currDistance + edge->getWeight();
                if (totalDistance < minDistance) {
                    minDistance = totalDistance;
                    bestPath = currPath;
                }
                return;
            }
        }
    }

    for (auto edge : currVertex->getAdj()) {
        auto dest = edge->getDest();
        if (!dest->isVisited()) {
            currPath.push_back(dest);
            dest->setVisited(true);
            currDistance += edge->getWeight();

            if (currDistance < minDistance) {
                backtrackingAlgorithmAux(dest, currDistance, currPath, visited, minDistance, bestPath);
            }

            currPath.pop_back();
            dest->setVisited(false);
            currDistance -= edge->getWeight();
        }
    }
}

void TSP::backtrackingAlgorithm() {
    vector<Vertex<int>*> currPath;
    vector<bool> visited(tspGraph.getVertexSet().size(), false);
    double minDistance = numeric_limits<double>::max();
    vector<Vertex<int>*> bestPath;

    Vertex<int>* root = tspGraph.findVertex(0);
    if (root == nullptr) {
        throw logic_error("Root vertex not found in graph");
    }
    currPath.push_back(root);
    root->setVisited(true);
    visited[0] = true;

    backtrackingAlgorithmAux(root, 0, currPath, visited, minDistance, bestPath);

    cout << "Minimum Distance: ";
    if (minDistance == numeric_limits<double>::max()) {
        cout << "No path found" << endl;
        return;
    } else {
        cout << minDistance << endl;
    }
    cout << "Path: ";
    if (bestPath.empty()) {
        cout << "No path found" << endl;
        return;
    }
    for (auto vertex : bestPath) {
        cout << vertex->getInfo() << " ";
    }
    cout << endl;
}

/*** TRIANGULAR APPROXIMATION RELATED FUNCTIONS [T2.2] ***/
Graph<int> TSP::getMST(const Graph<int>& graph) {
    Graph<int> copyGraph = deepGraphCopy(graph);
    copyGraph.convertToMST();

    return copyGraph;
}

double TSP::pathDistance(const vector<Vertex<int>*>& path) {
    double totalDistance = 0.0;

    for (int i = 0; i < path.size()-1; i++) {
        auto s = path[i];
        auto t = path[i+1];
        for (auto e : s->getAdj()) {
            if (e->getDest()->getInfo() == t->getInfo()) {
                double distance = e->getWeight();
                if (distance == 0.0) {
                    double lat1 = s->getLatitude();
                    double lon1 = s->getLongitude();
                    double lat2 = t->getLatitude();
                    double lon2 = t->getLongitude();
                    distance = HarversineDistance(lat1, lon1, lat2, lon2);
                }
                totalDistance += distance;
                break;
            }
        }
    }

    return totalDistance;
}

void TSP::traverseMST(Vertex<int>* start, vector<Vertex<int>*>& path) {
    stack<Vertex<int>*> s;

    start->setVisited(true);
    path.push_back(start);
    s.push(start);

    while (!s.empty()) {
        auto v = s.top();
        s.pop();

        for (auto e : v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited()) {
                w->setVisited(true);
                path.push_back(w);
                s.push(w);
            }
        }
    }

    path.push_back(start);
}

void TSP::triangularApproximationAlgorithm() {
    Graph<int> graph = getMST(this->tspGraph);
    graph.setAllNotVisited();

    Vertex<int>* start = graph.findVertex(0);
    if (start == nullptr) {
        throw logic_error("Node zero not found in graph");
    }

    vector<Vertex<int>*> path;
    traverseMST(start, path);
    double totalDistance = pathDistance(path);

    cout << "Travelled distance: " << totalDistance << endl;
    cout << "Path: ";
    for (auto step : path) {
        cout << step->getInfo() << " ";
    }
    cout << endl;
}
