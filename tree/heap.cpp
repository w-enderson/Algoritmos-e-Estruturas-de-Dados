#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Heap {
private:
    vector<int> H;
    int n;

    void inorder(int i) {
        if (i <= n) {
            inorder(2*i);
            cout << H[i] << " ";
            inorder(2*i + 1);
        }
    }
    void preorder(int i) {
        if (i <= n) {
            cout << H[i] << " ";
            preorder(2*i);
            preorder(2*i + 1);
        }
    }
    void posorder(int i) {
        if (i <= n) {
            posorder(2*i);
            posorder(2*i + 1);
            cout << H[i] << " ";
        }
    }

    void bottomUp() {
        for (int i = n/2; i >= 1; i--) {
            int k = i, v = H[k];
            bool heap = false;
            while (!heap && 2*k <= n) {
                int j = 2*k;
                if (j < n && H[j] < H[j+1]) { // >
                    j++;
                }
                if (v >= H[j]) { // <=
                    heap = true;
                } else {
                    H[k] = H[j];
                    k = j;
                }
            }
            H[k] = v;
        }
    }

    void topDown(int i) {
        while (i > 1 && H[i/2] < H[i]) { // >
            swap(H[i], H[i/2]);
            i = i / 2;
        }
    }

public:
    Heap() {
        H.push_back(0);  
        n = 0;
    }

    int getTop(){
        if (n > 0) {
            return H[1];
        } else {
            cout << "Heap vazia!" << endl;
            return -1;
        }
    }
    void printArray() {
        for (int i = 1; i <= n; i++) {
            cout << H[i] << " ";
        }
        cout << endl;
    }

    // bottomUp
    void remove() {
        if (n != 1) {
            swap(H[1], H[n]);
            n--;
            H.pop_back();
            bottomUp();
        } else {
            cout << "vazio" << endl;
        }
    }

    // topDown
    void insert(int value) {
        H.push_back(value);
        n++;
        topDown(n);
    }

    // tests
    void testBottomUp(vector<int>& elements) {
        cout << "Testing bottomUp heapify:" << endl;
        H=elements;
        n=H.size();
        bottomUp();
        printArray();
        cout << endl;
    }

    void testTopDown(vector<int>& elements) {
        cout << "Testing topDown heapify:" << endl;
        for (int elem : elements) {
            insert(elem);
            printArray();
        }
        cout << endl;
    }
};

int main() {
    Heap heap;

    vector<int> elements = {2, 9, 7, 6, 5, 8, 10};

    heap.testBottomUp(elements);

    // Reset heap for topDown test
    heap = Heap();

    heap.testTopDown(elements);

    return 0;
}
