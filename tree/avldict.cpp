#include <iostream>
#include <algorithm>

using namespace std;

class Node {
public:
    int key;
    int el;
    int height;
    Node* left;
    Node* right;

    Node(int k, int e) : key(k), el(e), height(1), left(nullptr), right(nullptr) { }
    ~Node() {
        if (left != nullptr) {
            delete left;
            left = nullptr;
        }
        if (right != nullptr) {
            delete right;
            right = nullptr;
        }
    }
};

class AVL {
private:
    Node* root = nullptr;
    int contNodes = 0;

    int h(Node* root) {
        if (root == nullptr) return 0;
        return root->height;
    }

    int getBalance(Node* root) {
        if (root == nullptr) return 0;
        return h(root->left) - h(root->right);
    }

    Node* right(Node* rt) {
        Node* l = rt->left;
        Node* lr = l->right;
        l->right = rt;
        rt->left = lr;
        rt->height = 1 + max(h(rt->left), h(rt->right));
        l->height = 1 + max(h(l->left), h(l->right));
        return l;
    }

    Node* left(Node* rt) {
        Node* r = rt->right;
        Node* rl = r->left;
        r->left = rt;
        rt->right = rl;
        rt->height = 1 + max(h(rt->left), h(rt->right));
        r->height = 1 + max(h(r->left), h(r->right));
        return r;
    }

    Node* inserthelp(Node* root, int k, int e) {
        if (root == nullptr) return new Node(k, e);
        if (root->key > k) root->left = inserthelp(root->left, k, e);
        else root->right = inserthelp(root->right, k, e);

        root->height = 1 + max(h(root->left), h(root->right));
        int balance = getBalance(root);

        if (balance < -1 && k >= root->right->key) return left(root);
        if (balance > 1 && k < root->left->key) return right(root);

        if (balance > 1 && k >= root->left->key) {
            root->left = left(root->left);
            return right(root);
        }
        if (balance < -1 && k < root->right->key) {
            root->right = right(root->right);
            return left(root);
        }

        return root;
    }

    int findhelp(Node* root, int k) {
        if (root == nullptr) return -1;
        if (root->key > k) return findhelp(root->left, k);
        else if (root->key == k) return root->el;
        else return findhelp(root->right, k);
    }

    Node* getmin(Node* root) {
        if (root->left == nullptr) return root;
        return getmin(root->left);
    }

    Node* deletemin(Node* root) {
        if (root->left == nullptr) return root->right;
        root->left = deletemin(root->left);
        return root;
    }

    Node* removehelp(Node* root, int k) {
        if (root == nullptr) return nullptr;

        if (root->key > k) root->left = removehelp(root->left, k);
        else if (root->key < k) root->right = removehelp(root->right, k);
        else if (root->left == nullptr) return root->right;
        else if (root->right == nullptr) return root->left;
        else {
            Node* temp = getmin(root->right);
            root->el = temp->el;
            root->key = temp->key;
            root->right = deletemin(root->right);
        }

        root->height = 1 + max(h(root->left), h(root->right));
        int balance = getBalance(root);

        if (balance < -1 && getBalance(root->right) <= 0) return left(root);
        if (balance > 1 && getBalance(root->left) >= 0) return right(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = left(root->left);
            return right(root);
        }
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = right(root->right);
            return left(root);
        }

        return root;
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->key << ", ";
            inorder(root->right);
        }
    }

    void posorder(Node* root) {
        if (root != nullptr) {
            posorder(root->left);
            posorder(root->right);
            cout << root->key << ", ";
        }
    }

    void preorder(Node* root) {
        if (root != nullptr) {
            cout << root->key << ", ";
            preorder(root->left);
            preorder(root->right);
        }
    }

public:
    AVL() {}
    ~AVL() {
        delete root;
        root = nullptr;
    }

    void insert(int k, int e) {
        root = inserthelp(root, k, e);
        contNodes++;
    }

    void remove(int k) {
        root = removehelp(root, k);
        contNodes--;
    }

    int find(int k) {
        return findhelp(root, k);
    }

    void print() {
        inorder(root);
        cout << endl;
        preorder(root);
        cout << endl;
        posorder(root);
        cout << endl;
    }

    void printTree(Node* node, string indent = "", bool last = true) {
        if (node != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << node->key << endl;
            printTree(node->left, indent, false);
            printTree(node->right, indent, true);
        }
    }

    Node* getRoot() {
        return root;
    }

    bool isBalanced(Node* root) {
        if (root == nullptr) return true;
        int balance = getBalance(root);
        if (balance > 1 || balance < -1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
};

int main() {
    AVL tree;
    cout << "Initial tree:" << endl;
    tree.printTree(tree.getRoot());
    tree.insert(10, 1);
    cout << "After inserting 10:" << endl;
    tree.printTree(tree.getRoot());
    tree.insert(20, 2);
    cout << "After inserting 20:" << endl;
    tree.printTree(tree.getRoot());
    tree.insert(30, 3);
    cout << "After inserting 30:" << endl;
    tree.printTree(tree.getRoot());
    tree.insert(40, 4);
    cout << "After inserting 40:" << endl;
    tree.printTree(tree.getRoot());
    tree.insert(50, 5);
    cout << "After inserting 50:" << endl;
    tree.printTree(tree.getRoot());
    tree.insert(25, 6);
    cout << "After inserting 25:" << endl;
    tree.printTree(tree.getRoot());

    tree.remove(10);
    cout << "After removing 10:" << endl;
    tree.printTree(tree.getRoot());

    tree.remove(20);
    cout << "After removing 20:" << endl;
    tree.printTree(tree.getRoot());

    tree.remove(30);
    cout << "After removing 30:" << endl;
    tree.printTree(tree.getRoot());

    return 0;
}
