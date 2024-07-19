#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// Estrutura para Disjoint Set
class DisjointSet {
private:
    vector<int> parent, rank;

public:
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

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

    void kruskal() {
        vector<tuple<int, int, int>> edges;
        for (int u = 0; u < V; ++u) {
            for (const auto& [v, weight] : adj[u]) {
                if (u < v) { // Para evitar duplicar as arestas em grafos não direcionados
                    edges.emplace_back(weight, u, v);
                }
            }
        }

        sort(edges.begin(), edges.end());

        DisjointSet ds(V);
        vector<tuple<int, int, int>> mst;

        for (const auto& [weight, u, v] : edges) {
            if (ds.find(u) != ds.find(v)) {
                ds.unionSets(u, v);
                mst.emplace_back(u, v, weight);
            }
        }

        cout << "Kruskal's MST:\n";
        for (const auto& [u, v, weight] : mst) {
            cout << "Edge: " << u << " - " << v << ", Weight: " << weight << "\n";
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

    cout << "Running Kruskal's algorithm...\n";
    graph.kruskal();

    return 0;
}
