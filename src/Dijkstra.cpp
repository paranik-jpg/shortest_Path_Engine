#include "Dijkstra.h"

#include <queue>
#include <climits>
#include <functional>
#include <iostream>
#include <utility>

using State = std::pair<long long, int>;

ShortestPathResult dijkstra(const Graph& graph, int source) {
    if(!graph.isValidVertex(source)) { // vertex validation
        std::cerr << "Invalid source vertex: " << source << std::endl;
        return {};
    }

    ShortestPathResult result;

    result.source = source;
    result.dist.assign(graph.vertices(), LLONG_MAX);
    result.parent.assign(graph.vertices(), -1);

    result.dist[source] = 0;

    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.push({0, source});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if(d > result.dist[u]) continue; // Already zyada -> skip

        for(const auto& edge : graph.getAdj()[u]) { // 'const' And '&' used to remove copying everytime
            int v = edge.to;
            int weight = edge.weight;

            if(result.dist[u] != LLONG_MAX && result.dist[u] + weight < result.dist[v]) {
                result.dist[v] = result.dist[u] + weight;
                result.parent[v] = u;
                pq.push({result.dist[v], v});
            }
        }
    }

    return result;
}
