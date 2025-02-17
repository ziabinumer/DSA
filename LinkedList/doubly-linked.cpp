#include <iostream>
using namespace std;

struct Node {
    int number;
    Node* next;
    Node* prev;
};

class DoublyLinked {
    public:
    Node* head;
    Node* tail;

    DoublyLinked() {
        head = nullptr;
        tail = nullptr;
    }

    int getNumber() {
        int n;
        cout << "enter number: ";
        cin >> n;
        return n;
    }

    Node* createNode(int n, Node *next = nullptr, Node *prev = nullptr) {
        Node* newNode = new Node;
        newNode->number = n;
        newNode->next = next;
        newNode->prev = prev;
        return newNode;
    }

    bool isEmpty() {
        return this->head == nullptr ? true : false;
    }

    void createList(int n) {

        // prepare the node 
        Node* newNode = createNode(n);
        this->head = newNode;
        this->tail = newNode;
    }   

    void insertItem() {
        int n = getNumber();

        
        if (isEmpty()) {
            createList(n);
            return;
        }

        // prepare Node to insert
        Node* newNode = createNode(n, nullptr, tail);

        tail->next = newNode;
        tail = newNode;
    }

    void deleteLastItem() {
        if (isEmpty()) {
            cout << "List is empty\n";
            return;
        }

        Node* tmpNode = tail;
        if (tail == head) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            this->tail = tail->prev;
            this->tail->next = nullptr;
        }
        delete tmpNode;
    }

    void displayElements() {
        if (isEmpty()) {
            cout << "List is empty\n";
            return;
        }
        Node* tmpNode = this->head;
        
        while(tmpNode != NULL) {
            cout << tmpNode->number << endl;
            tmpNode = tmpNode->next;
        }

        cout << endl;
    }


    void freeList() {
        if (isEmpty()) {
            return;
        }
        while (this->head != nullptr) {
            Node* tmpNode = head->next;
            delete head;
            head = tmpNode;
        }
        tail = nullptr;
    }
};


int main() {
    DoublyLinked list;
    list.insertItem();
    list.insertItem();
    list.insertItem();
    list.deleteLastItem();
    list.displayElements();
    
    list.freeList();
    return 0;
}