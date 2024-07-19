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
        vector<int> D(V, INT_MAX);
        vector<int> P(V, -1);
        vector<bool> visited(V, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        D[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (auto [v, weight] : adj[u]) {
                if (D[u] + weight < D[v]) {
                    D[v] = D[u] + weight;
                    P[v] = u;
                    pq.push({D[v], v});
                }
            }
        }

        for (int i = 0; i < V; ++i) {
            int d = D[i];
            if (d==INT_MAX){
                cout << -1 << endl;
            } else {
                cout << d << endl;
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

    void printArr(int dist[], int pred[]) {
        for (int i=0; i<V; ++i) {
            printf("Vertice: %d Antecessor: %d Distancia: %d\n", i, pred[i], dist[i]);
        }
    }

    void BellmanFord(int src) {
        int D[V];
        int P[V]; 

        for (int i=0; i<V; i++) {
            D[i] = INT_MAX;
            P[i] = -1; 
        }

        D[src] = 0;

        for (int i=1; i<=V-1; i++) {
            for (int u=0; u<V; u++) {
                for (auto edge : adj[u]) {
                    int v = edge.first;
                    int w = edge.second;
                    if (D[u]!=INT_MAX && (D[u]+w < D[v])) {
                        D[v] = D[u] + w;
                        P[v] = u;
                    }
                }
            }
        }

        for (int u = 0; u < V; u++) {
            for (auto edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (D[u]!=INT_MAX && D[u]+w < D[v]) {
                    cout << "Ciclo negativo encontrado!" << endl;
                    return; 
                }
            }
        }

        printArr(D, P);
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
