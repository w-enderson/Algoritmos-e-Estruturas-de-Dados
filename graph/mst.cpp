#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// Classe do Grafo
class Grafo {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Grafo(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int weight) {
        adj[u].emplace_back(v, weight);
        adj[v].emplace_back(u, weight); // Se for um grafo não direcionado
    }

    void prim(int s) {
        vector<int> D(V, INT_MAX);
        vector<int> P(V, -1); // Parent array
        vector<bool> inMST(V, false); // Mark vertices as part of MST
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        D[s] = 0;
        pq.push(make_pair(0, s)); // (weight, vertex)

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (const auto& [v, weight] : adj[u]) {
                if (!inMST[v] && weight < D[v]) {
                    D[v] = weight;
                    P[v] = u;
                    pq.push(make_pair(D[v], v));
                }
            }
        }

        cout << "Prim's MST:\n";
        for (int i = 0; i < V; ++i) {
            if (P[i] != -1) {
                cout << "Edge: " << P[i] << " - " << i << ", Weight: " << D[i] << "\n";
            }
        }
    }

   
};

int main() {
    int n, m;
    cin >> n >> m;
    Grafo graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    int source=0;
    cout << "Enter source vertex for Prim's algorithm: ";
    graph.prim(source);

    return 0;
}
