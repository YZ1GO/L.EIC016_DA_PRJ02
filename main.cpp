#include <iostream>
#include <vector>
#include "DataParser.h"

using namespace std;

int main() {
    vector<string> extraFullyConnectedGraphsEdges = {
            "data/Extra_Fully_Connected_Graphs/edges_25.csv",
            "data/Extra_Fully_Connected_Graphs/edges_50.csv",
            "data/Extra_Fully_Connected_Graphs/edges_75.csv",
            "data/Extra_Fully_Connected_Graphs/edges_100.csv",
            "data/Extra_Fully_Connected_Graphs/edges_200.csv",
            "data/Extra_Fully_Connected_Graphs/edges_300.csv",
            "data/Extra_Fully_Connected_Graphs/edges_400.csv",
            "data/Extra_Fully_Connected_Graphs/edges_500.csv",
            "data/Extra_Fully_Connected_Graphs/edges_600.csv",
            "data/Extra_Fully_Connected_Graphs/edges_700.csv",
            "data/Extra_Fully_Connected_Graphs/edges_800.csv",
            "data/Extra_Fully_Connected_Graphs/edges_900.csv",
    };
    string extraFullyConnectedGraphsNodes = "data/Extra_Fully_Connected_Graphs/nodes.csv";

    vector<string> realWorldGraphs = {
            "data/Real_world_Graphs/graph1/",
            "data/Real_world_Graphs/graph2/",
            "data/Real_world_Graphs/graph3/",
    };

    string toyGraphShipping = "data/Toy_Graphs/shipping.csv";
    string toyGraphStadiums = "data/Toy_Graphs/stadiums.csv";
    string toyGraphTourism = "data/Toy_Graphs/tourism.csv";

    DataParser dataParser(toyGraphShipping, toyGraphStadiums, toyGraphTourism,
                          extraFullyConnectedGraphsEdges, extraFullyConnectedGraphsNodes, realWorldGraphs);

    return 0;
}
