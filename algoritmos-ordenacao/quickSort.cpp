#include <iostream>
#include <algorithm>

int hoarePartition(int arr[], int l, int r) {
    int pivot = arr[l];
    int i = l - 1;
    int j = r + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);
        do {
            j--;
        } while (arr[j] > pivot);
        if (i >= j)
            return j;
        std::swap(arr[i], arr[j]);
    }
}

void quickSort(int arr[], int l, int r) {
    if (l < r) {
        int partitionIndex = hoarePartition(arr, l, r);
        quickSort(arr, l, partitionIndex);
        quickSort(arr, partitionIndex + 1, r);
    }
}

int main() {
    int arr[]{8, 1, 6, 2, 8099, 3, 7, 5, 9, 4, 600, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);

    // Print sorted array
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
