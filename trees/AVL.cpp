#include <iostream>
using namespace std;


struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int key) {
        this->key = key;
        this->height = 0;
        this->left = this->right = nullptr;
    }
};

class AVL {
public:
    Node* root;

    AVL() {
        this->root = nullptr;
    }

    // utility functions
    int getHeight(Node* node) {
        return node ? node->height : -1;
    }

    int getBF(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node* findMin(Node* node) {
        if (!node->left) return node;
        return findMin(node->left);
    }

    // rotation functions
    Node* rotateLeft(Node* node) {
        Node* right = node->right;
        Node* leftRight = right->left;

        right->left = node;
        node->right = leftRight;

        updateHeight(node);
        updateHeight(right);

        return right;

    }

    Node* rotateRight(Node* node) {
        Node* left = node->left;
        Node* rightLeft = left->right;

        left->right = node;
        node->left = rightLeft;

        updateHeight(left);
        updateHeight(node);

        return left;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int balanceFactor = getBF(node);
    
        // Left Heavy
        if (balanceFactor > 1) {
            if (getBF(node->left) < 0) {  // Left-Right case
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);  // Left-Left case
        }
    
        // Right Heavy
        if (balanceFactor < -1) {
            if (getBF(node->right) > 0) {  // Right-Left case
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);   // Right-Right case
        }
    
        // Already balanced
        return node;
    }
    


    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        
        if (key < node->key) {
            node->left = insert(node->left, key);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        else {
            return node;
        }

        return balance(node);
    }

    Node* deleteNode(Node* node, int key) {
        if (!node) return nullptr;
        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        }
        else {
            // case 1
            if (!node->left) {
                Node* rightNode = node->right;
                delete node;
                return rightNode;
            }
            else if (!node->right) {
                Node* leftNode = node->left;
                delete node;
                return leftNode;
            }
            else {
                Node* min = findMin(node->right);
                node->key = min->key;
                node->right = deleteNode(node->right, min->key);
            }
        }

        if (!node) return node;

        return balance(node);
    }

    Node* print(Node* node) {
        if (node != nullptr) {
            cout << node->key << " ";
            print(node->left);
            print(node->right);
        }
        return node;
    }
};








int main() {
    AVL a1;
    a1.root = a1.insert(a1.root, 15);
    a1.root = a1.insert(a1.root, 12);
    a1.root = a1.insert(a1.root, 9);
    a1.root = a1.insert(a1.root, 13);
    a1.print(a1.root);
    return 0;
}

/*
    bf = 1
                    
                    12
                9       15
                    13
                
*/