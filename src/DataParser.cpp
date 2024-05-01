#include "DataParser.h"

using namespace std;

DataParser::DataParser() {}

/*DataParser::DataParser(string shippingPath, string stadiumsPath, string tourismPath,
                        vector<string> extraFullyConnectedEdges, string extraFullyConnectedNodes,
                        vector<string> realWorldPaths) {
    ParseToyGraphs(shippingPath, this->ToyGraphShipping);
    ParseToyGraphs(stadiumsPath, this->ToyGraphStadiums);
    ParseToyGraphTourism(tourismPath, this->ToyGraphTourism);

    for (int i = 0; i < extraFullyConnectedEdges.size(); i++) {
        string edgeFilename = extraFullyConnectedEdges[i];

        switch(i+1) {
            case 1:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph25, false);
                break;
            case 2:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph50, false);
                break;
            case 3:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph75, false);
                break;
            case 4:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph100, false);
                break;
            case 5:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph200, false);
                break;
            case 6:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph300, false);
                break;
            case 7:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph400, false);
                break;
            case 8:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph500, false);
                break;
            case 9:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph600, false);
                break;
            case 10:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph700, false);
                break;
            case 11:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph800, false);
                break;
            case 12:
                ParseBigGraph(extraFullyConnectedNodes, edgeFilename, this->ExtraFullyConnectedGraph900, false);
                break;
            default:
                break;
        }
    }

    for (int i = 0; i < realWorldPaths.size(); i++) {
        string edgeFilename = realWorldPaths[i] + "edges.csv";
        string nodesFilename = realWorldPaths[i] + "nodes.csv";

        switch (i+1) {
            case 1:
                ParseBigGraph(nodesFilename, edgeFilename, this->RealGraph1, true);
                break;
            case 2:
                ParseBigGraph(nodesFilename, edgeFilename, this->RealGraph2, true);
                break;
            case 3:
                ParseBigGraph(nodesFilename, edgeFilename, this->RealGraph2, true);
                break;
            default:
                break;
        }
    }
}*/

void DataParser::ParseToyGraphs(std::string filePath, Graph<int>& graph) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        string nonTrimmed;
        int source, target;
        double distance;

        getline(ss, nonTrimmed, ',');
        source = stoi(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        target = stoi(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        distance = stod(TrimString(nonTrimmed));

        graph.addVertex(source);
        graph.addVertex(target);
        graph.addEdge(source, target, distance);
    }
    file.close();
    cout << "Success: " << filePath << " parsed!" << endl;
}

void DataParser::ParseToyGraphTourism(std::string tourismPath, Graph<int>& graph) {
    ifstream file(tourismPath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << tourismPath << endl;
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        string nonTrimmed, sourceLabel, targetLabel;
        int source, target;
        double distance;

        getline(ss, nonTrimmed, ',');
        source = stoi(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        target = stoi(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        distance = stod(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        sourceLabel = TrimString(nonTrimmed);

        getline(ss, nonTrimmed, ',');
        targetLabel = TrimString(nonTrimmed);

        graph.addVertex(source, sourceLabel);
        graph.addVertex(target, targetLabel);
        graph.addEdge(source, target, distance);
    }
    file.close();
    cout << "Success: " << tourismPath << " parsed!" << endl;
}

void DataParser::ParseBigGraph(std::string vertexPath, std::string edgePath, Graph<int>& graph, bool edgeFileHasHeader) {
    /*      NODES PARSER    */
    ifstream nodeFile(vertexPath);
    if (!nodeFile.is_open()) {
        cerr << "Error: Unable to open file " << vertexPath << endl;
        return;
    }

    string line;
    getline(nodeFile, line);

    while(getline(nodeFile, line)){
        stringstream ss(line);
        string nonTrimmed;
        int vertexID;
        double longitude, latitude;

        getline(ss, nonTrimmed, ',');
        vertexID = stoi(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        longitude = stod(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        latitude = stod(TrimString(nonTrimmed));

        graph.addVertex(vertexID, longitude, latitude);
    }
    nodeFile.close();
    cout << "Success: " << vertexPath << " parsed!" << endl;

    /*      EDGES PARSER    */
    ifstream edgeFile(edgePath);
    if (!edgeFile.is_open()) {
        cerr << "Error: Unable to open file " << edgePath << endl;
        return;
    }

    if (edgeFileHasHeader) {
        getline(edgeFile, line);
    }

    while(getline(edgeFile, line)){
        stringstream ss(line);
        string nonTrimmed;
        int source, target;
        double distance;

        getline(ss, nonTrimmed, ',');
        source = stoi(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        target = stoi(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        distance = stod(TrimString(nonTrimmed));

        graph.addEdge(source, target, distance);
    }
    nodeFile.close();
    cout << "Success: " << edgePath << " parsed!" << endl;
}
