#include <iostream>
using namespace std;

struct Node {
    int n;
    Node* next;
    Node(int n) {
        this->n = n;
        this->next = nullptr;
    }
};


class Queue {
public:
    int size;
    Node* front;
    Node* rear;

    Queue() {
        front =  nullptr;
        rear = nullptr;
        size = 0;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int n) {
        size++;
        Node* newNode = new Node(n);
        if (isEmpty()) {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Underflow\n";
            return;
        }

        Node* tmpNode = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete tmpNode;

        size--;
    }

    int getSize() {
        return size;
    }

    int getFront() {
        if (isEmpty()) {
            cout << "Queue Empty\n";
            return -1;
        }
        return front->n;
    }

    int getRear() {
        if (isEmpty()) {
            cout << "Queue Empty\n";
            return -1;
        }
        return rear->n;
    }

    void printQueue() {
        if (isEmpty()) {
            cout << "Queue Empty\n";
            return;
        }

        Node* tmpNode = front;

        while (tmpNode != nullptr) {
            cout << tmpNode->n << " ";
            tmpNode = tmpNode->next;
        }
        cout << endl;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};


int main() {
    Queue q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.printQueue();
    q1.dequeue();
    cout << q1.getFront() << endl;
    cout << q1.getRear() << endl;
    cout << q1.getSize() << endl;
    return 0;
}