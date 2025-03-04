#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    char element;
    Node* next;

    Node(char element) {
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

    void push(char element) {
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

    char getTop() {
        if (!isEmpty()) {
            return top->element;
        }
        return '\0'; 
    }
};

/*
bool isInteger(char digit) {
    if (digit - '0' >= 0 && digit - '0' <= 9) {
        return true;
    }
    return false;
}
*/
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

string reverseExp(const string &exp) {
    string result = "";
    int expLength = exp.length();

    for (int i = expLength - 1; i >= 0; i--) {
        result += exp[i];
    }

    return result; 
}

string infixToPostfix(const string& exp) {
    LinkedList stack;
    string result = "";

    int expLength = exp.length();

    for (int i = 0; i < expLength; i++) {
        char current  = exp[i];
        if (current == ' ') continue;
        if (current == '(') {
            stack.push(current);
        }
        else if (current == ')') {
            while (stack.getTop() != '(') {
                result += stack.getTop();
                stack.pop();
            }
            stack.pop();
        }
        else if (isOperator(current)) {
            while (!stack.isEmpty() && precedence(current) <= precedence(stack.getTop())) {
                result += stack.getTop();
                stack.pop();
            }
            stack.push(current);
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

    string exp = infixToPostfix(exp);

    reverse(exp.begin(), exp.end());
    return exp;
}

string postfixToInfix(const string& exp) {}

string prefixToInfix(const string& exp) {}

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
        postfix = infixToPostfix(extractExp(filename));
        prefix = infixToPrefix(extractExp(filename));
        cout << prefix << endl;
        
        // write to postfix file
        writeToFile("postfix.txt", postfix);

        // write to prefix file
        //writeToFile("prefix.txt", prefix);
        
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