#include <iostream>
using namespace std;

int main() {
    int arr[] = {-3,-2,-1,0,0,1,2,2,2};
    int size = sizeof(arr) / sizeof(int);

    int maxNeg = 0, maxPos = 0;

    for (int i = 0; i < size / 2; i++) {
        if (arr[i] < 0) {
            maxNeg++;
        }
        else if (arr[i] > 0) maxPos++;
    }

    if (maxNeg >= maxPos) cout << maxNeg << endl;
    else cout << maxPos << endl;

    return 0;
}