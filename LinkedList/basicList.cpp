#include <iostream>
using namespace std;

class Node {
    public:
        int number;
        Node* next;
};

Node* prepareNode(int n, Node *next = nullptr) {
    Node *newNode = new Node;
    newNode->number = n;
    newNode->next = next;
    return newNode;
}

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
    Node *newNode = prepareNode(n);

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

void insertAtFront(Node *&head) {
    int n = getNumber();

    Node* newNode = prepareNode(n, head);

    head = newNode;
}

void insertAtIndex(Node *&head) {
    int n = getNumber();
    cout << "(expecting index)\n";
    int index = getNumber();

    Node* newNode = prepareNode(n);

    if (index == 0) {
        insertAtFront(head);
        return;
    }

    /*
        head: 2, ->2nd
        2nd: 8, ->3rd
        3rd: 4, -> 4th
        4th: 12, -> NULL

        tmpNode = 2, ->2nd
        i = 0
        index = 2

        while (2nd != NULL && 0 < 1) /tmpNode->next = NULL/ {
            tmpNode = tmpNode->next;
            i++;
        }
        i = 1;
        tmpNode = 8, 3rd;
        3rd != NULL && 1 < 1 false
        break

        newNode->tmpNode->next; newNode -> 3rd
        tmpNode->newNode; 
    
    */

    Node* tmpNode = head;
    int i = 0;
    while (tmpNode->next != NULL && i < index - 1) {
        tmpNode = tmpNode->next;
        i++;
    }

    if (tmpNode == NULL) {
        cout << "Index out of bound\n";
        delete newNode;
        return;
    }

    newNode->next = tmpNode->next;
    tmpNode->next = newNode;

}

void deleteLastElement(Node *&head) {
    if (head == NULL) {
        cout << "Empty already" << endl;
        return;
    }
    else if (head->next == NULL) {
        delete head;
        head = NULL;
        return;
    }
    Node *tmpNode = head;
    while (tmpNode->next->next != NULL) {
        tmpNode = tmpNode->next;
    }

    delete tmpNode->next; // delete last element
    tmpNode->next = NULL;

}

void deleteFirstElement(Node *&head) {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }
    Node *first = head;
    head = head->next;
    delete first;
}



void deleteAtIndex(Node *&head) {
    cout << "(expecting index)\n";
    int index = getNumber();

    if (head == NULL) {
        cout << "List empty. cant delete anything\n";
        return;
    }

    Node* tmpNode = head;
    if (index == 0) {
        
        head = head->next;
        delete tmpNode;
        return;
    }

    int i = 0;
    while (tmpNode->next != NULL && i < index - 1) {
        tmpNode = tmpNode->next;
        i++;
    }

    if (tmpNode->next == NULL) {
        cout << "Index out of bound exception\n";
        return;
    }

    Node *nodeToDelete = tmpNode->next;
    tmpNode->next = tmpNode->next->next;
    delete nodeToDelete;
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

    insertAtFront(head);

    displayElements(head);


    freeList(head);
    return 0;
}