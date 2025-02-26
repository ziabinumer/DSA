#include <iostream>
#include <stack>
using namespace std;

bool isNumber(char c) {
    if (c - '0' >= 0 && c - '0' <= 9) {
        return true;
    }
    return false;
}
bool isOperator(char c) {
    switch(c) {
        case '%':
        case '/':
        case '*':
        case '-':
        case '+':
            return true;
    }
    return false;
}

int precedence(char current) {
    if (current == '/' || current == '*' || current == '%') {
        return 2;
    }
    if (current == '+' || current == '-') {
        return 1;
    }
    else return -1;
}

int calculator(char c, int v1, int v2) {
    switch(c) {
        case '+':
            return v1 + v2;
        case '-':
            return v1 - v2;
        case '*':
            return v1 * v2;
        case '/':
            return v1 / v2;
        case '%':
            return v1 % v2;
    };
    return INT_MIN;
}

string convert(string exp) {
    stack<char> st;
    string newExp = "";
    int expLength = exp.length();

    //
    for (int i = 0; i < expLength; i++) {
        char c = exp[i];
        if (c == ' ') {
            continue;
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (st.top() != '(') {
                newExp += st.top();
                st.pop();
            }
            st.pop();
        }
        else if (isOperator(c)) {
            while (!st.empty() && precedence(c) <= precedence(st.top())) {
                newExp += st.top();
                st.pop();
            }
            st.push(c);
        }
        else {
            newExp += c;
        }
    }

    while (!st.empty()) {
        newExp += st.top();
        st.pop();
    }

    return newExp;
    
}

void solve(string exp) {
    stack<int> st;
    int result;
    int expLen = exp.length();

    //
    for (int i = 0; i < expLen; i++) {
        
        char c = exp[i];

        if (isOperator(c)) {
            int v2 = st.top();
            st.pop();
            int v1 = st.top();
            st.pop();

            result = calculator(c, v1, v2);
            
            st.push(result);

        }
        else if (isNumber(c)) {
            st.push(c - '0');
        }
        else {
            cout << "invalid expression. aborting \n";
            return;
        }
        
    }
    cout << result << endl;
}
int main() {

    string exp = "";
    cout << "Enter expression: ";
    cin >> exp;

    solve(convert(exp));



    return 0;
}