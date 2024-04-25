#include <iostream>

int* subArray(int arr[], int begin, int end){
    int* newArr = new int[end-begin+1]; 
    for (int i = 0; i < end-begin+1; i++){ 
        newArr[i] = arr[begin+i];
    }

    return newArr;
}

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
        int *B = subArray(arr, 0, n/2);
        int *C = subArray(arr, n/2, n-1);

        mergeSort(B, n/2);
        mergeSort(C, n-n/2);
        merge(B, C, arr, n/2, n-n/2);

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
