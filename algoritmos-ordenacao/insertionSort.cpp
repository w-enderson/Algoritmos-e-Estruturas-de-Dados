#include <iostream>
#include <vector>

int main(){
    std::vector<int>arr{5,4,8,6,2,1,47,9};
    int v, j;

    for (int i=1; i<arr.size(); i++){
        v = arr[i];
        j = i-1;

        while(j>=0 && arr[j]>v){
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = v;
    }
    for (auto x: arr){
        std::cout << " " << x;
    }

    return 0;
}
