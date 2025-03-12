#include <iostream>
#include <vector>
using namespace std;

int getFibonacci(int h) {
    if (h <= 1) {
        return h;
    }
    return (getFibonacci(h - 1) + getFibonacci(h - 2));
}

int main() {
    int h;
    cout << "Enter height: ";
    cin >> h;
    h--;

    vector<int> fibonacci;
    while (h >= 0) {
        fibonacci.push_back(getFibonacci(h));
        h--;
    }
    for (auto n: fibonacci) {
        cout << n << endl;
    }

    return 0;

}

/*
0, 1, 1, 2, 3, 5, 8, 13
*/