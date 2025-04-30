#include <iostream>
#include <vector>
#include <sstream>
using namespace std;




struct Node {
public:
    string name;
    string type;
    vector<Node*> children;

    Node() {}

    Node(string name, string type) {
        this->name = name;
        this->type = type;
    }
};

class Filesystem {
public:
    Node* root;

    Filesystem() {
        root = nullptr;
    }

    void display(Node* node, int level) {
        if (!node) return;

        cout << string(level * 2, ' ');

        if (node->type == "file") {
            cout << "📄 " << node->name << endl;
        } else {
            cout << "📁 " << node->name << endl;
        }

        for (Node* child : node->children) {
            display(child, level + 1);
        }

    }

    void printMessage(string message, char flag) {
        if (flag == 's') {
            cout << "Success: " + message << endl;
        }
        else if (flag == 'e') cout << "Error: " + message << endl;
        else if (flag == 'w') cout << "Warning: " << message << endl;
    }

    void commandFormatHelper(string input) {
        stringstream ss(input);
        string arr[2];
        string arg = "";
        int count = 0;

        while (getline(ss, arg, ' ') && count < 2) {
            arr[count] = arg;
            count++;
        }

        if (arr[0] == "mkdir") {
            make(splitPath(arr[1]), 'd');
        }
        else if (arr[0] == "touch") make(splitPath(arr[1]));
    }

    vector<string> splitPath(string path) {
        vector<string> components;
        stringstream ss(path);
        string component;

        while(getline(ss, component, '/')) {
            components.push_back(component);
        }

        return components;
    }

    bool make(vector<string> components, char flag = 'f') {
        if (!components.size()) {
            printMessage("invalid path", 'e');
            return false;
        }

        if (!root) {
            if (components[0] != "root") {
                printMessage("root missing. Please create root first", 'e');
                return false;
            }
            else if (components.size() > 1) {
                printMessage("root missing. ignored path after root/", 'w');
            }
            root = new Node("root", "folder");
            printMessage("created directory with name 'root", 's');
            return true;
        }

        // get file or folder name
        string name = components.back();

        if (components[0] != "root") {
            printMessage(name + " doesn't exist.\nMake sure to include 'root/' in start", 'e');
            return false;
        }
        else {
            // remove root. no need to check for it again
            components.erase(components.begin());
        }

        // find parent if exists
        Node* current = root;
        for (int i = 0; i < components.size() - 1; i++) {
            bool parentFound = false;
            for (Node* child : current->children) {
                if (child->name == components[i]) {
                    if (child->type == "file") {
                        printMessage(components[i] + " is a file", 'e');
                        return false;
                    }
                    current = child;
                    parentFound = true;
                    break;
                }
            }
             // if parent doesnt exist, then can not insert
             if (!parentFound) {
                printMessage(components[i] + " doesn't exist", 'e');
                return false;
            }
        }

        // check if child with same name already exists under current parent
        for (Node* child : current->children) {
            if (child->name == name) {
                printMessage(name + " already exists", 'e');
                return false;
            }
        }


        if (flag == 'f') {
            if (name.find('.') == string::npos) {
                printMessage("filename must contain extension '.'", 'e');
                return false;
            }
            current->children.push_back(new Node(name, "file"));
            printMessage("created file with name " + name, 's');
            return true;
        }
        else {
            if (name.find('.') != string::npos) {
                printMessage("directory name can not contain '.'", 'e');
                return false;
            }
            current->children.push_back(new Node(name, "folder"));
            printMessage("created folder with name " + name, 's');
            return true;
        }
        

    }
};

int main() {
    Filesystem tree;
    string path; char flag;
    while (true) {
        cout << "Enter path: ";
        getline(cin, path);
        if (path == "exit") break;
        
        tree.commandFormatHelper(path);
    }

    tree.display(tree.root, 0);
    
    return 0;
}