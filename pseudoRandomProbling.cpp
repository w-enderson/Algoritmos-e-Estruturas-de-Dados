#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Pair {
    private:
        int key;
        int value;
        bool isOccupied=false;
    public:
        Pair(int k, int v) : key(k), value(v) {
            isOccupied=true;

        }
        Pair(){
            key = -1;
            value = -1;
        }

        int getKey() const { return key; }
        int getValue() const { return value; }
        bool getSituation()const { return isOccupied; }

        void setOcuppied(){
            isOccupied = true;
        }
};


class HashTable {
    private:
        int sizeHT;
        int nElements;
        int hashFunction(int key){
            return key%sizeHT;
        }
        vector<Pair> arr;
        vector<int> perm;
    public:
        HashTable(int s): sizeHT(s), arr(s), perm(s-1)  {
            for (int i=0; i<sizeHT-1;i++){
                perm[i]=i+1;
            }
            shuffle(perm.begin(), perm.end(), default_random_engine{});
        }
        ~HashTable(){
            for (auto& pair : arr) {
                if (pair.getSituation()) {
                    pair.~Pair();
                }
            }
        }
        int find(int k){
            int c = 0;
            int index = hashFunction(k);
            while(arr[index].getSituation()){
                if (arr[index].getKey()==k ) {
                    return index;
                }
                index = (index+perm[++c])%sizeHT;
            }
            return -1;
        }
        void insert(int k, int v) {
            int c = 0;
            if (nElements!=sizeHT && find(k)==-1){
                int index = hashFunction(k);
                while(arr[index].getKey()!=-1 && arr[index].getValue()!=-1){
                    index = (index+perm[c++])%sizeHT;
                }
                arr[index] = Pair(k, v);
                
                nElements++;
            }
        }

        void printPerm(){
            for (const auto& a: perm){
                cout << a << " ";
            }
            cout << endl;
        }

        void printArr(){
            for (const auto& a: arr){
                cout << a.getKey() << "," << a.getValue() << endl;
            }
            cout << endl;
        }
};


int main(){
    HashTable a(5);
    a.printPerm();
    a.insert(0,3);
    a.printArr();
    a.insert(5,3);
    a.printArr();
    a.insert(10,3);
    a.printArr();
    a.insert(15,3);
    a.printArr();
    a.insert(20,3);
    a.printArr();
    return 0;
}

// 3 4 2 1 
