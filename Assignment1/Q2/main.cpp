#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    string element;
    Node* next;

    Node(string element) {
        this->element = element;
        this->next = nullptr;
    }
};

class LinkedList {
public:
    Node* top;

    LinkedList() {
        top = nullptr;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(string element) {
        Node* newNode = new Node(element);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty. Cant perform pop.\n";
            return;
        }

        Node* tmpNode = top;
        top = top->next;
        delete tmpNode;
    }

    string getTop() {
        if (!isEmpty()) {
            return top->element;
        }
        return ""; 
    }

    ~LinkedList() {
        while(!isEmpty()) {
            pop();
        }
    }
};

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

int precedence(char op) {
    if (op == '/' || op == '*' || op == '%') {
        return 2;
    }
    if (op == '+' || op == '-') {
        return 1;
    }
    else return INT_MIN;
}

string extractExp(string filename) {
    ifstream inFile(filename);
    string line;
    getline(inFile, line);
    inFile.close();
    return line;
}

string infixToPostfix(const string& exp, char flag) {
    LinkedList stack;
    string result = "";

    int expLength = exp.length();

    for (int i = 0; i < expLength; i++) {
        char current  = exp[i];
        if (current == ' ') continue;
        if (current == '(') {
            stack.push(string(1, current));
        }
        else if (current == ')') {
            while (stack.getTop() != "(") {
                result += stack.getTop();
                stack.pop();
            }
            stack.pop();
        }
        else if (isOperator(current)) {
            if (flag == 'r') {
                while (!stack.isEmpty() && precedence(current) < precedence(stack.getTop()[0])) {
                    result += stack.getTop();
                    stack.pop();
                }
            }
            else if (flag == 's') {
                while (!stack.isEmpty() && precedence(current) <= precedence(stack.getTop()[0])) {
                    result += stack.getTop();
                    stack.pop();
                }
            }
            stack.push(string(1, current));
        }
        else result += current;
    }

    while (!stack.isEmpty()) {
        result += stack.getTop();
        stack.pop();
    }
    return result;
}

string infixToPrefix(string exp) {
    reverse(exp.begin(), exp.end());

    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }

    exp = infixToPostfix(exp, 'r');

    reverse(exp.begin(), exp.end());
    return exp;
}

string postfixToInfix(const string& exp) {
    LinkedList stack;

    for (int i = 0; i < exp.length(); i++) {
        char current = exp[i];
        if (!isOperator(current)) {
            stack.push(string(1, current));
        } else {
            string op2 = stack.getTop(); stack.pop();
            string op1 = stack.getTop(); stack.pop();
            string newExp = "(" + op1 + current + op2 + ")";
            stack.push(newExp);
        }
    }
    return stack.getTop();
}

string prefixToInfix(string exp) {
    reverse(exp.begin(), exp.end());
    exp = postfixToInfix(exp);
    reverse(exp.begin(), exp.end());

    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }

    return exp;
}

void writeToFile(string filename, string content) {
    ofstream outFile(filename, ios::out);
    outFile << content << endl;
    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Filename missing. \n";
        exit(0);
    }
    string filename = argv[1];
    string postfix, prefix, infix, infix2;

    if (filename == "infix.txt") {
        postfix = infixToPostfix(extractExp(filename), 's');
        prefix = infixToPrefix(extractExp(filename));
        
        writeToFile("postfix.txt", postfix);
        writeToFile("prefix.txt", prefix);
        
    }
    else if (filename == "postfix.txt") {
        infix = postfixToInfix(extractExp(filename));

        writeToFile("infix.txt", infix);
    }
    else if (filename == "prefix.txt") {
        infix2 = prefixToInfix(extractExp(filename));

        writeToFile("infix2.txt", infix2);
    }

    return 0;
}
