#include "TSP.h"
#include <random>
#include <unordered_map>
#include <cmath>
using namespace std;

TSP::TSP() {}

TSP::TSP(const Graph<int> &graph) {
    tspGraph = graph;
}

Graph<int> TSP::getTspGraph() {
    return tspGraph;
};

template <typename T>
void TSP::printPath(const T distance, const vector<Vertex<int> *> &path) {
    cout << "DISTANCE: ";
    if (distance == DOUBLE_INF || distance == LONG_LONG_INF) {
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
    tspGraph.setAllNotVisited();
    vector<Vertex<int>*> currPath;
    vector<bool> visited(tspGraph.getVertexSet().size(), false);
    double minDistance = DOUBLE_INF;
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
void TSP::heldKarp(const int& origin) {
    auto vertexRoot = tspGraph.findVertex(origin);
    if (vertexRoot == nullptr) throw logic_error("Root vertex not found in graph");

    auto vertexSet = tspGraph.getVertexSet();
    if (vertexSet.size() > 25) {
        vertexSet.resize(25);
    }
    int n = vertexSet.size();
    vector<vector<double>> dp(n, vector<double>(1 << n, INF));
    vector<vector<Vertex<int>*>> parentVertex(n, vector<Vertex<int>*>(1 << n, nullptr));

    dp[vertexRoot->getInfo()][1 << vertexRoot->getInfo()] = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int src = 0; src < n; src++) {
            if (mask & (1 << src)) {
                for (int dest = 0; dest < n; dest++) {
                    if (!(mask & (1 << dest)) && dest != origin) {
                        double distance = DOUBLE_INF;
                        auto vertexSrc = tspGraph.findVertex(src);
                        auto vertexDest = tspGraph.findVertex(dest);
                        if (vertexSrc == nullptr || vertexDest == nullptr) throw logic_error("Vertex not found in graph");

                        for (auto edge : vertexSrc->getAdj()) {
                            if (edge->getDest() == vertexDest) {
                                distance = edge->getWeight();
                                break;
                            }
                        }
                        if (distance != DOUBLE_INF && dp[src][mask] + distance < dp[dest][mask | (1 << dest)]) {
                            dp[dest][mask | (1 << dest)] = dp[src][mask] + distance;
                            parentVertex[dest][mask | (1 << dest)] = vertexSrc;
                        }
                    }
                }
            }
        }
    }

    double minDistance = DOUBLE_INF;
    Vertex<int>* lastVertex = nullptr;
    for (int i = 0; i < n; i++) {
        if (i == origin) continue;
        double distance = DOUBLE_INF;
        auto vertexI = tspGraph.findVertex(i);
        if (vertexI == nullptr) throw logic_error("Vertex not found in graph");

        for (auto edge : vertexI->getAdj()) {
            if (edge->getDest() == vertexRoot) {
                distance = edge->getWeight();
                break;
            }
        }
        if (distance != DOUBLE_INF && dp[i][(1 << n) - 1] + distance < minDistance) {
            minDistance = dp[i][(1 << n) - 1] + distance;
            lastVertex = vertexI;
        }
    }
    vector<Vertex<int>*> path;
    path.push_back(vertexRoot);

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
// return false if not find direct edge between 2 nodes
// distance is the total distance of the path if all vertices in path is connected
bool TSP::pathDistanceNotFullyConnected(const vector<Vertex<int>*>& path, long long& distance_) {
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
            return false;
        }
        totalDistance += distance;
    }
    distance_ = totalDistance;

    return true;
}
// Time Complexity: O(V+V×A)
// where V is the number of vertices in the path and A is the maximum number of adjacent edges for any vertex in the graph
// that function always consider graph fully connected
long long TSP::pathDistanceFullyConnected(const vector<Vertex<int>*>& path) {
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
        }
        totalDistance += distance;
    }
    return totalDistance;
}

// Time Complexity: O(V+E)
void TSP::dfsTraversal(Vertex<int>* current, vector<Vertex<int>*>& path) {
    current->setVisited(true);
    path.push_back(current);

    auto adj = current->getAdj();

    for (auto edge : adj) {
        Vertex<int>* nextVertex = edge->getDest();
        if (!nextVertex->isVisited()) {
            dfsTraversal(nextVertex, path);
        }
    }
}

//Time Complexity: O(V+E)
void TSP::traverseMST(const Graph<int>& graph, Vertex<int>* start, vector<Vertex<int>*>& path) {
    graph.setAllNotVisited();
    dfsTraversal(start, path);
    path.push_back(start);
}

