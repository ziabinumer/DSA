#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

struct Student {
    int id;
    string name;
    string dep;
    float cgpa;

    Student() {}

    Student(int id, string name, string dep, float cgpa) {
        this->id = id;
        this->name = name;
        this->dep = dep;
        this->cgpa = cgpa;
    }

    void display() {
        cout << "----------------------------\n"
             << "| Id: " << id << endl
             << "| Name: " << name << endl
             << "| Dep: " << dep << endl
             << "| Cgpa: " << cgpa << endl
             << "----------------------------\n";
    }
};

string lowercase(string& word) {
    string new_string = "";
    for (auto ch : word) {
        new_string += tolower(ch);
    }
    return new_string;
}

class HashTable {
public:
    static const int SIZE = 100;
    vector<Student> students[SIZE];

    HashTable() {}

    int HashCode(string name) {
        int code = 0;
        for (auto ch : name) {
            code += int(ch);
        }
        return code % SIZE;
    }

    void print() {
        int index = 0, Sindex;
        for (vector<Student> chain: students) {
            index++;
            Sindex = 0;
            for (Student student : chain) {
                cout << "----------------------------------------" << endl;
                cout << "Index: " << index << endl << "Chain Index: " << Sindex++ << endl;
                student.display();
            }
        }
    }

    void insert(Student student) {
        student.id = HashCode(lowercase(student.name));
        students[student.id].push_back(student);

        print();
    }
};

int main() {
    HashTable ht;
    string name, dep; float cgpa;
    while (true) {
        cout << "Enter name: ";
        cin >> name;
        if (name == "exit") {
            break;
        }
        cout << "Enter dep: ";
        cin >> dep;
        
        cout << "Enter cgpa: ";
        cin >> cgpa;
        ht.insert(Student(1, name, dep, cgpa));
    }
    
    return 0;
}