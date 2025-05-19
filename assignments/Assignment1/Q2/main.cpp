#include <iostream>
#include <fstream>
#include <climits>
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

    // destructor to free the list
    ~LinkedList() {
        while(!isEmpty()) {
            pop();
        }
    }
};

string reverse(string exp) {
    LinkedList st1;
    for (int i = 0; i < exp.length(); i++) {
        st1.push(string(1, exp[i]));
    }

    exp = "";

    while (!st1.isEmpty()) {
        exp += st1.getTop();
        st1.pop();
    }
    return exp;
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

int precedence(char op) {
    if (op == '/' || op == '*' || op == '%') {
        return 2;
    }
    if (op == '+' || op == '-') {
        return 1;
    }
    else return INT_MIN;
}

// reads expression from file and returns
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
    // reverse to make it compatible with infixtopostfix
    exp = reverse(exp);

    // swap brackets
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }

    // get converted exp
    exp = infixToPostfix(exp, 'r');

    // reverse again to get in correct order - brackets mess up
    return reverse(exp);
}

string postfixToInfix(const string& exp) {
    LinkedList stack;

    // push if find a variable or a number
    // if operator is read then remove two elements from stack
    // store the elements in format: (first statement + second statement)
    // this leaves the stack with a single element which is the converted exp

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
    // reverse the exp to make it compatible with postfixtoinfix
    // convert to postfix
    // reverse again to have the exp in given order
    exp = reverse(exp);
    exp = postfixToInfix(exp);
    exp = reverse(exp);

    // swap brackets to put at correct position
    // because reverse will kind of invert them
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
