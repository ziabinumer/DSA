#pragma once
#include <iostream>
#include "Course.h"
using namespace std;

struct Node {
    int key;
    Course course;

    Node *left, *right;

    Node(Course course) {
        this->key = course.getId();
        this->course = course;
        this->left = nullptr;
        this->right = nullptr;
    }

    void display() {
        course.display();
    }
};

class BST {
protected:
    Node* root;

    virtual Node* addHelper(Node* node, Course course);
    virtual Node* deleteHelper(Node* node, int key);

    Node* searchHelper(Node* node, int key);
    void displayHelper(Node* node);
    Node* findMin(Node* node);
    Node* minHelper(Node* node);
    Node* maxHelper(Node* node);
    int totalHelper(Node* node);
    int Height(Node* node);
    void freeBST(Node* node);

public:
    BST();
    virtual ~BST();

    void addCourse(Course course);
    void deleteCourse(int id);
    bool searchCourse(int id);
    void displayAscending();
    void totalCourses();
    void minCourseId();
    void maxCourseId();
    int treeHeight();
};


