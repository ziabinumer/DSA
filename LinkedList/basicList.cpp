#include <iostream>
using namespace std;

class Node {
    public:
        int number;
        Node* next;
};

int getNumber() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    return n;
}

void appendElement(Node *&head) {
    // get number to append
    int n = getNumber();

    // prepare the new node
    Node *newNode = new Node;
    newNode->number = n;
    newNode->next = NULL;

    // append the element
    if (head == NULL) {
        head = newNode;
    }
    else {
        Node *tmpNode = head;
        while (tmpNode->next != NULL) {
            tmpNode = tmpNode->next;
        }
        tmpNode->next = newNode;
    }
   
}

void displayElements(Node *head) {
    Node* tmpNode = head;
    if (tmpNode == NULL) {
        cout << "Nothing in the list right now. ";
        return;
    }
    else {
        while(tmpNode != NULL) {
            cout << tmpNode->number << endl;
            tmpNode = tmpNode->next;
        }
    }

    cout << endl;
}

void freeList(Node *&head) {
    while (head != NULL) {
        Node *tmpNode = head->next;
        delete head;
        head = tmpNode;
    }
}

int main() {
    Node *head = NULL;
    while (true) {
        appendElement(head);
        char c;
        cout << "Do you want to continue adding the elements: ";
        cin >> c;
        if (c != 'y') {
            break;
        }
    }


    displayElements(head);

    freeList(head);
    return 0;
}