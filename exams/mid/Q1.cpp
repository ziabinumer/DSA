#include <iostream>
using namespace std;




struct Node {
    int value;
    Node* next;
    Node(int value) {
        this->value = value;
        this->next = nullptr;
    }
};

class Stack {
    public:
        Node* front;

        Stack() {
            front = nullptr;
        }

        bool Empty() {
            return front == nullptr;
        }

        int getTop() {
            if (!Empty())
            return front->value;
            else return '\0';
        }

        void push(int n) {
            Node* newNode = new Node(n);
            newNode->next = front;
            front = newNode;
        }

        void pop() {
            if (!Empty()) {
                Node* tmp = front->next;
                delete front;
                front = tmp;
            }
        }

        ~Stack() {
            while (!Empty()) {
                pop();
            }
        }

};

/*
    This approach is not good. (But i used it in exam)
    instead after pushing in s1. simply compare its every value with list
    while (current != nullptr) {
        if (s1.getTop() != current->value)
        {
            return false;
        }
        else s1.pop();
    }
    return true;
*/
bool PalindromeCheck(Node* head) {
    Stack s1, s2, s3;
    Node* current = head;
    while (current != nullptr) {
        s1.push(current->value);
        s2.push(current->value);
        current = current->next;
    }
    while (!s2.Empty()) {
        s3.push(s2.getTop());
        s2.pop();
    }

    while (!s1.Empty()) {
        if (s1.getTop() != s3.getTop()) return false;
        s1.pop();
        s3.pop();
    }
    return true;
}

class LinkedList {
    public: 
        Node* head;

        LinkedList() {
            head = nullptr;
        }

        void insert(int n) {
            Node* newNode = new Node(n);
            if (head == nullptr) {
                head = newNode;
                return;
            }
            Node* current = head;
            while (current -> next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
};

int main() {
        LinkedList l1;
        l1.insert(1);
        l1.insert(3);
        l1.insert(3);
        l1.insert(1);

        if (PalindromeCheck(l1.head)) {
            cout << "Palindrome" << endl;
        }
        else cout << "Not\n";
        return 0;
}