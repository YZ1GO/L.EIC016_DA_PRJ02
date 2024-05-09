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
    Graph<int> realGraph1;
    Graph<int> realGraph2;
    Graph<int> realGraph3;
    dataParser.ParseRealWorldGraph("data/Real_world_Graphs/graph1/nodes.csv", "data/Real_world_Graphs/graph1/edges.csv", realGraph1);
    //realGraph1.printGraph("../output/real1.txt");
    //dataParser.ParseRealWorldGraph("data/Real_world_Graphs/graph2/nodes.csv", "data/Real_world_Graphs/graph2/edges.csv", realGraph2);
    //dataParser.ParseRealWorldGraph("data/Real_world_Graphs/graph3/nodes.csv", "data/Real_world_Graphs/graph3/edges.csv", realGraph3);

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
    dataParser.ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[0], ExtraFullyConnectedGraph25, 25);
    //ExtraFullyConnectedGraph25.printGraph("../output/25Full.txt");

    TSP twoFiveGraph(ExtraFullyConnectedGraph25);
    TSP realWorldGraph1(realGraph1);
    TSP realWorldGraph2(realGraph2);
    TSP realWorldGraph3(realGraph3);

    /***** EXECUTION ****/
    // 1. BEFORE CALL THE FUNCTION
    auto start = high_resolution_clock::now();

    // 1. FUNCTION CALL

    //tourismGraph.backtrackingAlgorithm(); // 0ms
    //tourismGraph.triangularApproximationAlgorithm();
    //tourismGraph.nearestNeighborAlgorithm(0);
    //tourismGraph.heldKarp(); // 0ms

    //shippingGraph.backtrackingAlgorithm(); // ~ 30ms
    //shippingGraph.triangularApproximationAlgorithm();
    //shippingGraph.nearestNeighborAlgorithm(0);
    //shippingGraph.heldKarp(); // ~ 220ms

    //stadiumGraph.backtrackingAlgorithm(); // ~ 550ms
    //stadiumGraph.triangularApproximationAlgorithm();
    //stadiumGraph.nearestNeighborAlgorithm(0);
    //stadiumGraph.heldKarp(); // ~ 15ms

    //twoFiveGraph.backtrackingAlgorithm(); // 1.5 hours still didn't end
    //twoFiveGraph.triangularApproximationAlgorithm();
    //twoFiveGraph.nearestNeighborAlgorithm(0);
    //twoFiveGraph.heldKarp(); // ~ 37min

    //stadiumGraph.heldKarp(); // ~ 15ms

    //realWorldGraph1.triangularApproximationAlgorithm();
    //realWorldGraph2.triangularApproximationAlgorithm();
    //realWorldGraph3.triangularApproximationAlgorithm();

    realWorldGraph1.nearestNeighborAlgorithm(0);
    //realWorldGraph2.nearestNeighborAlgorithm(0);
    //realWorldGraph3.nearestNeighborAlgorithm(0);

    // 3. AFTER FUNCTION CALL
    auto stop = high_resolution_clock::now();

    // 4. CALCULATE EXECUTION TIME
    // available units: nano, micro, milliseconds, seconds, minutes, hours
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " ms" << endl;
    return 0;
}
