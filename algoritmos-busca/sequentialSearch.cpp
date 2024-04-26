#include <iostream>
using namespace std;


int sequentialSearch(int arr[], int K, int n){
    int i = 0;
    arr[n] = K;

    while (arr[i]!=K){
        i++;
    }
    if (i<n){
        return i;
    } else {
        return -1;
    }
    
}

int main(){
    int arr[]{5,4,82,16,4};
    int n = sizeof(arr)/ sizeof(arr[0]);
    cout << sequentialSearch(arr, 5, n) << endl;
    return 0;
}
