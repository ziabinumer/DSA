#include "AVL.h"

int AVL::getBalanceFactor(Node* node) {
    if (!node) return 0;
    return (Height(node->left) - Height(node->right));
}

void AVL::inorderBalanceFactor(Node* node) {
    if (!node) return;
    cout << "Balance Factor of " << node->course.getId() << " : " << getBalanceFactor(node) << endl;
    inorderBalanceFactor(node->left);
    inorderBalanceFactor(node->right);
}

Node* AVL::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    return newRoot;
}

Node* AVL::rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    return newRoot;
}

Node* AVL::addHelper(Node* node, Course course) {
    if (!node) return new Node(course);

    int key = course.getId();
    if (key < node->key) {
        node->left = addHelper(node->left, course);
    }
    else if (key > node->key) {
        node->right = addHelper(node->right, course);
    }
    else {
        // duplication not allowed
        return node;
    }

    cout << "Printing Balance Factor after insertion (before balanceing) \n";
    inorderBalanceFactor(root);


    return AVL::balance(node);
}

Node* AVL::deleteHelper(Node* node, int key) {
    if (!node) return nullptr;
    
    if (key < node->key) {
        node->left = deleteHelper(node->left, key);
    }
    else if (key > node->key) {
        node->right = deleteHelper(node->right, key);
    }
    else {
        // delete 
        if (!node->left) { // only right child exists
            Node* rightNode = node->right;
            delete node;
            return rightNode;
        }
        if (!node->right) { // only left child exists
            Node* leftNode = node->left;
            delete node;
            return leftNode;
        }
        else { // both children exist
            Node* min = BST::findMin(node);

            // set values min to node that needs to be deleted
            node->key = min->key;
            node->course = min->course;

            node->right = deleteHelper(node->right, min->key);
        }
    }
    if (!node) return node;

    cout << "Printing Balance Factor after deletion (before balanceing) \n";
    inorderBalanceFactor(root);

    return AVL::balance(node);
}

Node* AVL::balance(Node* node) {
    int balanceFactor = getBalanceFactor(node);

    // left heavy
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) >= 0) {
            // Left Left Case
            return rotateRight(node);
        }
        else {
            // Left Right Case
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    // right heavy
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) <= 0) {
            // Right Right Case
            return rotateLeft(node);
        }
        else {
            // Right Left Case
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }


    return node;
}
