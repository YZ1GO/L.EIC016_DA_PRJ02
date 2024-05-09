#ifndef FEUP_DA_02_MENU_H
#define FEUP_DA_02_MENU_H

#include <chrono>
#include "TSP.h"

class Menu {
public:
    Menu();
    void run();
    int init();

private:
    void parseGraph();
    DataParser dataParser;
    Graph<int> graph;
    std::string currentGraph = "-";
    TSP tsp;

    static void printMenu(std::vector<std::string> menuIndex);
    static int waitInput(int& choice, const std::string& text);
    static void waitPress();
    static void clearScreen();

    std::string extraFullyConnectedGraphsNodes = "data/Extra_Fully_Connected_Graphs/nodes.csv";
    std::vector<std::string> extraFullyConnectedGraphsEdges = {
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
    std::vector<std::string> realWorldGraphs = {
            "data/Real_world_Graphs/graph1/",
            "data/Real_world_Graphs/graph2/",
            "data/Real_world_Graphs/graph3/"
    };

    std::string toyGraphShipping = "data/Toy_Graphs/shipping.csv";
    std::string toyGraphStadiums = "data/Toy_Graphs/stadiums.csv";
    std::string toyGraphTourism = "data/Toy_Graphs/tourism.csv";
};


#endif //FEUP_DA_02_MENU_H
