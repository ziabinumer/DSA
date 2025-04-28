// BST.cpp
#include "BST.h"

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    freeBST(root);
}

Node* BST::addHelper(Node* node, Course course) {
    if (!node) return new Node(course);

    int key = course.getId();
    if (key < node->key) {
        node->left = addHelper(node->left, course);
    }
    else if (key > node->key) {
        node->right = addHelper(node->right, course);
    }
    return node;
}

Node* BST::deleteHelper(Node* node, int key) {
    if (!node) return nullptr;

    if (key < node->key) {
        node->left = deleteHelper(node->left, key);
    }
    else if (key > node->key) {
        node->right = deleteHelper(node->right, key);
    }
    else {
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
            node->course = min->course;
            node->right = deleteHelper(node->right, min->key);
        }
    }
    return node;
}

Node* BST::searchHelper(Node* node, int key) {
    if (!node) return nullptr;

    if (key < node->key) {
        return searchHelper(node->left, key);
    }
    else if (key > node->key) {
        return searchHelper(node->right, key);
    }
    else {
        return node;
    }
}

Node* BST::findMin(Node* node) {
    if (!node) return nullptr;
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node* BST::minHelper(Node* node) {
    if (!node->left) return node;
    return minHelper(node->left);
}

Node* BST::maxHelper(Node* node) {
    if (!node->right) return node;
    return maxHelper(node->right);
}

void BST::displayHelper(Node* node) {
    if (!node) return;
    displayHelper(node->left);
    node->display();
    displayHelper(node->right);
}

int BST::totalHelper(Node* node) {
    if (!node) return 0;
    return 1 + totalHelper(node->left) + totalHelper(node->right);
}

int BST::Height(Node* node) {
    if (!node) return -1;
    return 1 + max(Height(node->left), Height(node->right));
}

void BST::freeBST(Node* node) {
    if (!node) return;
    freeBST(node->left);
    freeBST(node->right);
    delete node;
}

// PUBLIC METHODS
void BST::addCourse(Course course) {
    root = addHelper(root, course);
}

void BST::deleteCourse(int id) {
    root = deleteHelper(root, id);
}

bool BST::searchCourse(int id) {
    Node* node = searchHelper(root, id);
    if (!node) {
        cout << "Course with id " << id << " was not found" << endl;
        return false;
    }
    cout << "Found Course with Id " << id << endl;
    node->display();
    return true;
}

void BST::displayAscending() {
    displayHelper(root);
}

void BST::totalCourses() {
    cout << "Total courses: " << totalHelper(root) << endl;
}

void BST::minCourseId() {
    cout << "Min Id: " << minHelper(root)->key << endl;
}

void BST::maxCourseId() {
    cout << "Max Id: " << maxHelper(root)->key << endl;
}

int BST::treeHeight() {
    int height = Height(root);
    cout << "Height of Tree: " << height << endl;
    return height;
}
