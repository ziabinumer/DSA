#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int key) {
        this->key = key;
        this->left = this->right = nullptr;
    }
};

class BST {
public:
    Node* root;
    vector<int> path;
    int counter;

    BST() {
        root = nullptr;
        counter = 0;
    }

    ~BST() {
        freeBST(root);
    }

    bool empty() {
        return root == nullptr;
    }

    void insert(int key) {
        root = insertHelper(key, root);
    }
    void remove(int key) {
        root = removeHelper(key, root);
    }
    void search(int key) {
        searchHelper(key, root);
    };

    void print() {
        printHelper(root);
    }


    // helpers

    bool leafNode(Node* node) {
        return node->left == nullptr && node->right == nullptr;
    }
    int height(Node* node) {
        if (node == nullptr) {
            return -1;
        }
        counter++;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        
        return max(leftHeight, rightHeight) + 1;
    }

    Node* minInorderPred(Node* node) {
        if (node->right == nullptr) {
            return node;
        }
        return minInorderPred(node->right);

    }

    Node* insertHelper(int key, Node* node) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key <= node->key) {
            node->left = insertHelper(key, node->left);
        }
        else if (key >= node->key) {
            node->right = insertHelper(key, node->right);
        }

        return node;
    };

    /*
        6
    6
6
    */

    Node* removeHelper(int key, Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->left = removeHelper(key, node->left);
        }
        else if (key > node->key) {
            node->right = removeHelper(key, node->right);
        }
        else {
            // case 1
            if (leafNode(node)) {
                delete node;
                return nullptr;
            }
            // case 2
            else if (node->left == nullptr) {
                Node* rightNode = node->right;
                delete node;
                return rightNode;
            }
            // case 3
            else if (node->right == nullptr) {
                Node* leftNode = node->left;
                delete node;
                return leftNode;
            }
            // case 4 (both child exist)
            else {
               Node* pred = minInorderPred(node->left);
               node->key = pred->key;
               node->left = removeHelper(pred->key, node->left);
            }
        }
        return node;
    }


    Node* searchHelper(int key, Node* node) {
        path.push_back(node->key);
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            searchHelper(key, node->left);
        }
        else if (key > node->key) {
            searchHelper(key, node->right);
        }
        else {
            cout << "Found key " << key << " in " << path.size() << " iterations" << endl << "Path: ";
            for (auto item : path) {
                cout << item;
                if (item != key) {
                    cout << " > ";
                }
            }
            cout << endl;
            while(!path.empty()) {
                path.pop_back();
            }
            
        }
        return node;
    }

    void printHelper(Node* node) {
        if (node != nullptr) {
            cout << node->key << "  ";
            printHelper(node->left);
            printHelper(node->right);
        }
    }

    void freeBST(Node* node) {
        if (node == nullptr) return;

        freeBST(node->left);
        freeBST(node->right);
        delete node;
    }
};


int main() {
    BST b1;

    /**
      88
    5                111
  3   15            100  222
2        18       99  109   322
            45   
                55
          35        75
        
     */
    b1.insert(88);
    b1.insert(5);
    b1.insert(3);
    b1.insert(15);
    b1.insert(18);
    b1.insert(156);
    b1.insert(2);
    b1.insert(111);
    b1.insert(45);
    b1.insert(55);
    b1.insert(35);
    b1.insert(75);
    b1.insert(25);
    b1.insert(222);
    b1.insert(322);
    b1.insert(100);
    b1.insert(99);
    b1.insert(109);

    b1.print();
    cout << endl;

    b1.remove(18);
    b1.remove(156);
    b1.remove(25);
    
    b1.insert(1);
    b1.insert(88);

    b1.search(75);

    cout << "height: " << b1.height(b1.root) << endl;
    cout << endl;



    return 0;
}