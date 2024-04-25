#include <iostream>
#include <vector>

int main(){
    int min, temp;
    std::vector<int> arr{8,1,6,2,3,7,5,9,4,600,0};

    // sorting vector using brute force (selection sort)
    for (int i=0; i<arr.size()-1; i++){
        for (int j=0; j<arr.size()-1-i; j++){
            if (arr[j+1] < arr[j]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    // print vector
    for (int x: arr){
        std::cout << " " << x;
    }

    return 0;
}
