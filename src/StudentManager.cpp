#include "StudentManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN     "\033[92m"
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_YELLOW     "\033[93m"
#define BRIGHT_CYAN     "\033[96m"

using namespace std;

int StudentManager::getValidIntegerInput() {
    int value;
    while (true) {
        if (cin >> value) {
            return value;
        } else {
            cout <<RED<< "Invalid input. Enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
//check if student exist
bool StudentManager::studentExists(int id) const {
    for (const auto &s : students) {
        if (s.getStudentID() == id) return true;
    }
    return false;
}

const Student* StudentManager::getStudent(int id) const {
    for (const auto &s : students) {
        if (s.getStudentID() == id) return &s;
    }
    return nullptr;
}
//using outfile
void StudentManager::saveData() const {    //save current data from vector into the file
    ofstream outFile("students.txt");
    if (!outFile) return;
    for (const auto &s : students) {
        outFile << s.getStudentID() << "\n"
                << s.getFirstName() << "\n"
                << s.getLastName() << "\n"
                << s.getAge() << "\n"
                << s.getGender() << "\n"
                << s.getDepartment() << "\n"
                << s.getLevel() << "\n"
                << s.getPhone() << "\n"
                << s.getEmail() << "\n";
    }
    outFile.close();
}
//using infile
void StudentManager::loadData() {         //load data from file into program
    ifstream inFile("students.txt");
    if (!inFile) return;
    students.clear();

    int id, age, level;
    string fname, lname, gender, department, phone, email;

    while (inFile >> id) {
        inFile.ignore();
        getline(inFile, fname);
        getline(inFile, lname);
        inFile >> age;
        inFile.ignore();
        getline(inFile, gender);
        getline(inFile, department);
        inFile >> level;
        inFile.ignore();
        getline(inFile, phone);
        getline(inFile, email);

        students.push_back(Student(id, fname, lname, age, gender, department, level, phone, email));
    }
    inFile.close();
}

void StudentManager::studentMenu() {
    int choice;
    do {
        cout <<BRIGHT_BLUE "\n===== STUDENT MANAGEMENT =====\n";
        cout<<BRIGHT_CYAN;
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout <<RED<< "6. Back to Main Menu\n";
        cout <<BRIGHT_YELLOW<< "Enter choice: ";
        choice = getValidIntegerInput();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: saveData(); cout << "Data saved. Returning...\n"; break;
            default: cout <<RED<< "Invalid choice.\n";
        }
    } while (choice != 6);
}

void StudentManager::addStudent() {
    int id, age, level;
    string fname, lname, gender, department, phone, email;

    cout <<BRIGHT_YELLOW<< "Student ID: ";
    id = getValidIntegerInput();

    if (studentExists(id)) {                              //prevents duplicate student IDs
        cout <<GREEN<< "\n[Error] Student ID " << id << " already exists!\n";
        return;
    }

    cout << "First Name: "; cin >> fname;
    cout << "Last Name: "; cin >> lname;
    cout << "Age: "; age = getValidIntegerInput();
    cout << "Gender: "; cin >> gender;
    cout << "Department: "; cin >> department;
    cout << "Level: "; level = getValidIntegerInput();
    cout << "Phone: "; cin >> phone;
    cout << "Email: "; cin >> email;

    students.push_back(Student(id, fname, lname, age, gender, department, level, phone, email));
    saveData();
    cout <<BRIGHT_GREEN<< "\nStudent Added Successfully!\n";
}

void StudentManager::displayStudents() {
    if (students.empty()) {
        cout <<RED<< "No students available.\n";
        return;
    }
    for (const Student &s : students) {
        cout << "-----------------------------\n";
        s.displayStudent();
    }
    cout << "-----------------------------\n";
}

void StudentManager::searchStudent() {
    int id;
    cout <<BRIGHT_YELLOW<< "Enter Student ID: ";
    id = getValidIntegerInput();

    const Student* s = getStudent(id);
    if (s) {
        cout <<BRIGHT_GREEN<< "\nStudent Found:\n";
        cout << "-----------------------------\n";
        s->displayStudent();
        cout << "-----------------------------\n";
    } else {
        cout <<RED<< "Student Not Found.\n";
    }
}

void StudentManager::updateStudent() {
    int id;
    cout <<BRIGHT_YELLOW<< "Enter Student ID: ";
    id = getValidIntegerInput();

    for (Student &s : students) {
        if (s.getStudentID() == id) {
            int choice;
            cout <<BRIGHT_BLUE<< "\n===== UPDATE MENU =====\n";
            cout <<BRIGHT_CYAN<< "1. Change First Name\n2. Change Last Name\n3. Change Age\n4. Change Department\n5. Change Phone\n6. Change Email\n7. Change Level\nEnter Choice: ";
            choice = getValidIntegerInput();

            switch (choice) {
                case 1: { string name; cout << "Enter first name: "; cin >> name; s.setFirstName(name); break; }
                case 2: { string name; cout << "Enter last name: "; cin >> name; s.setLastName(name); break; }
                case 3: { int a; cout << "Enter Age: "; a = getValidIntegerInput(); s.setAge(a); break; }
                case 4: { string d; cout << "Enter Department: "; cin >> d; s.setDepartment(d); break; }
                case 5: { string p; cout << "Enter Phone: "; cin >> p; s.setPhone(p); break; }
                case 6: { string e; cout << "Enter Email: "; cin >> e; s.setEmail(e); break; }
                case 7: { int l; cout << "Enter Level: "; l = getValidIntegerInput(); s.setLevel(l); break; }
                default: cout << "Invalid Choice!\n"; return;
            }
            saveData();
            cout <<BRIGHT_GREEN<< "\nStudent Updated Successfully!\n";
            return;
        }
    }
    cout <<RED<< "Student Not Found.\n";
}

void StudentManager::deleteStudent() {
    int id;
    cout <<BRIGHT_YELLOW<< "Enter Student ID: ";
    id = getValidIntegerInput();

    auto original_size = students.size();
    students.erase(
        remove_if(students.begin(), students.end(), [id](const Student &s) { return s.getStudentID() == id; }),
        students.end()
    );

    if (students.size() < original_size) {
        saveData();
        cout <<BRIGHT_GREEN<< "Student Deleted Successfully.\n";
    } else {
        cout <<RED<< "Student Not Found.\n";
    }
}

