#include <iostream>
using namespace std;

double pow(double x, double n) {
    double result = 1.0;
    long binForm = n;
    if (binForm < 0) {
        x = 1 / x;
        binForm = -binForm;
    }
    while (binForm > 0) {
        
        if (binForm % 2 == 1) {
            result *= x;
        }
        x *= x;
        binForm /= 2;
    }
    if (n < 0) return 1 / result;
    return result;
}

int main() {
    double r = pow(2.0,10);
    cout << "result: " << r << endl;
    return 0;
}