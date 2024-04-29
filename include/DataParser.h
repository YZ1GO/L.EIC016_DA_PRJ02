#ifndef FEUP_DA_02_DATAPARSER_H
#define FEUP_DA_02_DATAPARSER_H

#include "Graph.h"
#include "Location.h"
#include "Utilities.h"
#include <fstream>
#include <vector>

class DataParser {
private:
    Graph<Location> RealGraph1;
    Graph<Location> RealGraph2;
    Graph<Location> RealGraph3;
    Graph<Location> ExtraFullyConnectedGraph25;
    Graph<Location> ExtraFullyConnectedGraph50;
    Graph<Location> ExtraFullyConnectedGraph75;
    Graph<Location> ExtraFullyConnectedGraph100;
    Graph<Location> ExtraFullyConnectedGraph200;
    Graph<Location> ExtraFullyConnectedGraph300;
    Graph<Location> ExtraFullyConnectedGraph400;
    Graph<Location> ExtraFullyConnectedGraph500;
    Graph<Location> ExtraFullyConnectedGraph600;
    Graph<Location> ExtraFullyConnectedGraph700;
    Graph<Location> ExtraFullyConnectedGraph800;
    Graph<Location> ExtraFullyConnectedGraph900;
    Graph<int> toyGraphShipping;
    Graph<int> toyGraphStadiums;
    Graph<int> toyGraphTourism;

    void ParseToyGraphs(std::string shippingPath, std::string stadiumsPath, std::string tourismPath);
    void ParseRealWorldGraphs(std::vector<std::string> datasetPaths);
    void ParseExtraFullyConnectedGraphs(std::vector<std::string> datasetPaths);
    void ParseBigGraph(std::string datasetPath);

public:
    DataParser();
    DataParser(std::string shippingPath, std::string stadiumsPath, std::string tourismPath,
               std::vector<std::string> extraFullyConnectedPaths, std::vector<std::string> realWorldPaths);
    Graph<Location> getRealGraph1;
    Graph<Location> getRealGraph2;
    Graph<Location> getRealGraph3;
    Graph<Location> getExtraFullyConnectedGraph25;
    Graph<Location> getExtraFullyConnectedGraph50;
    Graph<Location> getExtraFullyConnectedGraph75;
    Graph<Location> getExtraFullyConnectedGraph100;
    Graph<Location> getExtraFullyConnectedGraph200;
    Graph<Location> getExtraFullyConnectedGraph300;
    Graph<Location> getExtraFullyConnectedGraph400;
    Graph<Location> getExtraFullyConnectedGraph500;
    Graph<Location> getExtraFullyConnectedGraph600;
    Graph<Location> getExtraFullyConnectedGraph700;
    Graph<Location> getExtraFullyConnectedGraph800;
    Graph<Location> getExtraFullyConnectedGraph900;
    Graph<int> gettoyGraphShipping;
    Graph<int> gettoyGraphStadiums;
    Graph<int> gettoyGraphTourism;
};


#endif //FEUP_DA_02_DATAPARSER_H