//Time Complexity: O((V+E)logV)
void TSP::christofidesAlgorithm(int origin, bool fullyConnected) {
    Graph<int> graph = tspGraph.convertToMST();

    graph.setAllNotVisited();
    Vertex<int>* start = graph.findVertex(origin);
    if (start == nullptr) {
        throw logic_error("Node " + to_string(origin) + " not found in graph");
    }

    vector<Vertex<int>*> path;
    traverseMST(graph, start, path);

    long long totalDistance;
    if (fullyConnected) {
        totalDistance = pathDistanceFullyConnected(path);
    } else {
        bool feasible = pathDistanceNotFullyConnected(path, totalDistance);
        if (!feasible) {
            cerr << "No feasible tour exists starting on vertex " << origin << endl;
            return;
        }
    }
    printPath(totalDistance, path);
}

/*** NEAREST NEIGHBOR ALGORITHM ***/
// Time Complexity: O(V)
bool TSP::findPathToOrigin(Vertex<int>* origin, vector<Vertex<int>*>& tour) {
    if (tour.size() == tspGraph.getNumVertex() && tour.back() == origin) {
        return true;
    }

    Vertex<int>* current = tour.back();
    for (auto e : current->getAdj()) {
        auto dest = e->getDest();
        if (dest->getInfo() == origin->getInfo()) {
            tour.push_back(dest);
            return true;
        }
    }

    return false;
}

// Time Complexity: O(V^2)
vector<Vertex<int>*> TSP::nearestNeighborPath(Vertex<int>* origin) {
    vector<Vertex<int>*> tour;
    if (origin == nullptr) {
        return tour;
    }
    tspGraph.setAllNotVisited();
    origin->setVisited(true);
    tour.push_back(origin);

    Vertex<int>* current = origin;
    while (true) {
        Vertex<int> *next = current->nearestNeighbor();
        if (next == nullptr) {
            break;
        }
        next->setVisited(true);
        tour.push_back(next);
        current = next;
    }

    return tour;
}

// Time Complexity: O(V^2)
void TSP::nearestNeighborAlgorithm(const int& origin) {
    Vertex<int>* start = tspGraph.findVertex(origin);
    if (start == nullptr) {
        cerr << "Couldn\'t find origin vertex " << origin << endl;
        return;
    }

    vector<Vertex<int>*> tour = nearestNeighborPath(start);
    if (tour.size() == tspGraph.getNumVertex()) {
        if (!findPathToOrigin(start, tour)) {
            tour.clear();
        }
    } else {
        tour.clear();
    }

    if (tour.empty()) {
        cerr << "No feasible tour exists starting on vertex " << origin << endl;
        return;
    }

    long long totalDistance;
    pathDistanceNotFullyConnected(tour, totalDistance);
    printPath(totalDistance, tour);
}

