#include <iostream>
using namespace std;

const int SIZE = 9;

int main() {
    int arr[SIZE] = { -2, 1, 3, 4, -1, 2, 1, -2, 4 };

    int current_sum = arr[0];
    int max_sum = arr[0];
    int start_index = 0, temp_start = 0, end_index = 0;

    for (int i = 1; i < SIZE; i++) {
        if (current_sum + arr[i] < arr[i]) {
            current_sum = arr[i];
            temp_start = i; 
        } else {
            current_sum += arr[i];
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
            start_index = temp_start;
            end_index = i;
        }
    }


    cout << "Maximum sum subarray: ";
    for (int i = start_index; i <= end_index; i++) {
        cout << arr[i] << " ";
    }
    cout << "\nMax sum: " << max_sum << endl;

    return 0;
}
