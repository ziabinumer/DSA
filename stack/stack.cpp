#include <iostream>
using namespace std;

class Stack {
    public:
    int arr[6];
    int top;

    Stack() {
        top = -1;
    }

    void push() {
        int n;
        cout << "Enter number: ";
        cin >> n;

        top++;
        arr[top] = n;
    }

    void pop() {
        top--;
    }

    void print() {
        for (int i = top; i > -1; i--) {
            cout << arr[i] << endl;
        }
        cout << endl;
    }
};

int main() {
    Stack s;
    s.push();
    s.push();
    s.print();
    s.pop();
    s.print();

}