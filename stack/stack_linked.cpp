#include <iostream>
using namespace std;

struct Node {
    int number;
    Node* next;

    Node(int number) {
        this->number = number;
        this->next = nullptr;
    }
};

class Stack {
public:
    Node* top; 

    Stack() {
        top = nullptr;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int n) {
        Node* newNode = new Node(n);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack empty. Cant perform pop.\n";
            return;
        }
        Node* tmpNode = top;
        top = top->next;

        delete tmpNode;
    }
};

int main() {
    Stack s1;
    s1.push(1);
    return 0;
}