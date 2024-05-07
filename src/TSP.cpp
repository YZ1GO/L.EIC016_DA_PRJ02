#include "TSP.h"
using namespace std;

TSP::TSP(const Graph<int> &graph) {
    tspGraph = graph;
}

void TSP::printPath(const double distance, const vector<Vertex<int> *> &path) {
    cout << "Minimum Distance: ";
    if (distance == INF) {
        cout << "No path found" << endl;
        return;
    } else {
        cout << distance << endl;
    }
    cout << "Path: ";
    if (path.empty()) {
        cout << "No path found" << endl;
        return;
    }
    for (auto vertex : path) {
        cout << vertex->getInfo() << " ";
    }
    /*for (size_t i = 0; i < path.size() - 1; ++i) {
        double edgeWeight = 0;
        for (auto edge : path[i]->getAdj()) {
            if (edge->getDest() == path[i + 1]) {
                edgeWeight = edge->getWeight();
                break;
            }
        }
        cout << edgeWeight << " ";
    }*/
    cout << endl;
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
                    bestPath.push_back(bestPath.front());
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

// O(V!)
void TSP::backtrackingAlgorithm() {
    vector<Vertex<int>*> currPath;
    vector<bool> visited(tspGraph.getVertexSet().size(), false);
    double minDistance = INF;
    vector<Vertex<int>*> bestPath;

    Vertex<int>* root = tspGraph.findVertex(0);
    if (root == nullptr) {
        throw logic_error("Root vertex not found in graph");
    }
    currPath.push_back(root);
    root->setVisited(true);
    visited[0] = true;

    backtrackingAlgorithmAux(root, 0, currPath, visited, minDistance, bestPath);

    printPath(minDistance, bestPath);
}

/***************4.3 Other Heuristics****************/

// O(V^2 * 2^V)
void TSP::heldKarp() {
    auto vertexSet = tspGraph.getVertexSet();
    if (vertexSet.size() > 25) {
        vertexSet.resize(25);
    }
    int n = vertexSet.size();
    vector<vector<double>> dp(n, vector<double>(1 << n, INF));
    vector<vector<Vertex<int>*>> parentVertex(n, vector<Vertex<int>*>(1 << n, nullptr));

    for (auto v : vertexSet) {
        dp[v->getInfo()][1 << v->getInfo()] = 0;
    }

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int src = 0; src < n; src++) {
            if (mask & (1 << src)) {
                for (int dest = 0; dest < n; dest++) {
                    if (!(mask & (1 << dest)) && dest != 0) {
                        double distance = INF;
                        auto vertexSrc = tspGraph.findVertex(src);
                        auto vertexDest = tspGraph.findVertex(dest);
                        if (vertexSrc == nullptr || vertexDest == nullptr) throw logic_error("Vertex not found in graph");

                        for (auto edge : vertexSrc->getAdj()) {
                            if (edge->getDest() == vertexDest) {
                                distance = edge->getWeight();
                                break;
                            }
                        }
                        if (distance != INF && dp[src][mask] + distance < dp[dest][mask | (1 << dest)]) {
                            dp[dest][mask | (1 << dest)] = dp[src][mask] + distance;
                            parentVertex[dest][mask | (1 << dest)] = vertexSrc;
                        }
                    }
                }
            }
        }
    }

    double minDistance = INF;
    Vertex<int>* lastVertex = nullptr;
    for (int i = 1; i < n; i++) {
        double distance = INF;
        auto vertexI = tspGraph.findVertex(i);
        auto vertexZero = tspGraph.findVertex(0);
        if (vertexI == nullptr || vertexZero == nullptr) throw logic_error("Vertex not found in graph");

        for (auto edge : vertexI->getAdj()) {
            if (edge->getDest() == vertexZero) {
                distance = edge->getWeight();
                break;
            }
        }
        if (distance != INF && dp[i][(1 << n) - 1] + distance < minDistance) {
            minDistance = dp[i][(1 << n) - 1] + distance;
            lastVertex = vertexI;
        }
    }
    vector<Vertex<int>*> path;
    auto root = tspGraph.findVertex(0);
    if (root == nullptr) throw logic_error("Root vertex not found in graph");
    path.push_back(root);

    int mask = (1 << n) - 1;
    while (lastVertex != nullptr) {
        path.push_back(lastVertex);
        int temp = mask;
        mask ^= (1 << lastVertex->getInfo());
        lastVertex = parentVertex[lastVertex->getInfo()][temp];
    }
  
    printPath(minDistance, path);
}

/*** TRIANGULAR APPROXIMATION RELATED FUNCTIONS [T2.2] ***/
long long TSP::pathDistance(const vector<Vertex<int>*>& path) {
    long long totalDistance = 0.0;

    for (int i = 0; i < path.size() - 1; i++) {
        auto s = tspGraph.findVertex(path[i]->getInfo());
        auto t = tspGraph.findVertex(path[i + 1]->getInfo());

        double distance = 0.0;
        bool directEdgeFound = false;
        for (auto e : s->getAdj()) {
            if (e->getDest()->getInfo() == t->getInfo()) {
                distance = e->getWeight();
                directEdgeFound = true;
                break;
            }
        }

        if (!directEdgeFound) {
            double lat1 = s->getLatitude();
            double lon1 = s->getLongitude();
            double lat2 = t->getLatitude();
            double lon2 = t->getLongitude();
            distance = HarversineDistance(lat1, lon1, lat2, lon2);
            //if (distance <= 0) {
            //    cerr << "Error: Can\'t calculate the Harversine distance" << endl;
            //    cout << s->getInfo() << ", " << t->getInfo() << endl;
            //}
            //cout << lat1 << ", " << lon1 << ", " << lat2 << ", " << lon2 << endl;
        }
        totalDistance += distance;
        //cout << s->getInfo() << "," << t->getInfo() << ": " << distance << endl;
    }

    return totalDistance;
}


void TSP::dfsTraversal(Vertex<int>* current, vector<Vertex<int>*>& path) {
    current->setVisited(true);
    path.push_back(current);

    auto adj = current->getAdj();
    sort(adj.begin(), adj.end(), [](const Edge<int>* a, const Edge<int>* b) {
        return a->getWeight() < b->getWeight();
    });

    for (auto edge : adj) {
        Vertex<int>* nextVertex = edge->getDest();
        if (!nextVertex->isVisited()) {
            dfsTraversal(nextVertex, path);
        }
    }
}

void TSP::traverseMST(const Graph<int>& graph, Vertex<int>* start, vector<Vertex<int>*>& path) {
    graph.setAllNotVisited();
    dfsTraversal(start, path);
    path.push_back(start);
}

void TSP::triangularApproximationAlgorithm() {
    Graph<int> graph = tspGraph.convertToMST();

    //graph.printGraph("../output/MST.txt");
    //tspGraph.printGraph("../output/original.txt");
    graph.setAllNotVisited();
    Vertex<int>* start = graph.findVertex(0);
    if (start == nullptr) {
        throw logic_error("Node zero not found in graph");
    }

    vector<Vertex<int>*> path;
    traverseMST(graph, start, path);
    long long totalDistance = pathDistance(path);

    cout << "Travelled distance: " << totalDistance << endl;
    cout << "Path: ";
    for (auto step : path) {
        cout << step->getInfo() << " ";
    }
    cout << endl;
}
