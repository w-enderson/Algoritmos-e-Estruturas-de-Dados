#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>

using namespace std;

class GrafoLista {
private:
    int nVertices;
    vector<int> mark;
    vector<list<int>> adj;

public:
    GrafoLista(int n) : nVertices(n), mark(n, 0), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    void removeEdge(int u, int v) {
        adj[u].remove(v);
        adj[v].remove(u);
    }

    void traverse() {
        for (int i = 0; i < nVertices; ++i) {
            mark[i] = 0;
        }
    }

    void DFS(int v) {
        mark[v] = 1;
        cout << v << " ";

        for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
            if (mark[*it] == 0) {
                DFS(*it);
            }
        }
    }

    void ciclo(int v, int parent = -1) {
        mark[v] = 1;

        for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
            int i = *it;
            if (mark[i] == 0) {
                ciclo(i, v);
            } else if (i != parent) {
                cout << endl << "Ciclo encontrado entre " << v << " e " << i << " parent " << parent << endl;
            }
        }

        mark[v] = 2;
    }

    void BFS(int v) {
        queue<int> fila;
        fila.push(v);
        mark[v] = 1;

        while (!fila.empty()) {
            int atual = fila.front();
            fila.pop();

            cout << atual << " ";

            for (auto it = adj[atual].begin(); it != adj[atual].end(); ++it) {
                if (mark[*it] == 0) {
                    fila.push(*it);
                    mark[*it] = 1;
                }
            }
        }
    }

    void print() {
        for (int i = 0; i < nVertices; ++i) {
            cout << i << ": ";
            for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
                cout << *it << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    GrafoLista a(6);

    a.addEdge(0, 2);
    a.addEdge(0, 4);
    a.addEdge(2, 3);
    a.addEdge(2, 1);
    a.addEdge(2, 5);
    a.addEdge(1, 5);
    a.addEdge(3, 5);

    cout << "Lista de Adjacência do Grafo:" << endl;
    a.print();

    cout << endl << "DFS a partir do vértice 0:" << endl;
    a.traverse();
    a.DFS(0);
    cout << endl;

    cout << endl << "BFS a partir do vértice 0:" << endl;
    a.traverse();
    a.BFS(0);
    cout << endl;

    cout << endl << "Ciclos no Grafo:" << endl;
    a.traverse();
    a.ciclo(0);

    return 0;
}
