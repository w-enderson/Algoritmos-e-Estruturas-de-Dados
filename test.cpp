#include <iostream>
#include <string>

using namespace std;
 
int main() {
    double x, y;
    string quadr;
    
    cin >> x >> y;
    
    if (x>0 && y>0){
        quadr = "Q1";       
    } else if (x<0 && y>0){
        quadr = "Q2";       
    } else if (x<0 && y<0){
        quadr = "Q3";       
    } else if (x>0 && y<0){
        quadr = "Q4";        
    } else if (x==0 && y==0) {
        quadr = "Origem";
    } else if (y==0){
        quadr = "Eixo X";        
    } else if (x==0){
        quadr = "Eixo Y";        
    }
    cout << quadr << endl;
 
    return 0;
}