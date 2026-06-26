#include "WeightedGraph.h"

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

Graph::Graph(int vertices, bool directed) 
    : V(vertices), adj(vertices), directed(directed) {     // Default - undirected
}

bool Graph::isValidVertex(int v) const {   // const => Safe function
    return (v >= 0 && v < V);
}

bool Graph::isReachable(int target, const ShortestPathResult& result) const {
    if(!isValidVertex(target)) {
        return false;
    }

    return result.dist[target] != LLONG_MAX;
}

int Graph::vertices() const {
    return V;
}

const std::vector<std::vector<Edge>>& Graph::getAdj() const {
    return adj;
}

void Graph::addEdge(int u, int v, int weight) {
    if(!isValidVertex(u) || !isValidVertex(v)) { // vertex validation
        cerr << "Invalid edge (" << u << ", " << v << ")" << endl;
        return;
    }

    if(weight < 0) {
        cerr << "Negative weights are not allowed" << endl;
        return;
    }

    adj[u].push_back({v, weight});

    if(!directed) {
        adj[v].push_back({u, weight}); 
    }
}

void Graph::loadFromFile(const string& filename) {
    ifstream file(filename); 
    // opens file 'filename' as input to program only 

    // `file.is_open()` returns T if opened successfully
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    int u, v, w;
    while (file >> u >> v >> w) {
        addEdge(u, v, w);
    }

    // ifstream closes the opened file in end
}

void Graph::generateRandomGraph(int edges) {                // Vertices will be used from 'V'  
    uniform_int_distribution<int> distGen(1, 100);

    // Spanning tree with V-1 edges first, to ensure connectivity for undirected !!!
    for(int i = 1; i < V; i++) { 
        uniform_int_distribution<int> distri(0, i - 1);

        int parent = distri(rng);

        int w = distGen(rng);
        addEdge(parent, i, w);
    }    

    uniform_int_distribution<int> vertexGen(0, V-1); // Unifrom distribution between range(both inclusive)

    for(int i = V; i < edges; ++i) {
        int u = vertexGen(rng);
        int v = vertexGen(rng);
        int w = distGen(rng);

        if(u != v) {
            addEdge(u, v, w);
        }
    }
}

vector<int> Graph::getPath(int target, const ShortestPathResult& result) const {
    vector<int> path;

    if(!isValidVertex(target)) { // vertex validation
        return path;
    }

    for(int v = target; v != -1; v = result.parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}