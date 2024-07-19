#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <map>
#include <string>

using namespace std;

class DisjointSet {
private:
    vector<int> parent, rank;

public:
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i=0; i<n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); 
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

struct Edge {
    int u, v, weight;
};

bool compareEdges(const Edge &e1, const Edge &e2) {
    return e1.weight < e2.weight;
}

class Grafo {
private:
    int V;
    vector<Edge> edges;

public:
    Grafo(int V) : V(V) {}

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    int kruskal() {
        sort(edges.begin(), edges.end(), compareEdges);

        DisjointSet ds(V);
        vector<Edge> mst;

        for (auto edge : edges) {
            if (ds.find(edge.u)!=ds.find(edge.v)) {
                ds.unionSets(edge.u, edge.v);
                mst.push_back(edge);
            }
        }

        int r=0;
        for (const auto &edge : mst) {
            r+=edge.weight;
        }
        return r;
    }
};

int main() {
    map<string, int> vertexMap;
    int v = 0;

    string c1, c2;
    int d;

    Grafo graph(12);
    
    while (cin >> c1 >> c2 >> d){
        if (vertexMap.find(c1) == vertexMap.end()) {
            vertexMap[c1] = v++;
        }
        if (vertexMap.find(c2) == vertexMap.end()) {
            vertexMap[c2] = v++;
        }

        graph.addEdge(vertexMap[c1], vertexMap[c2], d);
    }
    
    cout << graph.kruskal() << endl;
    

    return 0;
}
