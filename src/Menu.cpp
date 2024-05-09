#include "Menu.h"

using namespace std;

Menu::Menu() {
    dataParser = DataParser();
    graph = Graph<int>();
    tsp = TSP();
}

void Menu::printMenu(vector<string> menuIndex) {
    cout << "┌───────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "│                      ████████╗    ███████╗     ███████╗                       │" << endl;
    cout << "│                      ╚══██╔══╝    ██╔════╝     ██╔═══██╗                      │" << endl;
    cout << "│                         ██║       ███████╗     ███████╔╝                      │" << endl;
    cout << "│                         ██║       ╚════██║     ██╔════╝                       │" << endl;
    cout << "│                         ██║       ███████║     ██║                            │" << endl;
    cout << "│                         ╚═╝       ╚══════╝     ╚═╝                            │" << endl;
    cout << "│                                                                               │" << endl;
    cout << "│                     Travelling    Salesman     Problem                        │" << endl;
    cout << "└──┬────────────────────────────────────────────────────────────────────────────┘" << endl;
    cout << "   │" << endl;
    for (const auto& e : menuIndex) {
        cout << "   │  " << e << endl;
    }
    cout << "   │" << endl;
}

void Menu::run() {
    while (true) {
        if (init()) {
            break;
        }
        tsp = TSP(graph);

        vector<string> menu = {
                makeBold("Current Graph: ") + currentGraph,
                "",
                makeBold("[1]. Backtracking"),
                makeBold("[2]. Triangular Approximation"),
                makeBold("[3]. Held Karp"),
                makeBold("[4]. Nearest Neighbor"),
                makeBold("[5]. K-Nearest Neighbor"),
                "...",
                "[0]. EXIT"
        };

        while (true) {
            clearScreen();
            printMenu(menu);

            int choice;
            if (waitInput(choice, "Choose a algorithm: ")) continue;

            switch (choice) {
                case 0:
                    clearScreen();
                    cout << "BYE BYE!" << endl;
                    cout << "Tip: Rerun to analyze another graph" << endl;
                    return;
                case 1:
                    tsp.backtrackingAlgorithm();
                    break;
                default:
                    continue;
            }
            waitPress();

        }
    }
}

int Menu::init() {
    vector<string> menu = {
            makeBold("[1]. Toy Graph - shipping"),
            makeBold("[2]. Toy Graph - stadiums"),
            makeBold("[3]. Toy Graph - tourism"),
            makeBold("[4]. Fully Connected - 25 edges"),
            makeBold("[5]. Fully Connected - 50 edges"),
            makeBold("[6]. Fully Connected - 75 edges"),
            makeBold("[7]. Fully Connected - 100 edges"),
            makeBold("[8]. Fully Connected - 200 edges"),
            makeBold("[9]. Fully Connected - 300 edges"),
            makeBold("[10]. Fully Connected - 400 edges"),
            makeBold("[11]. Fully Connected - 500 edges"),
            makeBold("[12]. Fully Connected - 600 edges"),
            makeBold("[13]. Fully Connected - 700 edges"),
            makeBold("[14]. Fully Connected - 800 edges"),
            makeBold("[15]. Fully Connected - 900 edges"),
            makeBold("[16]. Real World - graph 1"),
            makeBold("[17]. Real World - graph 2") + " (about 2 minutes)",
            makeBold("[18]. Real World - graph 3") + " (about 8 minutes)",
            "[0]. EXIT"
    };

    while (true) {
        clearScreen();
        printMenu(menu);

        int choice;
        if (waitInput(choice, "Choose a file to parse and analyze: ")) continue;

        switch (choice) {
            case 0:
                return 1;
            case 1:
                DataParser::ParseToyGraphs(toyGraphShipping, graph);
                currentGraph = "Toy Graph - shipping";
                break;
            case 2:
                DataParser::ParseToyGraphs(toyGraphStadiums, graph);
                currentGraph = "Toy Graph - stadiums";
                break;
            case 3:
                DataParser::ParseToyGraphTourism(toyGraphTourism, graph);
                currentGraph = "Toy Graph - tourism";
                break;
            case 4:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[0], graph, 25);
                currentGraph = "Fully Connected - 25 edges";
                break;
            case 5:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[1], graph, 50);
                currentGraph = "Fully Connected - 50 edges";
                break;
            case 6:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[2], graph, 75);
                currentGraph = "Fully Connected - 75 edges";
                break;
            case 7:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[3], graph, 100);
                currentGraph = "Fully Connected - 100 edges";
                break;
            case 8:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[4], graph, 200);
                currentGraph = "Fully Connected - 200 edges";
                break;
            case 9:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[5], graph, 300);
                currentGraph = "Fully Connected - 300 edges";
                break;
            case 10:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[6], graph, 400);
                currentGraph = "Fully Connected - 400 edges";
                break;
            case 11:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[7], graph, 500);
                currentGraph = "Fully Connected - 500 edges";
                break;
            case 12:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[8], graph, 600);
                currentGraph = "Fully Connected - 600 edges";
                break;
            case 13:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[9], graph, 700);
                currentGraph = "Fully Connected - 700 edges";
                break;
            case 14:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[10], graph, 800);
                currentGraph = "Fully Connected - 800 edges";
                break;
            case 15:
                DataParser::ParseFullyConnectedGraph(extraFullyConnectedGraphsNodes, extraFullyConnectedGraphsEdges[11], graph, 900);
                currentGraph = "Fully Connected - 900 edges";
                break;
            case 16:
                DataParser::ParseRealWorldGraph(realWorldGraphs[0] + "nodes.csv", realWorldGraphs[0] + "edges.csv", graph);
                currentGraph = "Real World - graph 1";
                break;
            case 17:
                DataParser::ParseRealWorldGraph(realWorldGraphs[1] + "nodes.csv", realWorldGraphs[1] + "edges.csv", graph);
                currentGraph = "Real World - graph 2";
                break;
            case 18:
                DataParser::ParseRealWorldGraph(realWorldGraphs[2] + "nodes.csv", realWorldGraphs[2] + "edges.csv", graph);
                currentGraph = "Real World - graph 3";
                break;
            default:
                continue;
        }
        break;
    }

    return 0;
}

int Menu::waitInput(int& choice, const string& text) {
    cout << "\n" + text;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }
    return 0;
}

void Menu::waitPress() {
    cout << "\n";
    cin.get();
    cout << "Press ENTER to continue...";
    cin.get();
}

void Menu::clearScreen() {
    system("clear || cls");
}
