#include <iostream>
#include <vector>
#include <chrono>
#include "TSP.h"

using namespace std;
using namespace chrono;

void countOneMillion() {
    for (long long i = 0; i < 1000000; i++) {
        cout << i << endl;
    }
    cout << "DONE" << endl;
}

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
            "data/Extra_Fully_Connected_Graphs/edges_900.csv"
    };
    string extraFullyConnectedGraphsNodes = "data/Extra_Fully_Connected_Graphs/nodes.csv";

    vector<string> realWorldGraphs = {
            "data/Real_world_Graphs/graph1/",
            "data/Real_world_Graphs/graph2/",
            "data/Real_world_Graphs/graph3/"
    };

    string toyGraphShipping = "data/Toy_Graphs/shipping.csv";
    string toyGraphStadiums = "data/Toy_Graphs/stadiums.csv";
    string toyGraphTourism = "data/Toy_Graphs/tourism.csv";
/*
    Graph<int> RealGraph1;
    Graph<int> RealGraph2;

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
    Graph<int> ToyGraphTourism;*/

    DataParser dataParser;

    //Graph<int> RealGraph3;
    //dataParser.ParseBigGraph("data/Real_world_Graphs/graph3/nodes.csv", "data/Real_world_Graphs/graph3/edges.csv", RealGraph3, true);

    Graph<int> ToyGraphTourism;
    Graph<int> ToyGraphStadiums;
    Graph<int> ToyGraphShipping;
    dataParser.ParseToyGraphTourism(toyGraphTourism, ToyGraphTourism);
    dataParser.ParseToyGraphs(toyGraphStadiums, ToyGraphStadiums);
    dataParser.ParseToyGraphs(toyGraphShipping, ToyGraphShipping);
    TSP tourismGraph(ToyGraphTourism);
    TSP stadiumGraph(ToyGraphStadiums);
    TSP shippingGraph(ToyGraphShipping);

    Graph<int> ExtraFullyConnectedGraph25;
    dataParser.ParseBigGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[0], ExtraFullyConnectedGraph25, false);
    TSP twoFiveGraph(ExtraFullyConnectedGraph25);

    /***** EXECUTION ****/
    // 1. BEFORE CALL THE FUNCTION
    auto start = high_resolution_clock::now();

    // 1. FUNCTION CALL

    //tourismGraph.backtrackingAlgorithm(); // 0ms
      //stadiumGraph.triangularApproximationAlgorithm();
    //tourismGraph.heldKarp(); // 0ms

    //shippingGraph.backtrackingAlgorithm(); // ~ 30ms
      //shippingGraph.triangularApproximationAlgorithm();
    //shippingGraph.heldKarp(); // ~ 220ms

    //stadiumGraph.backtrackingAlgorithm(); // ~ 550ms
      //tourismGraph.triangularApproximationAlgorithm();
    //stadiumGraph.heldKarp(); // ~ 15ms

    //twoFiveGraph.backtrackingAlgorithm(); // 1.5 hours still didn't end
    //twoFiveGraph.heldKarp(); // ???

    cout << "ADD TO THE EXCEL SHEET, LINK ON README"

    // 3. AFTER FUNCTION CALL
    auto stop = high_resolution_clock::now();

    // 4. CALCULATE EXECUTION TIME
    // available units: nano, micro, milliseconds, seconds, minutes, hours
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " ms" << endl;
    return 0;
}
