#include <iostream>
#include <algorithm>

int hoarePartition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
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

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int partitionIndex = hoarePartition(arr, low, high);
        quickSort(arr, low, partitionIndex);
        quickSort(arr, partitionIndex + 1, high);
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
