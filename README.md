# TSP - Traveling Salesman Problem

## Description
This project enables comparison between different solutions for the Traveling Salesman Problem (TSP), a renowned challenge in combinatorial optimization. The objective is to determine the shortest route that visits each city exactly once and returns to the starting city. Being [NP-hard](https://en.wikipedia.org/wiki/NP-hardness), the TSP lacks a polynomial-time solution algorithm.

[RESULTS SHEET](https://docs.google.com/spreadsheets/d/1I6d1NvNj34K96kJRol0O1ccQ8HP2-nnEXvQ0IW0alAs/edit?usp=sharing)

## Algorithms

### Backtracking
- __🚀 Time Complexity:__ O(V!), where V is the number of vertices in the graph. 

### Triangular Approximation
- Creates a MST using Prim's algorithm and traverses it using a DFS.
- __🚀 Time Complexity:__ O((V+E) logV), where V is the number of vertices and E is the number of edges in the graph.

### Nearest Neighbor
- Greedy algorithm that selects the nearest unvisited vertex to the current vertex.
- __🚀 Time Complexity:__ O(V^2), where V is the number of vertices in the graph.

### K-Nearest Neighbor
- Greedy algorithm that selects the k nearest unvisited vertices to the current vertex.
- __🚀 Time Complexity:__ O(V^2 * logV + V * k), where V is the number of vertices in the graph.

### 2-Opt
- Give a solution path and iteratively swaps two edges to reduce the total distance of the path.
- __🚀 Time Complexity:__ O(V^2), where V is the number of vertices in the graph.

### 3-Opt
- Give a solution path and iteratively swaps three edges to reduce the total distance of the path.
- __🚀 Time Complexity:__ O(V^3), where V is the number of vertices in the graph.
<br></br>
📝 Note: The Opt algorithms that we implemented, uses as initial solution the nearest neighbor algorithm (NNA). Which means that the time complexity of the Opt algorithms is `max(Opt, NNA)`.

### TSP in Real World
We tailored the Triangular Approximation, Nearest Neighbor Algorithm (NNA), and K-Nearest Neighbor (K-NN) to tackle real-world TSP scenarios. Users now have the flexibility to __select__ the starting vertex and determine whether to treat the graph as fully connected or not.

With these adjustments, our algorithms provide solutions even when the graphs __may not be fully connected__, by returning `feasible` or `not feasible`, ensuring that a solution is always provided.


