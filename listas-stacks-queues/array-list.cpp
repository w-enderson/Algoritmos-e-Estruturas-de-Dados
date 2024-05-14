#include <iostream>

using namespace std;

template <class W> class AList {
    private:
        int maxSize, listSize, curr;
        W* listArr;
    public:
        AList(int size) : maxSize(size), listArr(new W[maxSize]){ // constructor
            listSize = curr = 0;
        }
        ~AList() { delete[] listArr; } // destructor

        void clear() {
            delete[] listArr;
            listSize = curr = 0;
            listArr = new W[maxSize];
        }

        void insert(const W& el) {
            if (listSize>=maxSize){
                cout << "Lista cheia, impossível adicionar!!" << endl;
                return;
            }
            for (int i=listSize; i>curr; i--){
                listArr[i] = listArr[i-1];
            }
            listArr[curr] = el;
            listSize++;
        }
        W remove(){
            if (curr<0 || listSize<=curr){
                cout << "sem elemento, impossível remover!!" << endl;
                return -1;
            }
            W el = listArr[curr];
            for (int i=curr; i<listSize-1; i++){
                listArr[i] = listArr[i+1];
            }
            listSize--;
            return el;
        }
        void moveToStart() { curr = 0; }
        void moveToEnd() { curr = listSize; }
        void prev() { if (curr!=0) curr--; }
        void next() { if (curr < listSize) curr++; }
        
        int length() const { return listSize; }
        int currPos() const { return curr; }

        void moveToPos(int pos) {
            if (pos<0 || pos>=listSize){
                cout << "Pos fora do range!!" << endl;
                return;
            }
            curr = pos;
        }

        const W& getValue() const {
            return listArr[curr];
        }
};

int main(){
    int size = 3;

    AList <int> lista{size};

    return 0;
}