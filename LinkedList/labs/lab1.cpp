#include <iostream>
using namespace std;

class Employee {
public:
    int id;
    string name, fatherName;
};

struct Node { 
    Employee e;
    Node* next;
};

class List {
public:
    Node *head;
    Employee data;
    
    List() {
        head = nullptr;
    }

    int getNumber(string message) {
        int n;
        cout << message;
        cin >> n;
        return n;
    }

    void getData() {
        cout << "\n-- Input Employee Data --\n";
        cout << "Enter id: ";
        cin >> data.id;
        cout << "Enter name: ";
        cin >> data.name;
        cout << "Enter father name: ";
        cin >> data.fatherName;
        cout << "\n--------------------------" << endl;
    }

    void printItem(Employee c) {
        cout << "ID: " << c.id << endl;
        cout << "Name: " << c.name << endl;
        cout << "Father Name: " << c.fatherName << endl << endl;
    }

    bool isEmpty() {
        return head == nullptr;
    }
    
    // create a node, assigns data and links to next node if given any
    Node* prepareNode(Node* next = nullptr) {
        getData();
        Node* newNode = new Node;
        newNode->e = data;
        newNode->next = next;
        return newNode;
    }

    void createHead() {
        head = prepareNode();
    }

    void insertItem() {
        if (isEmpty()) {
            createHead();
            return;
        }
        Node* currentNode = head;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        
        Node* newNode = prepareNode();
        currentNode->next = newNode;
    }

    void insertAtIndex() {
        int index = getNumber("Enter index: ");

        if (index == 0) {
            Node *newNode = prepareNode(head);
            head = newNode;
            return;
        }

        int i = 0;
        Node* currentNode = head;
        while (currentNode != nullptr && i < index - 1) {
            currentNode = currentNode->next;
            i++;
        }

        if (currentNode == nullptr) {
            cout << "\nIndex out of bound\n";
            return;
        }

        Node *newNode = prepareNode(currentNode->next);
        currentNode->next = newNode;

    }

    void insertAfterId() {
        int id = getNumber("Enter id to insert after: ");

        if (isEmpty()) {
            createHead();
            return;
        }

        Node* currentNode = head;

        while (currentNode != nullptr && currentNode->e.id != id) {
            currentNode = currentNode->next;
        }

        if (currentNode == nullptr) {
            cout << "\nCant find id\n";
            return;
        }

        Node *newNode = prepareNode(currentNode->next);
        currentNode->next = newNode;




    }

    void printList() {
        if (isEmpty()) {
            cout << "\nList is empty\n";
            return;
        }

        cout << "\n----- Printing List -------\n";
        Node* currentNode = head;


        while (currentNode != nullptr) {
            printItem(currentNode->e);
            currentNode = currentNode->next;
        }

        cout << "\n----- Done Printing --------\n";

        cout << endl;
    }

    void freeList() {
        while (head != nullptr) {
            Node *currentNode = head->next;
            delete head;
            head = currentNode;
        }
    }

};

int main() {
    List list;
    int choice;

    do {
        cout << "\n---- Employee List Menu ----\n";
        cout << "1. Insert Employee\n";
        cout << "2. Insert at Index\n";
        cout << "3. Insert After ID\n";
        cout << "4. Print List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                list.insertItem();
                break;
            case 2:
                list.insertAtIndex();
                break;
            case 3:
                list.insertAfterId();
                break;
            case 4:
                list.printList();
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 5);

    list.freeList();
    return 0;
}
