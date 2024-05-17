#include <iostream>

class charNode {
    private:
        char el;
        charNode* next;

    public:
        charNode(int x, charNode* y=NULL) : el(x), next(y) {} 
        charNode(charNode* y=NULL) : next(y) {} 
};

class charList {
    private: 
        charNode* head; 
        charNode* tail;
        charNode* curr;
        int listSize;

        void init(){
            head = tail = curr = new charNode;
            listSize = 0;
        }
};

int main(){

    return 0;
}

