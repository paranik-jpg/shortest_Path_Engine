#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm> // for reverse
#include <fstream>   // for file handling
#include <chrono>    // for timer

using namespace std;

// struct for u->(to, weight)
struct Edge {
    int to;
    int weight;
};

class ShortestPathEngine {
private:
    int V;
    vector<vector<Edge>> adj;

public:
    ShortestPathEngine(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Assuming undirected
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

        // always close the opened file in end
        file.close();
    }

    void generateRandomGraph(int vertices, int edges) {
        for(int i = 0; i < edges; ++i) {
            int u = rand() % vertices;
            int v = rand() % vertices;
            int w = rand() % 100 + 1;
            if(u != v) {
                addEdge(u, v, w);
            }
        }
    }

    // Std Dijkstra but { dist, path }
    pair<vector<int>, vector<int>> dijkstra(int source) {
        vector<int> dist(V, INT_MAX);
        dist[source] = 0;
        
        vector<int> parent(V, -1); // for path

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});

        while(!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if(d > dist[u]) continue; // Already zyada -> skip

            for(auto edge : adj[u]) {
                int v = edge.to;
                int weight = edge.weight;

                if(dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        return {dist, parent};
    }

    // will get reachability, but pass the dists's vector
    bool isReachable(int target, const vector<int>& dists) {
        return dists[target] != INT_MAX;
    }

    // will get path, but pass the parent's vector
    vector<int> getPath(int target, const vector<int>& parent) {
        vector<int> path;
        for(int v = target; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    // will print path, but pass the parent's vector And dist's vector
    void printPath(int target, const vector<int>& parent, const vector<int>& dists) {
        if(!isReachable(target, dists)) {
            cout << "Path to node " << target << ": Unreachable!" << endl;
            return;
        }

        vector<int> path = getPath(target, parent);
        cout << "Route from " << path[0] << " to " << target << " (Cost: " << dists[target] << "): ";
        for(int i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
    }

    void printGraph() {
        for(int i=0; i<V; i++) {
            cout << i << " : ";
            cout << "{ ";
            for(auto adjNode : adj[i]) {
                cout << "{";
                cout << adjNode.to << "," << adjNode.weight;
                cout << "}";
            }
            cout << " }" << endl;
        }
    }
};

int main() {

    vector<pair<int, int>> benchMarks = {{100, 500}, {10000, 50000}, {100000, 500000}};

    for(auto itr : benchMarks) {
        int nodes = itr.first;
        int edges = itr.second;

        ShortestPathEngine spe(nodes);

        spe.generateRandomGraph(nodes, edges);
        // spe.loadFromFile("C:/Users/HP/OneDrive/Desktop/Coding/SPE/tests/graph_data.txt");

        // Timer starts
        auto start = chrono::high_resolution_clock::now();  // Highest available precision
        auto it = spe.dijkstra(rand() % nodes);
        // Timer stops
        auto end = chrono::high_resolution_clock::now();

        // Type is float And unit is milli
        chrono::duration<double, milli> elapsed = end - start;      
        // .count() retruns numeric value      
        cout << "Calculation took: " << elapsed.count() << " ms" << endl; 

        vector<int> dists = it.first;
        vector<int> parent = it.second;

        spe.printPath(rand() % nodes, parent, dists);
    }

    return 0;
}