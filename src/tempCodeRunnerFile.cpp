

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