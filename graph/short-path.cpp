#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Grafo {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Grafo(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int weight) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cerr << "Invalid edge between " << u << " and " << v << endl;
            return;
        }
        adj[u].emplace_back(v, weight);
        adj[v].emplace_back(u, weight); // Se for um grafo não direcionado
    }

    void dijkstra(int s) {
        if (s < 0 || s >= V) {
            cerr << "Invalid source vertex for Dijkstra: " << s << endl;
            return;
        }

        vector<int> D(V, INT_MAX);
        vector<int> P(V, -1);
        vector<bool> visited(V, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        D[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (const auto& [v, weight] : adj[u]) {
                if (D[u] + weight < D[v]) {
                    D[v] = D[u] + weight;
                    P[v] = u;
                    pq.push({D[v], v});
                }
            }
        }

        cout << "Dijkstra from " << s << ":\n";
        for (int i = 0; i < V; ++i) {
            if (D[i] == INT_MAX) {
                cout << "Vertex " << i << ": INF\n";
            } else {
                cout << "Vertex " << i << ": Distance " << D[i] << ", Parent " << P[i] << "\n";
            }
        }
    }

    void floydWarshall() {
        vector<vector<int>> D(V, vector<int>(V, INT_MAX));

        for (int i = 0; i < V; ++i) {
            D[i][i] = 0;
            for (const auto& [v, weight] : adj[i]) {
                if (v < V) {
                    D[i][v] = weight;
                } else {
                    cerr << "Invalid vertex " << v << " in Floyd-Warshall initialization\n";
                }
            }
        }

        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    if (D[i][k] != INT_MAX && D[k][j] != INT_MAX && D[i][j] > D[i][k] + D[k][j]) {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                }
            }
        }

        cout << "Floyd-Warshall:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (D[i][j] == INT_MAX) {
                    cout << "INF ";
                } else {
                    cout << D[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    void bellmanFord(int s) {
        if (s < 0 || s >= V) {
            cerr << "Invalid source vertex for Bellman-Ford: " << s << endl;
            return;
        }

        vector<int> D(V, INT_MAX);
        D[s] = 0;

        for (int k = 0; k < V - 1; ++k) {
            for (int i = 0; i < V; ++i) {
                for (const auto& [j, weight] : adj[i]) {
                    if (D[i] != INT_MAX && D[i] + weight < D[j]) {
                        D[j] = D[i] + weight;
                    }
                }
            }
        }

        bool hasNegativeCycle = false;
        for (int i = 0; i < V; ++i) {
            for (const auto& [j, weight] : adj[i]) {
                if (D[i] != INT_MAX && D[i] + weight < D[j]) {
                    hasNegativeCycle = true;
                    break;
                }
            }
            if (hasNegativeCycle) break;
        }

        if (hasNegativeCycle) {
            cout << "Negative cycle detected\n";
        } else {
            cout << "Bellman-Ford from " << s << ":\n";
            for (int i = 0; i < V; ++i) {
                if (D[i] == INT_MAX) {
                    cout << "Vertex " << i << ": INF\n";
                } else {
                    cout << "Vertex " << i << ": Distance " << D[i] << "\n";
                }
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

    int source = 0;
    cout << "Enter source vertex for Dijkstra: ";
    graph.dijkstra(source);

    cout << "Running Floyd-Warshall algorithm...\n";
    graph.floydWarshall();

    cout << "Enter source vertex for Bellman-Ford: ";
    cin >> source;
    graph.bellmanFord(source);

    return 0;
}
