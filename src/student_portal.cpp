#include <iostream>
#include <string>
#include <vector>
#include <limits>


using namespace std;
bool isLoggedIn = false;
string currentUser = "";

struct Account {
    string username;
    int pin;
};

vector<Account> accounts = {
    {"admin", 1234}
};

// Privacy: only the admin account may view student mobile numbers.

struct Student {
    int rollNo;
    string name;
    int age;
    string program;
    string email;
    string phone;
};

void printMenu() {
    cout << "\n==== Student Portal ====" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Display Students" << endl;
    cout << "3. Search Student by Roll Number" << endl;
    cout << "4. Update Student Program" << endl;
    cout << "5. Delete Student" << endl;
    cout << "6. Create Account" << endl;
    cout << "7. Login" << endl;
    cout << "8. Logout" << endl;
    cout << "0. Exit" << endl;
    cout << "9. Update Student Contact" << endl;
    cout << "10. Dashboard Summary" << endl;
    cout << "11. Settings" << endl;
    cout << "12. Notices (draft)" << endl;
    cout << "Choose an option: ";
}

int findAccountIndexByUsername(const string& username) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].username == username) {
            return (int)i;
        }
    }
    return -1;
}

int findStudentIndexByRollNo(const vector<Student>& students, int rollNo) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].rollNo == rollNo) {
            return (int)i;
        }
    }
    return -1; 
}

bool canViewMobileNumber() {
    return isLoggedIn && currentUser == "admin";
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

    cout << "Enter Email: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newStudent.email);

    cout << "Enter Phone: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newStudent.phone);

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
             << ", Age: " << student.age << ", Program: " << student.program
             << ", Email: " << student.email;
        if (canViewMobileNumber()) {
            cout << ", Phone: " << student.phone;
        }
        cout << endl;
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
             << ", Age: " << student.age << ", Program: " << student.program
             << ", Email: " << student.email;
        if (canViewMobileNumber()) {
            cout << ", Phone: " << student.phone;
        }
        cout << endl;
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

void updateStudentContact(vector<Student>& students) {
    int rollNo;
    cout << "Enter Roll Number to update contact: ";
    cin >> rollNo;

    int index = findStudentIndexByRollNo(students, rollNo);
    if (index != -1) {
        cout << "Enter new Email: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, students[index].email);

        cout << "Enter new Phone: ";
        getline(cin, students[index].phone);

        cout << "Student contact updated successfully!" << endl;
    } else {
        cout << "Student with Roll Number " << rollNo << " not found." << endl;
    }
}

void showDashboardSummary(const vector<Student>& students) {
    cout << "\n==== Dashboard Summary ====" << endl;
    if (isLoggedIn) {
        cout << "Signed in as: " << currentUser << endl;
    } else {
        cout << "Signed in as: (none)" << endl;
    }
    cout << "Total Students: " << students.size() << endl;

    int uniquePrograms = 0;
    for (size_t i = 0; i < students.size(); ++i) {
        bool seen = false;
        for (size_t j = 0; j < i; ++j) {
            if (students[j].program == students[i].program) {
                seen = true;
                break;
            }
        }
        if (!seen) {
            uniquePrograms++;
        }
    }
    cout << "Distinct Programs: " << uniquePrograms << endl;
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

void createAccount() {
    string username;
    int pin;

    cout << "Choose username: ";
    cin >> username;

    if (findAccountIndexByUsername(username) != -1) {
        cout << "Username already exists. Choose a different username." << endl;
        return;
    }

    cout << "Choose pin: ";
    if (!(cin >> pin) || pin <= 0) {
        cout << "Invalid pin. Please enter a positive number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    accounts.push_back({username, pin});
    cout << "Account created successfully for user: " << username << endl;
}

bool loginUser() {
    string username;
    int pin;

    if (isLoggedIn) {
        cout << "Already logged in as " << currentUser << ". Please logout first." << endl;
        return true;
    }

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter pin: ";
    cin >> pin;

    int accountIndex = findAccountIndexByUsername(username);
    if (accountIndex != -1 && accounts[accountIndex].pin == pin) {
        currentUser = username;
        isLoggedIn = true;
        cout << "Login successful!" << endl;
        return true;
    }

    cout << "Invalid credentials." << endl;
    return false;
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

void changeCurrentUserPin() {
    int newPin;
    cout << "Enter new pin: ";
    if (!(cin >> newPin) || newPin <= 0) {
        cout << "Invalid pin." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findAccountIndexByUsername(currentUser);
    if (index == -1) {
        cout << "Account not found." << endl;
        return;
    }

    accounts[index].pin = newPin;
    cout << "Pin updated for user: " << currentUser << endl;
}

void showSettings() {
    cout << "\n==== Settings ====" << endl;
    cout << "Signed in as: " << currentUser << endl;
    if (canViewMobileNumber()) {
        cout << "Mobile numbers: visible (admin)" << endl;
    } else {
        cout << "Mobile numbers: hidden" << endl;
    }
    cout << "Policy: only the admin account can view student mobile numbers." << endl;

    cout << "Change pin? (1 = yes, 0 = no): ";
    int changePin;
    if (!(cin >> changePin)) {
        cout << "Invalid input." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (changePin == 1) {
        changeCurrentUserPin();
    }
}

int main() {
    
    int choice;
    vector<Student> students;
    do {
        printMenu();
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue; 
        }

        switch (choice) {
            case 1:
                if (requireLoginForWrite()) {
                    addStudent(students);
                }
                break;
            case 2:
                if (requireLoginForWrite()) {
                    listStudents(students);
                }
                break;
            case 3:
                if (requireLoginForWrite()) {
                    searchStudent(students);
                }
                break;
            case 4:
                if (requireLoginForWrite()) {
                    updateStudentProgram(students);
                }
                break;
            case 5:
                if (requireLoginForWrite()) {
                    deleteStudent(students);
                } 
                break;
            case 6:
                createAccount();
                break;
            case 7:
                loginUser();
                break;
            case 8:
                logoutUser();
                break;
            case 0:
                cout << "Exiting the program." << endl;
                break;
            case 9:
                if (requireLoginForWrite()) {
                    updateStudentContact(students);
                }
                break;
            case 10:
                if (requireLoginForWrite()) {
                    showDashboardSummary(students);
                }
                break;
            case 11:
                if (requireLoginForWrite()) {
                    showSettings();
                }
                break;
            default:
                cout << "Invalid option. Enter a number from the menu and try again." << endl;
        }
    } while(choice != 0);
    
    return 0;
}