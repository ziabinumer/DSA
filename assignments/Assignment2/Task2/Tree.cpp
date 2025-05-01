/*
    Name: Zia ur Rehman
    Reg No: 5005-FOC/BSCS/F23
    Section: B
    Course: DSA (Sir. Saqlain)

    Code available at: 
*/

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

    void printMessage(string message, char flag) {
        if (flag == 's') {
            cout << "Success: " + message << endl;
        }
        else if (flag == 'e') cout << "Error: " + message << endl;
        else if (flag == 'w') cout << "Warning: " << message << endl;
    }

    void commandFormatHelper(string input) {
        stringstream ss(input);
        vector<string> args;
        string arg = "";
        int count = 0;

        while (getline(ss, arg, ' ') && count < 2) {
            args.push_back(arg);
            count++;
        }

        if (args.size() > 2) {
            printMessage("Too many arguments", 'e');
            return;
        }
        
        if (args[0] == "ls") {
            if (args.size() == 1) {
                display(root, 0);
                return;
            }
            display(findParentByPath(splitPath(args[1]), false), 0);
            return;
        }
        else if (args[0] == "count") {
            int total = countChildren(root);
            printMessage(to_string(total) + " files/folders found", 's');
            return;
        }

        else if (args[0] == "clear") {
            system("clear");
            return;
        }

        if (args.size() < 2) {
            printMessage("Too few arguments", 'e');
            return;
        }
        if (args[0] == "mkdir") {
            make(splitPath(args[1]), 'd');
        }
        else if (args[0] == "touch") make(splitPath(args[1]));
        else if (args[0] == "search") search(args[1]);
        else if (args[0] == "quit") exit(0);
        else if (args[0] == "reset") reset();
        
       
    }

    vector<string> splitPath(string path) {
        vector<string> components;
        stringstream ss(path);
        string component;

        while(getline(ss, component, '/')) {
            if (!component.empty())
            components.push_back(component);
        }

        return components;
    }

    Node* findParentByPath(vector<string> components, bool skipLast = true) {
        if (!root) {
            printMessage("invalid path: root doesn't exist", 'e');
            return nullptr;
        }
        if (components[0] != "root") {
            printMessage("invalid path: must start with root/", 'e');
            return nullptr;
        }


        else if (components.size() == 1) {
            return root;
        }

        components.erase(components.begin());

        int limit = skipLast ? components.size() - 1 : components.size();

        Node* current = root;
        for (int i = 0; i < limit; i++) {
            bool parentFound = false;
            for (Node* child : current->children) {
                if (child->name == components[i]) {
                    if (child->type == "file") {
                        printMessage("invalid path: directory name can not be file", 'e');
                        return nullptr;
                    }
                    parentFound = true;
                    current = child;
                    break;
                }
            }
            if (!parentFound) {
                printMessage("invalid path: " + components[i] + " doesn't exist in loop", 'e');
                return nullptr;
            }
        }
        return current;
    }

    void findAll(Node* node, string name, vector<string>& results, string path = "root") {
        if (!node) {
            return;
        }

        if (node->name == name) {
            results.push_back(path);
        }

        for (Node* child : node->children) {
            string childPath = path + "/" + child->name;
            
            findAll(child, name, results, childPath);
        }
    }   

    void search(string name) {
        if (!root) {
            printMessage("root doesn't exist", 'e');
            return;
        }
        vector<string> results;

        if (root->name == name) {
            results.push_back(root->name);
        }

        for (Node* child : root->children) {
            string childPath = "root/" + child->name;
            findAll(child, name, results, childPath);
        }

        if (results.empty()) {
            cout << "no matching file/folder was found\n";
            return;
        }
        else printMessage(to_string(results.size())+ " matching results found", 's');
        for (string result : results) {
            cout << result << endl;
        }
        return;
    }

    int countChildren(Node* node) {
        if (!node) return 0;
    
        int total = 1; 
        for (Node* child : node->children) {
            total += countChildren(child); 
        }
        return total;
    }

    void display(Node* node, int level) {
        if (!node) return;

        cout << string(level * 2, ' ');

        if (node->type == "file") {
            cout << "f: " << node->name << endl;
        } else {
            cout << "d: " << node->name << endl;
        }

        for (Node* child : node->children) {
            display(child, level + 1);
        }

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
            printMessage("created directory with name 'root'", 's');
            return true;
        }

        // get file or folder name
        string name = components.back();

        // find parent if exists
        Node* current = findParentByPath(components);

        if (current == nullptr) {
            return false;
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
            cout << "Printing all...\n";
            display(root, 0);
            return true;
        }
        else {
            if (name.find('.') != string::npos) {
                printMessage("directory name can not contain '.'", 'e');
                return false;
            }
            current->children.push_back(new Node(name, "folder"));
            printMessage("created folder with name " + name, 's');
            cout << "Printing all...\n";
            display(root, 0);
            return true;
        }
        

    }

    void deleteFS(Node* node) {
        if (!node) return;

        for (Node* child : node->children) {
            deleteFS(child);
        }
        delete node;
    }

    void reset() {
        deleteFS(root);
        printMessage("Filesystem is reset", 's');
        return;
    }


};

int main() {
    Filesystem fs;
    string command;
    
    
    cout << "-------------------------------------------\n"
         << "  File System Hierarchy Simulator\n"
         << "  Here is a list of available commands: \n"
         << "1. mkdir [path] - Create a new directory\n"
         << "2. touch [path] - Create a new file\n"
         << "3. ls [optional: path] - List contents\n"
         << "4. search [name] - Search for a file or folder\n"
         << "5. count - Count files and folders\n"
         << "6. reset - Reset the file system\n"
         << "7. quit - Exit the program\n"
         << "8. clear - Clear Screen\n"
         << "--------------------------------------------\n";
    
    while (true) {
        
        cout << "\n$ ";
        getline(cin, command);

        fs.commandFormatHelper(command);

    }
    
    return 0;
}
