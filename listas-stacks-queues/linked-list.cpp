#include <iostream>

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
            if (curr->next==NULL) return -1;
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
            if (curr->next==NULL) return -1;
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
    LList <int> a;
    a.insert(11);
    a.insert(11);
    a.insert(11);
    a.remove();

    return 0;
}