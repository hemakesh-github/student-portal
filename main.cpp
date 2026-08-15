#include <iostream>
#include <string>
#include <vector>
#include <limits>


using namespace std;
struct Student {
    int rollNo;
    string name;
    int age;
    string program;
};

void printMenu() {
    cout << "\n==== Student Portal ====" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Display Students" << endl;
    cout << "3. Search Student by Roll Number" << endl;
    cout << "4. Update Student Program" << endl;
    cout << "5. Delete Student" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose an option: ";

}

int findStudentIndexByRollNo(const vector<Student>& students, int rollNo) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].rollNo == rollNo) {
            return (int)i;
        }
    }
    return -1; 
}

void addStudent(vector<Student>& students) {
    Student newStudent;
    cout << "Enter Roll Number: ";
    cin >> newStudent.rollNo;
    cout << "Enter Name: ";
    getline(cin, newStudent.name);
    cout << "Enter Age: ";
    cin >> newStudent.age;
    cout << "Enter Program: ";
    getline(cin, newStudent.program);

    students.push_back(newStudent);
    cout << "Student added successfully!" << endl;
}

void listStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students found." << endl;
        return;
    }

    cout << "\n==== Student List ====" << endl;
    for (const auto& student : students) {
        cout << "Roll Number: " << student.rollNo << ", Name: " << student.name
             << ", Age: " << student.age << ", Program: " << student.program << endl;
    }
}

void searchStudent(const vector<Student>& students) {
    int rollNo;
    cout << "Enter Roll Number to search: ";
    cin >> rollNo;

    int index = findStudentIndexByRollNo(students, rollNo);
    if (index != -1) {
        const Student& student = students[index];
        cout << "Student found: Roll Number: " << student.rollNo << ", Name: " << student.name
             << ", Age: " << student.age << ", Program: " << student.program << endl;
    } else {
        cout << "Student with Roll Number " << rollNo << " not found." << endl;
    }
}

int main() {
   
    
    return 0;
}