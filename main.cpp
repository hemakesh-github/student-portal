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

int main() {
   
    
    return 0;
}