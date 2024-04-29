#ifndef FEUP_DA_02_DATAPARSER_H
#define FEUP_DA_02_DATAPARSER_H

#include "Graph.h"
#include "Location.h"
#include "Utilities.h"
#include <fstream>

class DataParser {
private:
    Graph<Location> bigGraph;

    Graph<int> toyGraphShipping;
    Graph<int> toyGraphStadiums;
    Graph<int> toyGraphTourism;


public:
    DataParser();
    void ParseToysGraph(std::string shippingPath, std::string stadiumsPath, std::string tourismPath);

};


#endif //FEUP_DA_02_DATAPARSER_H
