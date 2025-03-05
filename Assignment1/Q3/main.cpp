#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
using namespace std;



struct Time {
    int hour;
    int minute;
    int second;

    static bool isFirstEarly(Time t1, Time t2) {
        if (t1.hour < t2.hour) return true;
        if (t1.hour == t2.hour) {
            if (t1.minute < t2.minute) return true;
            if (t1.minute == t2.minute) {
                return t1.second < t2.second;
            }
        }
        return false;
    }
};

struct ProcessData {
    int priorty_level;
    string process_name;
    Time time;
};

struct Node {
    ProcessData data;
    Node* next;
    Node* prev;

    Node(ProcessData data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};




class Queue {
public:
    int size;
    Node* front;

    Queue() {
        size = 0;
        front = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void Enqueue(ProcessData data) {
        size++;
        Node* newNode = new Node(data);

        // Case 1: If the list is empty or the new node has the highest priority, insert at front
        if (isEmpty() || front->data.priorty_level < data.priorty_level) {
            newNode->next = front;
            if (front != nullptr) {
                front->prev = newNode;
            }
            front = newNode;
            return;
        }

        Node* tmpNode = front;

        // Traverse to find the correct insertion point
        while (tmpNode->next != nullptr && tmpNode->data.priorty_level >= data.priorty_level) {
            if (tmpNode->data.priorty_level == data.priorty_level) {
                if (Time::isFirstEarly(data.time, tmpNode->data.time)) {
                    break; // Insert before tmpNode
                }
            }
            tmpNode = tmpNode->next;
        }

        // Insert newNode before tmpNode
        newNode->next = tmpNode;
        newNode->prev = tmpNode->prev;

        if (tmpNode->prev != nullptr) {
            tmpNode->prev->next = newNode;
        } else {
            front = newNode; // If inserting at front
        }

        tmpNode->prev = newNode;
    }


    void Dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cant perform dequeue\n";
            return;
        }

        Node* tmpNode = front;
        front = front->next;

        delete tmpNode;
        size--;
    }

    string getFirst() {
        return front->data.process_name;
    }

    void printQueue() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        Node* tmpNode = front;
        cout << "Queue Contents:\n";
        while (tmpNode != nullptr) {
            cout << "Process: " << tmpNode->data.process_name
                << " | Priority: " << tmpNode->data.priorty_level
                << " | Time: " << tmpNode->data.time.hour << ":"
                << tmpNode->data.time.minute << ":"
                << tmpNode->data.time.second << endl;

            tmpNode = tmpNode->next;
        }
    }


    ~Queue() {
        while(!isEmpty()) {
            Dequeue();
        }
    }
};

ProcessData getData(string process) {
    ProcessData data;
    stringstream ss(process);
    int count = 0; 
    while (getline(ss, process, ' ')) {
        switch(count) {
            case 0:
                data.process_name = process;
                break;
            case 1:
                data.priorty_level = stoi(process);
                break;
            case 2: 
                stringstream dd(process);
                int count2 = 0;
                while(getline(dd, process, ':')) {
                    switch(count2) {
                        case 0:
                            data.time.hour = stoi(process);
                            break;
                        case 1:
                            data.time.minute = stoi(process);
                            break;
                        case 2:
                            data.time.second = stoi(process);
                    }
                }
        }
        count++;
    }
    return data;
}

Queue readFile() {
    Queue q1;
    string filename = "process.txt";
    ifstream file(filename);
    
    string process;
    while(getline(file, process)) {
        q1.Enqueue(getData(process));
    }
    return q1;
}



int main() {
    Queue processQueue = readFile();
    processQueue.printQueue();
    processQueue.Dequeue();
    processQueue.Dequeue();
    processQueue.printQueue();
    return 0;
}