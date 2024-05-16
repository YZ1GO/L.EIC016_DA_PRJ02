#ifndef FEUP_DA_02_DATAPARSER_H
#define FEUP_DA_02_DATAPARSER_H

#include "Graph.h"
#include "Utilities.h"
#include <fstream>
#include <vector>

class DataParser {
public:
    DataParser();

    static void ParseToyGraphs(std::string filePath, Graph<int>& graph);
    static void ParseToyGraphTourism(std::string tourismPath, Graph<int>& graph);
    static void ParseFullyConnectedGraph(std::string vertexPath, std::string edgePath, Graph<int>& graph, const int& nodesNum);
    static void ParseRealWorldGraph(std::string vertexPath, std::string edgePath, Graph<int>& graph);
};


#endif //FEUP_DA_02_DATAPARSER_H
