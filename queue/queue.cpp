#include <iostream>
#include <list>
using namespace std;

class Queue {
public:
    list<int> queue;

    void Enqueue(int n) {
        queue.push_front(n); 
    }

    void Dequeue() {
        queue.pop_back();
    }

    void Print() {
        for (int n : queue) {
            cout << n << " ";
        }
        cout << endl;
    }
};



int main() {
    Queue q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Print();

    q.Dequeue();
    q.Dequeue();
    q.Print();

    return 0;
}