#include <iostream>
using namespace std;

const short int MAX_SIZE = 100;

int insertAtEnd(int arr[], int size, int num) {
    if (size < MAX_SIZE) {
        arr[size] = num;
        return size + 1;
    }
    cout << "SIZE EXCEEDED\n";
    return size;
}

int insertAtStart(int arr[], int size, int num) {
    if (size < MAX_SIZE) {
        for (int i = size; i > 0; i--) {
            arr[i] = arr[i - 1];
        }
        arr[0] = num;
        return size + 1;
    }
    cout << "SIZE EXCEEDED\n";
    return size;
}

/*
1,2,3,4
size = 4, num = 0

if (4 < 100) {
    for (i = 4; i > 0; i--) {
        arr[4] = arr[3]
    }
}
*/


int insertAtIndex(int arr[], int size, int index, int num) {
    if (size < MAX_SIZE) {
        if (index <= size) {
            for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
            }
            arr[index] = num;
            return size + 1;
        }
        cout << "Index out of range\n";
        return size;
    }
    cout << "SIZE EXCEEDED\n";
    return size;
}

int deleteAtEnd(int size) {
    return size - 1;
}

int deleteAtFront(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = arr[i + 1];
    }
    return size - 1;
}

int deleteAtIndex(int arr[], int size, int index) {
    if (index < size) {
        for (int i = index; i < size; i++) {
            arr[i] = arr[i + 1];
        }
        return size - 1;
    }
    cout << "Index out of range\n";
    return size;
}
/*
1,2,3,4,5

    1,2,4,5, size = 4, num = 3, index = 2
    i = 4, i > 2: arr[4] = arr[3] ----- 1,2,4,5,5
    i = 3, i > 2: arr[3] = arr[2] ----- 1,2,4,4,5
    i = 2: arr[2] = 3 ----------------- 1,2,3,4,5

    1,2,3,4,5
    1 = 2, 2= 3, 
*/

int main() {
    int arr[MAX_SIZE];
    int size = 0;
    size = insertAtEnd(arr, size, 4);
    size = insertAtStart(arr, size, 3);
    size = insertAtStart(arr, size, 2);
    size = insertAtEnd(arr, size, 5);
    size = insertAtEnd(arr, size, 6);
    size = insertAtEnd(arr, size, 7);
    size = insertAtIndex(arr, size, 3, 11);

    size = deleteAtEnd(size);
    size = deleteAtFront(arr, size);
    size = deleteAtIndex(arr, size, 4);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << endl;
    }


    return 0;
}