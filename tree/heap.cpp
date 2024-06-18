#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Heap {
private:
    vector<int> H;
    int n;

    void heapfyDown() {
        for (int i = n/2; i >= 1; i--) {
            int k=i, v=H[k];
            bool heap = false;
            while (!heap && 2*k <= n) {
                int j = 2*k; // left
                if (j<n && H[j]<H[j+1]) { // >
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

    void heapfyUp() {
        for (int i=0; i<H.size(); i++){
            // enquanto pai menor que filho,
            // troca filho com pai
            while (i>1 && H[i/2] < H[i]) { // >
                swap(H[i], H[i/2]);
                i = i/2;
            }    
        }
    }

public:
    Heap() {
        H.push_back(0);
        n = 0;
    }

    void setArr(vector<int> arr){
        H = arr;
        n = H.size()-1;
        heapfyDown();
    }
    void printArray() {
        for (int i = 1; i <= n; i++) {
            cout << H[i] << " ";
        }
        cout << endl;
    }
    int getTop(){
        if (n > 0) {
            return H[1];
        } else {
            cout << "Heap vazia!" << endl;
            return -1;
        }
    }

    // bottomUp
    void remove() {
        if (n>0) {
            swap(H[1], H[n]);
            n--;
            heapfyDown();
        }
    }

    void heapsort(){
        while (n>1){
            remove();
        }

        for (int i=1; i<H.size(); i++){
            cout << H[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    vector<int> arr = {0, 9,6,8,2,5,7};

    Heap heap;
    
    heap.setArr(arr);
    heap.heapsort();

    return 0;
}
