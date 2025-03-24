#include <iostream>
using namespace std;

struct Node {
    int num;
    Node* left;
    Node* right;

    Node(int n) {
        this->num = n;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class Tree {
public:
    Node* root;

    Tree() {
        root = nullptr;
    }

    void insertNode(int n) {
        root = insertNodeHelper(n, root);
    }

    Node* insertNodeHelper(int n, Node* node) {
        if (node == nullptr) {
            return new Node(n);
        }
        cout << "root: " << node->num << endl;
        if (n < node->num) {
            node->left = insertNodeHelper(n, node->left);
        }
        else {
            node->right = insertNodeHelper(n, node->right);
            // root->right = insertNodeHelper(4, root->right)
            // root->right = insertNodeHelper()
            // 
        }

        return node;
    }

    Node* search(Node* node = nullptr, int key = -1) {
        if (node != nullptr) {
            if (node->num == key) {
                return node;
            }
            if (node->num > key) {
                search(node->left, key);
            }
            else {
                search(node->right, key);
            }
        }
        return node;
    }

    void print(Node* node = nullptr) {
        if (node != nullptr) {
            cout << node->num << endl;
            print(node->left);
            print(node->right);
            
        }
    }
};


int main() {
    Tree tree;
    tree.insertNode(8);
    tree.insertNode(3);
    tree.insertNode(4);
    tree.insertNode(12);
    tree.insertNode(9);
    tree.insertNode(13);
    Node* root = tree.search(tree.root, 21);
    if (root == nullptr) cout << "Not found\n";
    else cout << root->num << endl;
    return 0;
}

/*
            2
        1       4
    -1              6

    to insert 3
    right = insert(3, 2r-right) 4r
            left = insert(3, 4r-left) null
                    insert(3, null)
                    return node
            left = node;
            right = 


*/