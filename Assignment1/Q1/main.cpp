#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

class ProfileData {
public:
    int regNo;
    string name, fatherName, birthDate, className;
    int age;
};


class Screens {
public:
    Screens() {
        createCredentials();
    }

    void createCredentials() {
        ofstream cred("credentials.txt", ios::out | ios::app);
        cred.close();
    }

    void menu() {
        clearScreen();

        printLine();
        cout << "1. Login\n" 
             << "2. Signup\n"
             << "3. Exit\n";

        cout << "\nYour choice: ";

        int choice;
        cin >> choice;
        switch (choice) {
            case 1: 
                loginScreen();
                break;
            case 2:
                RegisterScreen();
                break;
            default:
                cout << "Exiting Program...\n";
                printLine();
                exit(0);
        }
        printLine();
        
    }

    void showMenu() {
        cout << "\nPress something to continue\n";
        cin.ignore();
        cin.get();
        menu();
    }

    void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }

    void printLine() {
        cout << "\n------------------------------\n\n";
    }


    vector<string> getCredentials() {
        vector<string> items;
        string input;
        cout << "Enter username: ";
        cin >> input;
        items.push_back(input);

        do {
        cout << "Enter password: ";
        cin >> input;

        try {
            int pass = stoi(input); // Convert once
            if (pass > 10000 && pass < 65000) {
                break;
            } else {
                cout << "\nPassword must be between 10000 & 65000\n";
            }
        }
            catch (exception &e) {
            cout << "\nPassword must not be a string. Only digits accepted\n";
        }

    } while (true);

        
        items.push_back(input);
        return items;
    }

    bool userExists(string username, string password, char flag) {
        ifstream credentials;
        credentials.open("credentials.txt", ios::in);

        if (!credentials) {
            cout << "\nCredentials file is missing. Exiting the Program\n";
            printLine();
            exit(1);
        }

        string line, word;
        
        while (getline(credentials, line)) {
        stringstream ss(line);
        ss >> word;  // Read the first word (username)
        
        if (flag == 'a' && line == username + " " + password) return true;
        if (flag == 'r' && word == username) return true;
    }
        return false;
    }
    void showProfile(string username) {
        clearScreen();
        ifstream userFile(username + ".txt");
        if (!userFile) {
            cout << "User File was not found.\n";
            
            showMenu();
            return;
        }
        string line;
        printLine();
        cout << "Showing Record of " << username << "\n\n";
        while (getline(userFile, line)) {
            cout << line << endl;
        }
        cout << "Press something to continue";
        cin.ignore();
        cin.get();
        showProfileMenu(username);
        
    }

    void showProfileMenu(string username) {
        clearScreen();
            cout << endl << username << " is Logged in\n";
            string choice;
            cout << "1. Show Profile\n2. Overwrite Profile\n3. Exit to main menu\n ";
            cin >> choice;
            if (choice == "1") {
                showProfile(username);
            } else if (choice == "3") {showMenu();} else createProfile(username);
    }

    void loginScreen() {
        clearScreen();
        printLine();
        vector<string> cred = getCredentials();
        
        if (userExists(cred.at(0), cred.at(1), 'a')) {
            // implement show profile
            showProfileMenu(cred.at(0));
            
        }
        else {
            cout << "\nUser not found\n";
            showMenu();
        }
    }

    int getInteger(string message) {
        int num;
        while (true) {
            cout << message;
            cin >> num;

            if (cin.fail()) {  // If input is invalid (not an integer)
                cin.clear();  // Clear the error flag
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input! Please enter a valid integer.\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return num; // Return the valid integer
            }
        }
    }

    ProfileData getData() {
        ProfileData d;
        d.regNo = getInteger("Enter reg no: ");

        cout << "Enter name: ";
        cin.ignore();  // Ensure no leftover '\n' before using getline
        getline(cin, d.name);

        cout << "Enter father name: ";
        getline(cin, d.fatherName);

        cout << "Enter birth date (format: month, year): ";
        getline(cin, d.birthDate);

        d.age = getInteger("Enter age: ");

        cout << "Enter class name: ";
        getline(cin, d.className);

        return d;
    }

    void createProfile(string username) {
        clearScreen();
        cout << "---- Get Profile Data ----\n";
        // get profile data
        ProfileData data = getData();

        // implement write profile data
        ofstream userFile(username + ".txt", ios::out);
        userFile << "Reg No: " << data.regNo << endl
                 << "Name: " << data.name << endl
                 << "Father Name: " << data.fatherName << endl
                 << "Birth Date: " << data.birthDate << endl
                 << "Age: " << data.age << endl
                 << "Class Name: " << data.className << endl;


        userFile.close();
        showProfileMenu(username);
    }

    void RegisterScreen() {
        clearScreen();
        printLine();
        vector<string> cred;
        do {
            cred = getCredentials();
            if (userExists(cred.at(0), cred.at(1), 'r')) {
                cout << "\nUsername already exists. enter a different username\n";
            }
            else {
                break;
            }
        } while (true);
        

        ofstream credentials("credentials.txt", ios::app);
        credentials << cred.at(0) << " " << cred.at(1) << endl;
        cout << "\nRegistered. \n";

        string choice;
        cout << "Do you want to create profile? [y] ";
        cin >> choice;

        if (choice == "y" || choice == "Y") {
            createProfile(cred.at(0));

        }
        showMenu();
        

    }


};

int main() {
    Screens main;
    main.menu();

    return 0;
}