// Time complexity: O(V^2 * logV)
vector<Vertex<int>*> TSP::kNearestNeighborPath(Vertex<int>* origin, int numNeighbors) {
    vector<Vertex<int>*> tour;
    if (origin == nullptr) {
        return tour;
    }
    tspGraph.setAllNotVisited();
    origin->setVisited(true);
    tour.push_back(origin);

    Vertex<int>* current = origin;
    while (tour.size() < tspGraph.getNumVertex()) {
        vector<pair<Vertex<int>*, double>> neighbors;
        for (auto e : current->getAdj()) {
            auto dest = e->getDest();
            if (!dest->isVisited()) {
                neighbors.push_back({dest, e->getWeight()});
            }
        }
        if (neighbors.empty()) {
            break;
        }

        sort(neighbors.begin(), neighbors.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        int neighborsToExplore = min(numNeighbors, static_cast<int>(neighbors.size()));
        for (int i = 0; i < neighborsToExplore; ++i) {
            auto next = neighbors[i].first;
            next->setVisited(true);
            tour.push_back(next);
            current = next;
        }
    }

    return tour;
}

// Time complexity: O(V^2 * logV)
void TSP::kNearestNeighborAlgorithm(const int& origin, int k) {
    Vertex<int>* start = tspGraph.findVertex(origin);
    if (start == nullptr) {
        cerr << "Couldn\'t find origin vertex " << origin << endl;
        return;
    }

    vector<Vertex<int>*> tour = kNearestNeighborPath(start, k);
    if (tour.size() == tspGraph.getNumVertex()) {
        if (!findPathToOrigin(start, tour)) {
            tour.clear();
        }
    } else {
        tour.clear();
    }

    if (tour.empty()) {
        cerr << "No feasible tour exists starting on vertex " << origin << endl;
        return;
    }

    long long totalDistance;
    pathDistanceNotFullyConnected(tour, totalDistance);
    printPath(totalDistance, tour);
}

void TSP::twoOptNearestNeighborAlgorithm(const int& origin) {
    vector<Vertex<int> *> path = nearestNeighborPath(tspGraph.findVertex(origin));
    path.push_back(path[0]);
    long long minDistance = pathDistanceFullyConnected(path);
    long long maxIterations = path.size(), iterations = 0;

    bool improved = true;
    while (improved && iterations < maxIterations) {
        improved = false;
        for (int i = 1; i < path.size() - 2; ++i) {
            for (int k = i + 1; k < path.size() - 1; ++k) {
                swap(path[i], path[k]);

                long long newDistance = pathDistanceFullyConnected(path);

                if (newDistance < minDistance) {
                    improved = true;
                    minDistance = newDistance;
                    //cout << iterations << ". min distance: " << minDistance << endl;
                    break;
                } else {
                    swap(path[i], path[k]);
                }
            }

            if (improved) break;
        }
        iterations++;
        //cout << "current iteration: " << iterations << endl;
    }
    printPath(pathDistanceFullyConnected(path), path);
}

/*vector<vector<Vertex<int> *>> TSP::kMeansClustering(int k) {
    vector<vector<Vertex<int>*>> clusters(k);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, tspGraph.getNumVertex() - 1);
    vector<pair<double, double>> centroids;
    for (int i = 0; i < k; i++) {
        int index = dis(gen);

    }
}*/

void TSP::initializePheromones(double initialPheromoneLevel) {
    int numVertices = tspGraph.getNumVertex();
    pheromones = vector<vector<double>>(numVertices, vector<double>(numVertices, initialPheromoneLevel));
}

double TSP::calculateHeuristic(Vertex<int>* s, Vertex<int>* t) {
    for (auto edge : s->getAdj()) {
        if (edge->getDest() == t) {
            return 1.0 / edge->getWeight();
        }
    }
    double lat1 = s->getLatitude();
    double lon1 = s->getLongitude();
    double lat2 = t->getLatitude();
    double lon2 = t->getLongitude();
    return 1.0 / HarversineDistance(lat1, lon1, lat2, lon2);
}

vector<Vertex<int>*> TSP::constructSolution(Vertex<int>* start) {
    vector<Vertex<int>*> tour;
    tspGraph.setAllNotVisited();
    Vertex<int>* current = start;
    current->setVisited(true);
    tour.push_back(current);

    while (tour.size() < tspGraph.getNumVertex()) {
        vector<pair<Vertex<int>*, double>> probabilities;
        double sum = 0.0;

        for (auto edge : current->getAdj()) {
            auto next = edge->getDest();
            if (!next->isVisited()) {
                double pheromone = pheromones[current->getInfo()][next->getInfo()];
                double heuristic = calculateHeuristic(current, next);
                double probability = pow(pheromone, alpha) * pow(heuristic, beta);
                probabilities.emplace_back(next, probability);
                sum += probability;
            }
        }

        if (sum == 0) break;

        double threshold = (double) rand() / RAND_MAX * sum;
        double cumulative = 0.0;

        for (auto& p : probabilities) {
            cumulative += p.second;
            if (cumulative >= threshold) {
                current = p.first;
                current->setVisited(true);
                tour.push_back(current);
                break;
            }
        }
    }

    tour.push_back(start);
    return tour;
}

void TSP::updatePheromones(const vector<vector<Vertex<int>*>> &allTours, const std::vector<long long> &distances) {
    for (auto& row : pheromones) {
        for (auto& pheromone : row) {
            pheromone *= (1.0 - evaporationRate);
        }
    }

    for (int i = 0; i < allTours.size(); i++) {
        double contribution = 1.0 / distances[i];
        for (int j = 0; j < allTours[i].size() - 1; j++) {
            int from = allTours[i][j]->getInfo();
            int to = allTours[i][j + 1]->getInfo();
            pheromones[from][to] += contribution;
            pheromones[to][from] += contribution;
        }
    }
}

void TSP::antColonyOptimization(const int &origin, int numAnts, int numIterations, bool fullyConected) {
    Vertex<int>* start = tspGraph.findVertex(origin);
    if (start == nullptr) throw logic_error("Root vertex not found in graph");

    double initialPheromoneLevel = 1.0;
    initializePheromones(initialPheromoneLevel);

    vector<Vertex<int>*> bestTour;
    long long bestDistance = LONG_LONG_INF;

    for (int iter = 0; iter < numIterations; iter++) {
        vector<vector<Vertex<int>*>> allTours(numAnts);
        vector<long long> distances(numAnts);

        for (int ant = 0; ant < numAnts; ant++) {
            vector<Vertex<int>*> tour = constructSolution(start);
            long long distance;
            if (fullyConected) {
                distance = pathDistanceFullyConnected(tour);
            } else {
                bool feasible = pathDistanceNotFullyConnected(tour, distance);
                if (!feasible) {
                    cerr << "No feasible tour exists starting on vertex " << origin << endl;
                    return;
                }
            }

            if (distance < bestDistance) {
                bestDistance = distance;
                bestTour = tour;
            }

            allTours[ant] = tour;
            distances[ant] = distance;
        }

        updatePheromones(allTours, distances);
    }

    printPath(bestDistance, bestTour);
}