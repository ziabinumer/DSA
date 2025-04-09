#include <iostream>
using namespace std;

struct Node {
    int num;
    Node* next;
    Node* prev;

    Node(int n) {
        this->num = n;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class List {
public:
    Node* head;
    Node* tail;
    List() {
        head = tail = nullptr;
    }

    bool isEmpty() {
        if (head == nullptr) {
            return true;
        }
        return false;
    }

    void insertItem(int n) {
        Node* newNode = new Node(n);
        if (isEmpty()) {
            head = tail = newNode;
            return;
        }
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    void deleteLast() {
        if (isEmpty()) {
            return;
        }
        if (head == tail) {
            delete tail;
            tail = head = nullptr;
            return;
        }
        Node* secondLast = tail->prev;
        delete tail;
        tail = secondLast;
        tail->next = nullptr;
    }

    void deleteFirst() {
        if (isEmpty()) {
            return;
        }
        if (head == tail) {
            delete tail;
            tail = head = nullptr;
            return;
        }
        Node* tmpHead = head->next;
        delete head;
        head = tmpHead;
        head->prev = nullptr;
    }

    void deleteAtIndex(int index) {
        if (isEmpty()) {
            cout << "List empty\n";
            return;
        }
    
        if (index == 0) {  
            deleteFirst();  
            return;
        }
    
        int count = 0;
        Node* current = head;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
    
        if (current == nullptr) { 
            cout << "Index out of bounds." << endl;
            return;
        }
    
        // Handling removal of current node
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }
    
        // If we delete the tail node, we need to update the tail pointer
        if (current->next == nullptr) {
            tail = current->prev;
        }
    
        delete current;
    }

    void printList() {
        if (isEmpty()) {
            return;
        }
        cout << "Head: " << head->num << " Tail: " << tail->num << endl;
        Node* currentNode = head;
        while (currentNode != nullptr) {
            cout << "Current: " << currentNode->num << " | ";
    
            if (currentNode->prev != nullptr)
                cout << "prev: " << currentNode->prev->num << " | ";
            else
                cout << "prev: NULL | ";
    
            if (currentNode->next != nullptr)
                cout << "next: " << currentNode->next->num << endl;
            else
                cout << "next: NULL" << endl;
    
            currentNode = currentNode->next;
        }
    }

    ~List() {
        Node* tmpNode;
        while (head != nullptr) {
            tmpNode = head->next;
            delete head;
            head = tmpNode;
        }
    }
};

int main() {
    List list;

    for (int i = 0; i < 5; i++) {
        list.insertItem((i + 2) * 3 - 5);
    }

    list.printList();
    list.deleteAtIndex(0);
    list.printList();


    return 0;
}
