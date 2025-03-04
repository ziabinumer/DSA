#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
using namespace std;

class Screens {
public:
    void main() {
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

    void showMain() {
        cout << "\nPress something to continue\n";
        cin.ignore();
        cin.get();
        main();
    }

    void clearScreen() {
        system("cls") ? system("clear") : system("cls");
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
                if (stoi(input)) {}
                else {
                    throw exception();
                }
                if (stoi(input) > 10000 && stoi(input) < 65000) {
                    break;
                }
                else {
                    cout << "\nPassword must be between 10000 & 65000\n";
                    continue;
                }
            }
            catch(exception e) {
                cout << "\nPassword must not be a string. Only digits accepted\n";
                continue;
            }

        } while (true);

        
        items.push_back(input);
        return items;
    }
    
    void loginScreen() {
        clearScreen();
        printLine();

        string username = authenticate(getCredentials());
        if (username == "NOTFOUND") {
            cout << "\nNo Matching Username Found\n";
            showMain();
        }
        else {
            // implement show profile
        }
    }

    string authenticate(vector<string> cred) {
        ifstream credentials;
        credentials.open("credentials.txt");

        if (!credentials) {
            cout << "\nCredentials file is missing. Exiting the Program\n";
            printLine();
            exit(1);
        }

        string data;
        string line = cred.at(0) + " " + cred.at(1);

        while (getline(credentials, data)) {
            if (line == data) {
                cout << "\nFound a user\n";
                credentials.close();
                return cred.at(0); 
            }
        }
        cout << "\nEither a user was not found. Or the password is incorrect\n";
        credentials.close();
        return "NOTFOUND";
    }

    void RegisterScreen() {
        clearScreen();
        printLine();
        vector<string> cred = getCredentials();
        string username = cred.at(0);

            ofstream userFile(username + ".txt");
            ofstream credentials("credentials.txt", ios::app);
            credentials << username << " " << cred.at(1) << endl;
            cout << "\nRegistered. \n";
            // implement get Data
            userFile.close();

    }


};

int main() {
    Screens main;
    main.main();

    return 0;
}