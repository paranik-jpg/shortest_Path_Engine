#include "WeightedGraph.h"
# include "Dijkstra.h"

#include <iostream>
#include <chrono>
#include <random>
#include <vector>

std::mt19937 rng(std::random_device{}());                  // Random number generator

void runBenchmark(int nodes, int edges) {
    // constexpr -> const whose value is known at compile time
    constexpr bool DIRECTED = true;
    Graph graph(nodes, DIRECTED);


    graph.generateRandomGraph(edges);
    // spe.loadFromFile("C:/Users/HP/OneDrive/Desktop/Coding/SPE/tests/graph_data.txt");

    // New random mechanism
    std::uniform_int_distribution<int> vertexDist(0, nodes-1); // Unifrom distribution between range(both inclusive)

    int source = vertexDist(rng);
    int target = vertexDist(rng);


    // Timer starts
    auto start = std::chrono::high_resolution_clock::now();  // Highest available precision
    auto result = dijkstra(graph, source);
    // Timer stops
    auto end = std::chrono::high_resolution_clock::now();


    // Type is float And unit is milli
    std::chrono::duration<double, std::milli> elapsed = end - start;      
             
    std::cout << "Nodes : " << nodes << std::endl;
    std::cout << "Edges : " << edges << std::endl;                // .count() retruns numeric value 
    std::cout << "Time : " << elapsed.count() << " ms" << std::endl;

    if(!graph.isReachable(target, result)) {
        std::cout << "Target is unreachable" << std::endl;
    }
    else {
        std::vector<int> path = graph.getPath(target, result);
        std::cout << "Route from " << result.source 
                  << " to " << target 
                  << " (Cost: " << result.dist[target] << "): ";

        for(size_t i = 0; i < path.size(); ++i) { // Use size_t when iterating on vectors
            std::cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        std::cout << std::endl; 
        std::cout << "---------------------------" << std::endl;
    }
}

int main() {
    // Speeds up I/O in C++
    std::ios_base::sync_with_stdio(false); // Disable the sync of cin, cout with scanf, printf
    std::cin.tie(nullptr);                 // Automatic flushing of cout before cin is disabled

    runBenchmark(100, 500);
    runBenchmark(10000, 50000);
    runBenchmark(100000, 500000);

    return 0;
}