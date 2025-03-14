#include <iostream>
using namespace std;

string fancyString(string s) {
    string newS = "";
    int count = 0;
    char prev = s[0];
    for (char c : s) {
        if (count == 2 && c == prev) {
            continue;
        }
        else if (c == prev) {
            count++;   
        }
        else {
            prev = c;
            count = 1;
        }
        newS += c;
    }
    return newS;
}

int main() {
    cout << fancyString("leeeeeetcode") << endl;
    return 0;
}