#include <iostream>
#include <vector>

int main(){
    int min, temp;
    std::vector<int> arr{8,1,6,2,3,7,5,9,4,600,0};

    // sorting vector using brute force (selection sort)
    for (int i=0; i<arr.size(); i++){
        min = i;

        for (int j=i+1; j<arr.size(); j++){
            if (arr[j] < arr[min]){
                min = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }

    // print vector
    for (int x: arr){
        std::cout << " " << x;
    }

    return 0;
}
