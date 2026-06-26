// Include guard: prevents multiple inclusion of this header.
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <random>
#include <utility> // for pair

struct Edge {
    int to;
    int weight;
};

struct ShortestPathResult {
    int source;
    std::vector<long long> dist;
    std::vector<int> parent;
};

class Graph {
private:
    using State = std::pair<long long, int>;

    int V;
    std::vector<std::vector<Edge>> adj;
    bool directed;

    std::mt19937 rng {std::random_device{}()};

public:
    explicit  Graph(int vertices, bool directed = false);

    bool isValidVertex(int v) const;
    bool isReachable(int target, const ShortestPathResult& result) const;

    // Read only Getters for algos
    int vertices() const;
    const std::vector<std::vector<Edge>>& getAdj() const;

    void addEdge(int u, int v, int weight);
    void loadFromFile(const std::string& filename);
    void generateRandomGraph(int edges);

    std::vector<int> getPath(int target, const ShortestPathResult& result) const;
};

#endif