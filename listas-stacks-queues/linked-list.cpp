#include <iostream>
using namespace std;
template <class E> class Link {
    public:
        E el;
        Link *next;
        Link (const E& val, Link* nextVal=NULL) {
            el = val;
            next = nextVal;
        }
        Link (Link* nextVal=NULL){
            next = nextVal;
        }
};
template <class E> class LList {
    private:
        Link<E>* head;
        Link<E>* tail;
        Link<E>* curr;
        int listSize;

        void init() {
            curr = tail = head = new Link<E>;
            listSize = 0;
        }

        void removeAll(){
            while (head!=NULL){
                curr = head;
                head = head->next;
                delete curr;
            }
        }
    public:
        LList () { init(); }
        ~LList () { removeAll(); }

        void clear() {removeAll(); init(); }

        void moveToStart() { curr=head; }
        void moveToEnd() { curr=tail; }
        void prev(){
            if (curr=head) return;
            Link<E>* temp = head;
            while (temp->next!=curr) temp=temp->next;
            curr=temp;
        }
        void next(){ if (curr!=tail) curr=curr->next; }
        int currPos() const {
            Link<E>* temp = head;
            int i;
            for (i=0; curr!=temp; i++){
                temp = temp->next;
            }
            return i;
        }
        void moveToPos(int pos) {
            if (pos<0 || pos>listSize) return;
            curr = head;
            for (int i=0; i<0; i++) curr=curr->next;
        }
        const E& getValue() const {
            if (curr->next==NULL) exit(1);
            return curr->next->el;
        }
        void insert(const E& el) {
            curr->next = new Link<E> (el, curr->next);
            if (tail==curr) tail=curr->next;
            listSize++;
        }
        void append(const E& el){
            tail = tail->next = new Link<E>(el, NULL);
            listSize++;
        }
        E remove(){
            if (curr->next==NULL) exit(1);
            E el = curr->next->el;
            Link<E>* tempLink = curr->next;
            if (tail==curr->next) tail=curr;
            curr->next = curr->next->next;

            delete tempLink;
            listSize--;
            return el;
        }

        int length() const { return listSize; }

};

int main() {
    LList<int> a;

    // Insert elements into the list
    a.insert(10);
    a.insert(20);
    a.insert(30);

    // Move to the start of the list
    a.moveToStart();

    // Move to the end of the list
    a.moveToEnd();

    // Move to the previous element
    a.prev();

    // Move to the next element
    a.next();

    // Get the current position
    int currentPosition = a.currPos();
    std::cout << "Current Position: " << currentPosition << std::endl;

    // Move to a specific position
    a.moveToPos(1);

    // Get the value at the current position
    int value = a.getValue();
    std::cout << "Value at current position: " << value << std::endl;

    // Append an element to the list
    a.append(40);

    // Remove an element from the list
    int removedValue = a.remove();
    std::cout << "Removed Value: " << removedValue << std::endl;

    // Get the length of the list
    int listLength = a.length();
    std::cout << "List Length: " << listLength << std::endl;

    // Clear the list
    a.clear();
    std::cout << "List cleared." << std::endl;

    // Re-insert elements after clearing
    a.insert(50);
    a.insert(60);

    // Move to the start and iterate through the list
    a.moveToStart();
    while (a.currPos() < a.length()) {
        std::cout << "Current Value: " << a.getValue() << std::endl;
        a.next();
    }

    return 0;
}