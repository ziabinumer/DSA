// Course.h
#pragma once
#include <iostream>
using namespace std;

class Course {
    int courseId;
    string courseName;
    int crHours;

public:
    Course(int id, string name, int hours) : courseId(id), courseName(name), crHours(hours) {}
    Course() {}

    int getId() { return courseId; }
    string getName() { return courseName; }
    int getHours() { return crHours; }

    void setId(int id) { courseId = id; }
    void setName(string name) { courseName = name; }
    void setHours(int hours) { crHours = hours; }

    void display() {
        cout << "----------------------------" << endl;
        cout << "ID: " << courseId << endl;
        cout << "Name: " << courseName << endl;
        cout << "Cr Hours: " << crHours << endl;
        cout << "----------------------------" << endl;
    }
};
