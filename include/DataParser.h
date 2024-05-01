#ifndef FEUP_DA_02_DATAPARSER_H
#define FEUP_DA_02_DATAPARSER_H

#include "Graph.h"
#include "Utilities.h"
#include <fstream>
#include <vector>

class DataParser {
private:
    Graph<int> RealGraph1;
    Graph<int> RealGraph2;
    Graph<int> RealGraph3;
    Graph<int> ExtraFullyConnectedGraph25;
    Graph<int> ExtraFullyConnectedGraph50;
    Graph<int> ExtraFullyConnectedGraph75;
    Graph<int> ExtraFullyConnectedGraph100;
    Graph<int> ExtraFullyConnectedGraph200;
    Graph<int> ExtraFullyConnectedGraph300;
    Graph<int> ExtraFullyConnectedGraph400;
    Graph<int> ExtraFullyConnectedGraph500;
    Graph<int> ExtraFullyConnectedGraph600;
    Graph<int> ExtraFullyConnectedGraph700;
    Graph<int> ExtraFullyConnectedGraph800;
    Graph<int> ExtraFullyConnectedGraph900;
    Graph<int> ToyGraphShipping;
    Graph<int> ToyGraphStadiums;
    Graph<int> ToyGraphTourism;

    void ParseToyGraphs(std::string filePath, Graph<int>& graph);
    void ParseToyGraphTourism(std::string tourismPath, Graph<int>& graph);
    void ParseBigGraph(std::string vertexPath, std::string edgePath, Graph<int>& graph, bool edgeFileHasHeader);

public:
    DataParser();
    DataParser(std::string shippingPath, std::string stadiumsPath, std::string tourismPath,
               std::vector<std::string> extraFullyConnectedEdges, std::string extraFullyConnectedNodes,
               std::vector<std::string> realWorldPaths);
    Graph<int> getRealGraph1();
    Graph<int> getRealGraph2();
    Graph<int> getRealGraph3();
    Graph<int> getExtraFullyConnectedGraph25();
    Graph<int> getExtraFullyConnectedGraph50();
    Graph<int> getExtraFullyConnectedGraph75();
    Graph<int> getExtraFullyConnectedGraph100();
    Graph<int> getExtraFullyConnectedGraph200();
    Graph<int> getExtraFullyConnectedGraph300();
    Graph<int> getExtraFullyConnectedGraph400();
    Graph<int> getExtraFullyConnectedGraph500();
    Graph<int> getExtraFullyConnectedGraph600();
    Graph<int> getExtraFullyConnectedGraph700();
    Graph<int> getExtraFullyConnectedGraph800();
    Graph<int> getExtraFullyConnectedGraph900();
    Graph<int> getToyGraphShipping();
    Graph<int> getToyGraphStadiums();
    Graph<int> getToyGraphTourism();
};


#endif //FEUP_DA_02_DATAPARSER_H
