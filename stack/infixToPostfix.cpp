#include <iostream>
#include <stack>
using namespace std;

bool isOperator(char c) {
    switch(c) {
        case '/':
        case '*':
        case '-':
        case '+':
            return true;
    }
    return false;
}

int precedence(char current) {
    if (current == '/' || current == '*') {
        return 2;
    }
    if (current == '+' || current == '-') {
        return 1;
    }
    else return -1;
}

string convert(string exp) {
    stack<char> st;
    string newExp = "";
    int expLength = exp.length();
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
    cout << newExp << endl;

    return newExp;
    
}

void solve(string exp) {
    stack<int> st;
    int result;
    int expLen = exp.length();
    cout << "len: " << expLen << endl;
    for (int i = 0; i < expLen; i++) {
        cout << " ----  iteration " << i << " ----\n\n"; 
        
        char c = exp[i];

        if (isOperator(c)) {
            cout << "---Operator read----" << endl;
            int v2 = st.top();
            cout << "stack top: " << st.top() << " --- v1: " << v2 << endl;
            st.pop();
            int v1 = st.top();
            cout << "stack top: " << st.top() << " --- v2: " << v1 << endl;
            st.pop();

            
            
            switch(c) {
                case '+':
                    result = v1 + v2;
                    break;
                case '-':
                    result = v1 - v2;
                    break;
                case '*':
                    result = v1 * v2;
                    break;
                case '/':
                    result = v1 / v2;
                    break;
            }
            cout << "result: " << result << endl;
            st.push(result);
            cout << "stack top: " << st.top() << endl;

        }
        else {
            st.push(c - '0');
            cout << "pushing " << c << endl;
            cout << "stack top now: " << st.top() << endl;
        }

        cout << "\n\n";
    }
    cout << endl;
    cout << result << endl;
}
int main() {

    string exp = "";
    cout << "Enter expression: ";
    cin >> exp;

    solve(convert(exp));


    return 0;
}