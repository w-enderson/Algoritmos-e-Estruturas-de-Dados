#include <iostream>
using namespace std;

int binarySearch(int arr[], int K, int n){
    int l=0, r=n-1, m;
    while (l<=r){
        m = (l+r)/2;
        if (K==arr[m]) {
            return m;
        } else if (K<arr[m]) {
            r = m-1;
        } else {
            l = m+1;
        }
    }
    return -1;
}


int main(){
    int arr[]{1,2,4,6,8,9,50};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k;
    while(true){
        cin >> k;
        cout << binarySearch(arr, k, n) << endl;
    }

    return 0;
}
