#include <iostream>


void merge(int B[], int C[], int arr[], int p, int q){
    int i=0, j=0, k=0;

    while (i<p && j<q){
        if (B[i]<=C[j]){
            arr[k] = B[i];
            i++;
        } else {
            arr[k]=C[j];
            j++;
        }

        k++;
    }
    while (i < p){
        arr[k] = B[i];
        i++;
        k++;
    }
    while (j < q){
        arr[k] = C[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int n){
    if (n>1){
        int mid = n / 2;

        int* B = new int[mid];
        int* C = new int[n - mid];

        for (int i = 0; i < mid; i++) {
            B[i] = arr[i];
        }
        for (int i = mid; i < n; i++) {
            C[i-mid] = arr[i];
        }

        mergeSort(B, mid);
        mergeSort(C, n-mid);
        merge(B, C, arr, mid, n-mid);


        delete[] B;
        delete[] C;
    }
}


int main(){
    int arr[]{8,1,6,2, 8099,3,7,5,9,4,600,0};

    int n = sizeof(arr)/sizeof(arr[0]);
    mergeSort(arr, n);

    // print array
    for (int x: arr){
        std::cout << " " << x;
    }
    return 0;
}
