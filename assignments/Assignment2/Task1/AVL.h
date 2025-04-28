#pragma once
#include "BST.h"

class AVL : public BST {
private:
    int getBalanceFactor(Node* node);
    void inorderBalanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* balance(Node* node);
    
public:
    AVL() : BST() {}
    Node* addHelper(Node* node, Course course) override;
    Node* deleteHelper(Node* node, int key) override;
};