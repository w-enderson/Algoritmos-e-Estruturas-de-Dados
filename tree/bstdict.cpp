#include <iostream>

using namespace std;

class Node {
	public:
		int key;
		int el;	
		Node* left;
		Node* right;

		Node(int k, int e): el(e), key(k), left(nullptr), right(nullptr) { 
		}
		~Node() {
			if (left!=nullptr) {
	            delete left;
	            left=nullptr;
	        }
	        if (right!=nullptr) {
	            delete right;
	            right=nullptr;
	        }
		}
};


class BST {
	private:
		Node* root = nullptr;
		int contNodes = 0;

		int findhelp(Node* root, int k){
			if(root==nullptr) return -1;
			if(root->key > k) return findhelp(root->left, k);
			else if (root->key == k) return root->el;
			else return findhelp(root->right, k);
		}
		Node* inserthelp(Node* root, int k, int v){
			if(root==nullptr) return new Node(k, v);
			if(root->key > k) root->left = inserthelp(root->left, k, v);
			else root->right = inserthelp(root->right, k, v);

			return root;
		}

		Node* getmin(Node* root){
			if(root->left==nullptr) return root;
			return getmin(root->left);
		}
		Node* deletemin(Node* root){
			if(root->left==nullptr) return root->right;
			root->left = deletemin(root->left);
			return root;
		}
		Node* removehelp(Node* root, int k){
			if (root==nullptr) return nullptr;

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
			return root;
		}

		void inorder(Node* root){
			if(root!=nullptr){
				inorder(root->left);
				cout << root->key  << ", ";
				inorder(root->right);
			}
		}
		void posorder(Node* root){
			if(root!=nullptr){
				posorder(root->left);
				posorder(root->right);
				cout << root->key  << ", ";
			}
		}
		void preorder(Node* root){
			if(root!=nullptr){
				cout << root->key  << ", ";
				preorder(root->left);
				preorder(root->right);
			}
		}
	public:
		BST() {}
		~BST() {
        	delete root;
    	    root = nullptr;
    	}
		int find(int k){
			return findhelp(root, k);
		}

		void insert(int k, int e) {
			root = inserthelp(root, k, e);
			contNodes++;
		}

		int remove(int k){
			int temp = findhelp(root, k);
			if (temp!=-1){
				root = removehelp(root, k);
				contNodes--;
			}
			return temp;
		}

		void print() {
			inorder(root);
			cout<<endl;
			preorder(root);
			cout<<endl;
			posorder(root);
			cout<<endl;

		}

};

int main() {
    BST tree;

    // Inserção de vários elementos
    tree.insert(50, 500);
    tree.insert(30, 300);
    tree.insert(70, 700);
    tree.insert(20, 200);
    tree.insert(40, 400);
    tree.insert(60, 600);
    tree.insert(80, 800);
    tree.insert(10, 100);
    tree.insert(90, 900);
    tree.insert(55, 550);
    tree.insert(65, 650);

    // Impressão da árvore após inserção
    cout << "Árvore após inserção de vários elementos:" << endl;
    tree.print();

    // Busca por elementos presentes e ausentes
    int chaveBusca = 30;
    cout << "Busca pela chave " << chaveBusca << ": " << tree.find(chaveBusca) << endl;
    chaveBusca = 85;
    cout << "Busca pela chave " << chaveBusca << ": " << tree.find(chaveBusca) << endl;

    // Remoção de nós com diferentes configurações de filhos
    int chaveRemocao = 20;
    tree.remove(chaveRemocao);
    cout << "Árvore após remoção da chave " << chaveRemocao << ":" << endl;
    tree.print();

    chaveRemocao = 70;
    tree.remove(chaveRemocao);
    cout << "Árvore após remoção da chave " << chaveRemocao << ":" << endl;
    tree.print();

    chaveRemocao = 50;
    tree.remove(chaveRemocao);
    cout << "Árvore após remoção da chave " << chaveRemocao << ":" << endl;
    tree.print();

    return 0;
}