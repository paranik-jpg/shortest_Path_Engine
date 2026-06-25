#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm> // for reverse
#include <fstream>   // for file handling
#include <chrono>    // for timer
#include <random>    // for alternatives of rand()

using namespace std;

// struct for u->(to, weight)
struct Edge {
    int to;
    int weight;
};

class ShortestPathEngine {
private:
    // Type Alias
    using State = pair<long long, int>;

    int V;
    vector<vector<Edge>> adj;
    bool directed;

    mt19937 rng {random_device{}()}; // Random Number Generator

public:

    // explicit => ShortestPathEngine spe(6) - OK, S... spe = 6 - NOT  OK
    explicit  ShortestPathEngine(int vertices, bool directed = false) : V(vertices), adj(vertices), directed(directed) { // Default - undirected
    }

    // Vertex Validation for adding edges after declaring a fix nodded graph
    bool isValidVertex(int v) const {   // const => Safe function
        return (v >= 0 && v < V);
    }

    // will get reachability, but pass the dists's vector
    bool isReachable(int target, const vector<long long>& dists) const {
        if(!isValidVertex(target)) {
            return false;
        }

        return dists[target] != LLONG_MAX;
    }

    void addEdge(int u, int v, int weight) {
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

    void loadFromFile(const string& filename) {
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

    void generateRandomGraph(int edges) {                // Vertices will be used from 'V'  
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

    // Dijkstra
    // T.C. = O((V+E) logV)
    // S.C. = O(V)
    // Std Dijkstra but { dist, path }
    void dijkstra(int source, vector<long long>& dist, vector<int>& parent) {
        if(!isValidVertex(source)) { // vertex validation
            cerr << "Invalid source vertex: " << source << endl;
            return;
        }

        dist.assign(V, LLONG_MAX);
        parent.assign(V, -1);

        dist[source] = 0;

        priority_queue<State, vector<State>, greater<State>> pq;
        pq.push({0, source});

        while(!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if(d > dist[u]) continue; // Already zyada -> skip

            for(const auto& edge : adj[u]) { // 'const' And '&' used to remove copying everytime
                int v = edge.to;
                int weight = edge.weight;

                if(dist[u] != LLONG_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // will get path, but pass the parent's vector
    vector<int> getPath(int target, const vector<int>& parent) const {
        vector<int> path;

        if(!isValidVertex(target)) { // vertex validation
            return path;
        }

        for(int v = target; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    // will print path, but pass the parent's vector And dist's vector
    void printPath(int target, const vector<int>& parent, const vector<long long>& dists) const {
        if(!isValidVertex(target)) { // vertex validation
            cout << "Invalid destination vertex." << endl;
            return;
        }

        if(!isReachable(target, dists)) {
            cout << "Path to node " << target << ": Unreachable!" << endl;
            return;
        }

        vector<int> path = getPath(target, parent);

        if(path.empty()) {
            return;
        }

        cout << "Route from " << path[0] << " to " << target << " (Cost: " << dists[target] << "): ";
        for(size_t i = 0; i < path.size(); ++i) { // Use size_t when iterating on vectors
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
    }

    void printGraph() const {
        for(int i = 0; i < V; ++i) {
            cout << i << " : ";
            cout << "{";
            for(size_t j = 0; j < adj[i].size(); ++j) {
                cout << "{" << adj[i][j].to << ", " << adj[i][j].weight << "}";
                if(j + 1 != adj[i].size()) {
                    cout << ", ";
                }
            }
            cout << "}" << endl;
        }
    }
};

int main() {
    // Speeds up I/O in C++
    ios_base::sync_with_stdio(false); // Disable the sync of cin, cout with scanf, printf
    cin.tie(nullptr);                 // Automatic flushing of cout before cin is disabled

    vector<pair<int, int>> benchMarks = {{100, 500}, {10000, 50000}, {100000, 500000}};
    mt19937 rng(random_device{}());                  // Random number generator

    for(const auto& itr : benchMarks) {
        int nodes = itr.first;
        int edges = itr.second;

        // constexpr -> const whose value is known at compile time
        constexpr bool DIRECTED = true;
        ShortestPathEngine spe(nodes, DIRECTED);
        
        vector<long long> dist;
        
        vector<int> parent; // for path

        spe.generateRandomGraph(edges);
        // spe.loadFromFile("C:/Users/HP/OneDrive/Desktop/Coding/SPE/tests/graph_data.txt");

        // New random mechanism
        uniform_int_distribution<int> rando(0, nodes-1); // Unifrom distribution between range(both inclusive)

        // Timer starts
        auto start = chrono::high_resolution_clock::now();  // Highest available precision
        spe.dijkstra(rando(rng), dist, parent);
        // Timer stops
        auto end = chrono::high_resolution_clock::now();

        // Type is float And unit is milli
        chrono::duration<double, milli> elapsed = end - start;      
        // .count() retruns numeric value      
        cout << "Nodes : " << nodes << endl;
        cout << "Edges : " << edges << endl;
        cout << "Time : " << elapsed.count() << " ms" << endl; 
        cout << "---------------------------" << endl;

        spe.printPath(rando(rng), parent, dist);
    }

    return 0;
}