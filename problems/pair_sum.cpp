#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int arr[] = { 2, 3, 4, 18, 8, 9, 11, 15 };
    sort(begin(arr), end(arr));
    int size = sizeof(arr) / sizeof(arr[0]) - 1;
    int target_sum = 11;
    int s = 0, e = size, found = 0;
    int count = 0;

    while (s < e) {
        count++;
        if (arr[s] + arr[e] == target_sum) {
            found = 1;
            break;
        }
        else if (arr[s] + arr[e] < target_sum) {
            s++;
        }
        else if (arr[s] + arr[e] > target_sum) {
            e--;
        }
    }
    if (found)
    {
        cout << arr[s] << ","  << arr[e] << endl;
    }
    else {
        cout << "No pair\n";
    }
    cout << "Loop ran " << count << " times.\n";

    return 0;
}