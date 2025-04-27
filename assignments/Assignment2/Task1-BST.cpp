#include <iostream>
using namespace std;

class Course {
    int courseId;
    string courseName;
    int crHours;


public:
    Course(int id, string name, int hours) : courseId(id), courseName(name), crHours(hours) {}
    Course() {}

    // getters
    int getId() { return courseId;}
    string getName() {return courseName;}
    int getHours() {return crHours;}

    // setters
    void setId(int id) {courseId = id;}
    void setName(string name) {courseName = name;}
    void setHours(int hours) {crHours = hours;}

};

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
};

class BST {
    Node* root;

    // utility functions
    Node* findMin(Node* node) {
        if (!node->left) return node;
        return findMin(node->left);
    }

    // helpers
    Node* addHelper(Node* node, Course course) {
        if (!node) return new Node(course); // create new node

        int key = course.getId();
        if (key < node->key) {
            node->left = addHelper(node->left, course);
        }
        else if (key > node->key) {
            node->right = addHelper(node->right, course);
        }
        return node;
    }

    Node* deleteHelper(Node* node, int key) {
        if (!node) return nullptr;
        
        if (key < node->key) {
            node->left = deleteHelper(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteHelper(node->right, key);
        }
        else {
            // case 
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

    Node* searchHelper(Node* node, int key) {
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

    Node* displayHelper(Node* node) {
        return node;
    }

    int totalHelper(Node* node) {
        if (!node) return 0;
        return 1 + totalHelper(node->left) + totalHelper(node->right);
    }


    Node* minHelper(Node* node) {
        if (!node->left) return node;
        return minHelper(node->left);
    }

    Node* maxHelper(Node* node) {
        if (!node->right) return node;
        return maxHelper(node->right);
    }

    int Height(Node* node) {
        if (!node) {return -1;}
        return 1 + max(Height(node->left), Height(node->right));
    }

public:
    BST() {
        root = nullptr;
    }
    ~BST() {
        freeBST(root);
    }
    void freeBST(Node* node) {
        if (!node) return;
        freeBST(node->left);
        freeBST(node->right);
        delete node;
    }

    // operations
    void addCourse(Course course) {
        root = addHelper(root, course);
    }

    void deleteCourse(int id) {
        root = deleteHelper(root, id);
    }

    bool searchCourse(int id) {
        Node* node = searchHelper(root, id);
        if (!node) {  
            cout << "Course with id " << id << " was not found" << endl;
            return false;
        }
    
        cout << "Found Course with Id " << id << endl;
        cout << "----------------------------" << endl
             << "ID: " << id << endl
             << "Name: " << node->course.getName() << endl
             << "Cr Hours: " << node->course.getHours() << endl
             << "----------------------------" << endl;
    
        return true;
    }

    void displayAscending() {
        displayHelper(root);
    }

    void totalCourses() {
        cout << "Total courses: " << totalHelper(root) << endl;
    }

    void minCourseId() {
        cout << "Min Id: " << minHelper(root)->key << endl;
    }
    void maxCourseId() {
        cout << "Max Id: " << maxHelper(root)->key << endl;
    }
    int treeHeight() {
        int height = Height(root);
        cout << "Height of Tree: " << height << endl;
        return height;
    }
};

int main() {
    BST courseData;
    courseData.addCourse(Course(8, "DSA", 4));
    courseData.addCourse(Course(9, "IDS", 4));
    courseData.addCourse(Course(2, "IWVC", 3));
    courseData.addCourse(Course(10, "Algorithms", 3));
    courseData.addCourse(Course(12, "Database Systems", 4));
    courseData.addCourse(Course(15, "Operating Systems", 3));
    courseData.addCourse(Course(20, "Software Engineering", 4));
    courseData.addCourse(Course(5, "Computer Networks", 3));
    courseData.addCourse(Course(7, "Web Development", 3));
    courseData.addCourse(Course(18, "Artificial Intelligence", 4));
    courseData.addCourse(Course(25, "Data Structures", 3));
    courseData.addCourse(Course(30, "Discrete Mathematics", 3));
    courseData.addCourse(Course(13, "Computer Graphics", 4));

    courseData.searchCourse(13);
    courseData.deleteCourse(13);
    courseData.searchCourse(13);
    courseData.totalCourses();
    courseData.minCourseId();
    courseData.maxCourseId();
    courseData.treeHeight();
    
    return 0;
}