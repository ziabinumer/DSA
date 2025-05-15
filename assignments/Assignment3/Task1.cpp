/*
    Name: Zia ur Rehman
    Reg No: 5005-FOC/BSCS/F23
    Section: B
    Course: DSA (Sir. Saqlain)

    Code available at: https://github.com/ziabinumer/DSA/assignments/Assignment3
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int SIZE = 100;

string lowercase(string& word) {
    string new_string = "";
    for (auto ch : word) {
        new_string += tolower(ch);
    }
    return new_string;
}

struct Student {
    int roll_num;
    string name;
    string dep;
    float cgpa;

    Student(string name, string dep, float cgpa) {
        this->roll_num = 0;
        this->name = name;
        this->dep = dep;
        this->cgpa = cgpa;
    }

    Student() {}
};

class HashTable {
public:
    vector<Student> students[SIZE];

    int hash_code(string name) {
        name = lowercase(name);
        int code = name.length() % SIZE;
        for (auto ch : name) {
            code += static_cast<int>(ch);
        }

        return code % SIZE;
    }

    void insert(Student student) {
        student.roll_num = hash_code(student.name);
        students[student.roll_num].push_back(student);
    }

    void remove(string name) {
        int code = hash_code(name);
        if (!students[code].empty()) {
            for (size_t i = 0; i < students[code].size(); ++i) {
                if (lowercase(students[code][i].name) == lowercase(name)) {
                    students[code].erase(students[code].begin() + i);
                    return;
                }
            }
        }
    }

    void search(string name) {
        int code = hash_code(name);
        for (auto& student : students[code]) {
            if (lowercase(student.name) == lowercase(name)) {
                cout << "Found: " << student.name << " at index " << code << endl;
                return;
            }
        }
        cout << name << " not found\n";
    }

    void print() {
        cout << "\n--------------------------------\n";
        int i = -1;
        for (vector in : students) {
            i++;
            if (in.empty()) continue;
            cout << "index: " << i << " ";
            for (Student student : in) {
                cout << student.name << ", ";

            }
            cout << endl;
        }
        cout << "\n---------------------------------\n";
    }
    
};

int main() {
    HashTable ht;
    string name, dep; float cgpa;
    string choice;
    while (true) {
        cout << "which op to perform? ";
        getline(cin, choice);
        system("clear");
        if (choice == "insert") {
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter dep: ";
            getline(cin, dep);
            
            cout << "Enter cgpa: ";
            cin >> cgpa;
            ht.insert(Student(name, dep, cgpa));
        }
        else if (choice == "delete") {
            cout << "Enter name: ";
            getline(cin, name);
            ht.remove(name);
        }
        else if (choice == "print") {
            ht.print();
        }
        else if (choice == "search") {
            cout << "Enter name: ";
            getline(cin, name);
            ht.search(name);
        }
        else if (choice == "exit") {
            return 0;
        }
    }



    return 0;
}