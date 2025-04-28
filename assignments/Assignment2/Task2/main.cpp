#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void commandFormatHelper(string input) {
    vector<string> arguments; // to store command parameteres [mkdir, root]
    stringstream ss(input);
    string s;
    while (getline(ss, s, ' ')) {
        arguments.push_back(s);
    }

    string command = arguments[0];
    arguments.erase(arguments.begin() + 0);
    
    if (command == "mkdir" || command == "touch" || command == "ls") {
        if (arguments.size() < 1) {
            cout << "too few arguments\n"; 
            return;
        }
        else if (arguments.size() > 1) {
            cout << "too much arguments\n";
            return;
        }
        s = arguments[0];
        arguments.pop_back(); // empty vector
        
        stringstream ss(s);
        while(getline(ss, s, '/')) {
            arguments.push_back(s);
        }

        for (int i = 0; i <= arguments.size() - 2; i++) {
            if (arguments[i].find(".") != string::npos) {
                cout << "Invalid path \n";
                return;
            }
        }

        string name = arguments[arguments.size() - 1];
        if (command == "mkdir") {
            if (name.find('.') == string::npos) {
                // addFolder(arguments)
            }
            else {
                cout << "folder name can not have '.' \n";
                return;
            }
        }
        else if (command == "touch") {
            if (name.find('.') != string::npos) {
                // addFolder(arguments)
            }
            else {
                cout << "filename must have an extension [filename.ext]\n";
                return;
            }
            // addFile(arguments)
        }
       
    }
    else {
        cout << "Invalid command\n";
    }
    cout << endl;
}

int main() {
    string command;
    system("clear");
    cout << "-------------------------------------------\n"
         << "  Here is a list of available commands: \n"
         << "1. mkdir [foldername] or [foldername/foldername/...]\n"
         << "2. touch [filename] or [foldername/filename]\n"
         << "3. ls [optional: foldername]\n"
         << "4. quit [for quitting the program]\n"
         << "5. reset [for resetting root]\n"
         << "--------------------------------------------\n";
    while (true) {
        cout << "$ ";
        getline(cin, command);
        
        if (command == "quit") {
            system("clear");
            cout << "\nquitting program....\n";
            return 0;
        }
        else if (command == "reset") {
            cout << "Root is reset. Nothing in file system right now\n\n";
        }
        else {
            commandFormatHelper(command);
        }
    }
    return 0;
}