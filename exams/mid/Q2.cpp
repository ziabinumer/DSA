#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int applyOperation(const string& op, int a, int b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    return 0;
}

int evaluatePrefix(stack<string>& tokens) {
    stack<int> eval;

    while (!tokens.empty()) {
        string token = tokens.top();
        tokens.pop();

        if (isOperator(token)) {
            int operand1 = eval.top(); eval.pop();
            int operand2 = eval.top(); eval.pop();
            int result = applyOperation(token, operand1, operand2);
            eval.push(result);
        } else {
            eval.push(stoi(token)); // Convert operand to int
        }
    }

    return eval.top();
}

int main() {
    stack<string> prefix;
    int n;
    cout << "Enter number of tokens in prefix expression: ";
    cin >> n;

    cout << "Enter tokens (operator or operand), one per line:" << endl;
    for (int i = 0; i < n; i++) {
        string token;
        cin >> token;
        prefix.push(token); // Pushing tokens gives us reversed expression
    }

    int result = evaluatePrefix(prefix);
    cout << "Result = " << result << endl;

    return 0;
}
