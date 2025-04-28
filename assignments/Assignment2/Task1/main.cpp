#include "AVL.h"

int main() {
    AVL courseData;
    courseData.addCourse(Course(8, "DSA", 4));
    courseData.addCourse(Course(9, "IDS", 4));
    courseData.addCourse(Course(2, "IWVC", 3));
    courseData.addCourse(Course(10, "Algorithms", 3));
    courseData.addCourse(Course(12, "Database Systems", 4));
    courseData.deleteCourse(2);

    return 0;
}