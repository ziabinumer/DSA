// Solve the problem of equal a's and b's 
#include <iostream>
using namespace std;

struct Node {
    char c;
    Node* next;
    
    Node(char c) {
        this->c = c;
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

    char getTop() {
        if (isEmpty()) {
            return '\0';
        }
        return top->c;
    }

    void push(char c) {
        Node* newNode = new Node(c);

        newNode->next = top;

        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }

        Node* tmpNode = top;
        top = top->next;
        delete tmpNode;
    }

    // destructor
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

};

int main() {
    string st;
    cout << "Enter string: ";
    cin >> st;

    Stack astack, bstack;
    for (char c: st) {
        if (c == 'a') {
            astack.push(c);
        }
        if (c == 'b') {
            bstack.push(c);
        }
    }


    while (!astack.isEmpty() && !bstack.isEmpty()) {
        astack.pop();
        bstack.pop();
    }

    if (astack.isEmpty() && bstack.isEmpty()) {
        cout << "Equal number of a's and b's were found in " << st << endl;
    }
    else {
        cout << "Not equal number of a's and b's\n";
    }

    return 0;
}