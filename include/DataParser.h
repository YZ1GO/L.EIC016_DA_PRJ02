#ifndef FEUP_DA_02_DATAPARSER_H
#define FEUP_DA_02_DATAPARSER_H

#include "Graph.h"
#include "Utilities.h"
#include <fstream>
#include <vector>

class DataParser {
private:


public:
    DataParser();

    static void ParseToyGraphs(std::string filePath, Graph<int>& graph);
    static void ParseToyGraphTourism(std::string tourismPath, Graph<int>& graph);
    static void ParseBigGraph(std::string vertexPath, std::string edgePath, Graph<int>& graph, bool edgeFileHasHeader);
};


#endif //FEUP_DA_02_DATAPARSER_H
