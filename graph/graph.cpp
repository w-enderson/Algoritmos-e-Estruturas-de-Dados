#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class GrafoMatriz{
private:
	int nEdges=0;
	int nVertices=0;
	vector<int> mark;
	vector<vector<int>> matriz;

public:
	GrafoMatriz(int n): nVertices(n), mark(n,0){
		matriz.resize(nVertices, vector<int>(nVertices, 0));

	}
	int first(int v){
		for (int i=0; i<nVertices; i++){
			if (matriz[v][i]!=0) return i;
		}
		return nVertices;
	}
	int next(int v, int w){
		for (int i=w+1; i<nVertices; i++){
			if (matriz[v][i]!=0) return i;
		}
		return nVertices;
	}
	void setEdge(int i, int j, int wt){
		if (wt==0) return ;
		if (matriz[i][j]==0) nEdges++;
		matriz[i][j] = wt;
		matriz[j][i] = wt;
	}
	void delEdge(int i, int j){
		if (matriz[i][j]!=0) nEdges--;
		matriz[i][j]=0;
	}

	void traverse(){
		for (int i=0; i<nVertices; i++){
			mark[i]= 0;
		}
	}
	
    void ciclo(int v, int parent=-1) {
        mark[v] = 1;  

        for (int i = 0; i < nVertices; ++i) {
            if (matriz[v][i] != 0) {
                if (mark[i] == 0) {
                    ciclo(i, v);
                } else if (i!=parent) {
                    cout << endl << "Ciclo encontrado entre " << v << " e " << i << " parent " <<parent << endl;
                }
            }
        }

        mark[v] = 2; 
    }

	void toposort(int v, stack<int> *a){
		mark[v]= 1;
		
		for (int i = 0; i < nVertices; ++i) {
	        if (matriz[v][i] != 0 && mark[i] == 0) { 
	            toposort(i, a);  
	        }
	    }
	    a->push(v);
	}
	void BFS(int v) {
        queue<int> fila;
        fila.push(v); 
        mark[v]= 1;

        while (!fila.empty()) {
            int atual = fila.front();
            fila.pop();

            cout << atual << endl; 

            for (int i=0; i<nVertices; ++i) {
                if (matriz[atual][i]!=0 && mark[i]==0) {  
                    fila.push(i);
                    mark[i]= 1;
                }
            }
        }
    }
    void menorCaminho(int origem, int destino) {
        vector<int> predecessor(nVertices, -1); 
        queue<int> fila;
        fila.push(origem);
        mark[origem] = 1; 

        while (!fila.empty()) {
            int u = fila.front();
            fila.pop();

            if (u == destino) {
                reconstruirCaminho(origem, destino, predecessor);
                return;
            }

            for (int i = 0; i < nVertices; ++i) {
                if (matriz[u][i] != 0 && mark[i] == 0) {
                    fila.push(i);
                    mark[i] = 1;
                    predecessor[i] = u; 
                }
            }
        }

        cout << "Não há caminho de " << origem << " para " << destino << endl;
    }

    void reconstruirCaminho(int origem, int destino, vector<int>& predecessor) {
        stack<int> caminho;
        for (int atual=destino; atual != -1; atual = predecessor[atual]) {
            caminho.push(atual);
        }

        cout << "Caminho mais curto de " << origem << " para " << destino << ": ";
        while (!caminho.empty()) {
            cout << caminho.top() << " ";
            caminho.pop();
        }
        cout << endl;
    }

	void print(){
		for(auto i: matriz){

			for(auto j: i){
				cout << j << " ";
			}
			cout<<endl;
		}
	}

};


int main(){
	GrafoMatriz a(6);

	a.setEdge(0, 2, 1);
	a.setEdge(0, 4, 1);
	a.setEdge(2, 3, 1);
	a.setEdge(2, 1, 1);
	a.setEdge(2, 5, 1);
	a.setEdge(1, 5, 1);
	a.setEdge(3, 5, 1);

	stack<int> b;
	a.toposort(0, &b);

    cout << "Elementos da pilha: ";
    while (!b.empty()) {
        cout << b.top() << " "; // Imprime o elemento do topo
        b.pop(); // Remove o elemento do topo
    }
    cout << endl;
    cout << endl;

    a.traverse();
	a.menorCaminho(0, 5);

	a.traverse();
	a.ciclo(0);

	return 0;
}