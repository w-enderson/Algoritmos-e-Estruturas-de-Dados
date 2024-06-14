#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Heap {
private:
    vector<int> H;
    int n;

    void inorder(int idx) {
        if (idx <= n) {
            inorder(2*idx);
            cout << H[idx] << " ";
            inorder(2*idx + 1);
        }
    }

    void preorder(int idx) {
        if (idx <= n) {
            cout << H[idx] << " ";
            preorder(2*idx);
            preorder(2*idx + 1);
        }
    }

    void posorder(int idx) {
        if (idx <= n) {
            posorder(2*idx);
            posorder(2*idx + 1);
            cout << H[idx] << " ";
        }
    }

    void bottomUp() {
        for (int i = n/2; i >= 1; i--) {
            int k = i, v = H[k];
            bool heap = false;
            while (!heap && 2*k <= n) {
                int j = 2*k;
                if (j < n && H[j] < H[j+1]) {
                    j++;
                }
                if (v >= H[j]) {
                    heap = true;
                } else {
                    H[k] = H[j];
                    k = j;
                }
            }
            H[k] = v;
        }
    }

    void topDown(int i, int n) {
        int maior = i;
        int esquerda = 2*i;
        int direita = 2*i + 1;

        if (esquerda <= n && H[esquerda] > H[maior]) {
            maior = esquerda;
        }

        if (direita <= n && H[direita] > H[maior]) {
            maior = direita;
        }

        if (maior != i) {
            swap(H[i], H[maior]);
            topDown(maior, n);
        }
    }

public:
    Heap() {}

    void setArray(vector<int> arr) {
        H = arr;
        n = H.size() - 1;
    }

    void printArray() {
        for (int i = 1; i <= n; i++) {
            cout << H[i] << " ";
        }
        cout << endl;
        preorder(1);
        cout << endl;
        posorder(1);
        cout << endl;
        inorder(1);
        cout << endl;
    }

    void heapify() {
        bottomUp();
    }

    void remove() {
        if (n != 1) {
            swap(H[1], H[n]);
            n--;
            heapify();
        } else {
            cout << "vazio" << endl;
        }
    }

    void topDownHeapify() {
        for (int i = n/2; i >= 1; i--) {
            topDown(i, n);
        }
    }
};

int main() {
    Heap a;

    vector<int> arr{0, 9, 8, 6, 2, 5, 1};

    cout << "Original Heap:" << endl;
    a.setArray(arr);
    a.printArray();
    cout << endl;

    cout << "Heap after topDownHeapify:" << endl;
    a.topDownHeapify();
    a.printArray();

    return 0;
}
