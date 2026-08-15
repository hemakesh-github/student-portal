#include <iostream>
#include <string>
#include <vector>
#include <limits>


using namespace std;
bool isLoggedIn = false;
string currentUser = "";


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
    cout << "6. Login" << endl;
    cout << "7. Logout" << endl;
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
    while(newStudent.rollNo <= 0) {
        cout << "Invalid roll number. Please enter a positive integer: ";
        cin >> newStudent.rollNo;
    }

    if (findStudentIndexByRollNo(students, newStudent.rollNo) != -1) {
        cout << "Student with this roll number already exists." << endl;
        return;
    }
    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newStudent.name);

    cout << "Enter Age: ";
    cin >> newStudent.age;
    while(newStudent.age <= 0) {
        cout << "Invalid age. Please enter a positive integer: ";
        cin >> newStudent.age;
    }

    cout << "Enter Program: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newStudent.program);

    students.push_back(newStudent);
    cout << "Student added successfully!" << endl;
    cout << "Total Students: " << students.size() << endl;
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

void updateStudentProgram(vector<Student>& students) {
    int rollNo;
    cout << "Enter Roll Number to update program: ";
    cin >> rollNo;

    int index = findStudentIndexByRollNo(students, rollNo);
    if (index != -1) {
        cout << "Enter new Program: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, students[index].program);
        cout << "Student program updated successfully!" << endl;
    } else {
        cout << "Student with Roll Number " << rollNo << " not found." << endl;
    }
}

void deleteStudent(vector<Student>& students) {
    int rollNo;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNo;

    int index = findStudentIndexByRollNo(students, rollNo);
    if (index != -1) {
        students.erase(students.begin() + index);
        cout << "Student deleted successfully!" << endl;
    } else {
        cout << "Student with Roll Number " << rollNo << " not found." << endl;
    }
}

bool loginUser() {
string username;
int pin;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter pin: ";
    cin >> pin;

    // Simple login logic - replace with actual authentication mechanism
    if (username == "admin" && pin == 1234) {
        currentUser = username;
        isLoggedIn = true;
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "Invalid credentials." << endl;
        return false;
    }
}


void logoutUser() {
    if (!isLoggedIn) {
        cout << "No active session found." << endl;
        return;
    }

    cout << "User " << currentUser << " logged out successfully." << endl;
    isLoggedIn = false;
    currentUser.clear();
}

bool requireLoginForWrite() {
    if (!isLoggedIn) {
        cout << "Please login first to perform this action." << endl;
        return false;
    }
    return true;
}

int main() {
    
    int choice;
    vector<Student> students;
    do {
        printMenu();
        if (!cin >> choice) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue; 
        }

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                listStudents(students);
                break;
            case 3:
                searchStudent(students);
                break;
            case 4:
                updateStudentProgram(students);
                break;
            case 5:
                deleteStudent(students);
                break;
            case 0:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while(choice != 0);
    
    return 0;
}