#include <iostream>
using namespace std;

long int getFactorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * getFactorial(n - 1);
}

int main() {
    int n;
    cout << "Enter number: ";
    cin >> n;

    long int factorial = getFactorial(n);
    cout << "Factorial = " << factorial << endl;

    return 0;

}