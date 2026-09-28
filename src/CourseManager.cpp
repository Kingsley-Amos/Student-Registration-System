#include "CourseManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#define RED     "\033[31m"
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_CYAN     "\033[96m"
#define BRIGHT_GREEN     "\033[92m"
#define BRIGHT_RED     "\033[91m"

using namespace std;

CourseManager::CourseManager() {
    // Standard starting catalog
    courses.push_back(Courses("CE162", "Object Oriented Programming", 2));
    courses.push_back(Courses("CE164", "Basic Electronics", 3));
    courses.push_back(Courses("CE166", "Calculus", 3));
    courses.push_back(Courses("CE170", "Database System", 2));
    courses.push_back(Courses("CE172", "Web Programming", 2));
}

int CourseManager::getValidIntegerInput() {
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

bool CourseManager::courseExists(const string &cCode) const {
    for (const auto &c : courses) {
        if (c.getCourseCode() == cCode) return true;
    }
    return false;
}

const Courses* CourseManager::getCourse(const string &cCode) const {
    for (const auto &c : courses) {
        if (c.getCourseCode() == cCode) return &c;
    }
    return nullptr;
}

void CourseManager::saveData() const {
    ofstream outFile("courses.txt");
    if (!outFile) return;
    for (const auto &c : courses) {
        outFile << c.getCourseCode() << "\n"
                << c.getCourseName() << "\n"
                << c.getCreditHour() << "\n";
    }
    outFile.close();
}

void CourseManager::loadData() {
    ifstream inFile("courses.txt");
    if (!inFile) return;
    courses.clear();

    string cCode, cName;
    int cHour;

    while (inFile >> cCode) {
        inFile.ignore();
        getline(inFile, cName);
        inFile >> cHour;
        inFile.ignore();
        courses.push_back(Courses(cCode, cName, cHour));
    }
    inFile.close();
}

void CourseManager::courseMenu() {
    int choice;
    do {
        cout <<BRIGHT_BLUE<< "\n===== COURSE MANAGEMENT =====\n";
        cout<<BRIGHT_CYAN;
        cout << "1. Add Course\n";
        cout << "2. Display Courses\n";
        cout << "3. Search Course\n";
        cout << "4. Update Course\n";
        cout << "5. Delete Course\n";
        cout <<RED<< "6. Back to Main Menu\n";
        cout <<BRIGHT_GREEN<< "Enter choice: ";
        choice = getValidIntegerInput();

        switch (choice) {
            case 1: addCourse(); break;
            case 2: displayCourses(); break;
            case 3: searchCourse(); break;
            case 4: updateCourse(); break;
            case 5: deleteCourse(); break;
            case 6: saveData(); cout <<BRIGHT_GREEN<< "Data saved. Returning...\n"; break;
            default: cout <<RED<< "Invalid choice.\n";
        }
    } while (choice != 6);
}

void CourseManager::addCourse() {
    int cHour;
    string cName, cCode;
    cout<<BRIGHT_CYAN;
    cout << "Course Code: "; cin >> cCode;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Course Name: "; getline(cin, cName);
    cout << "Course Hour: "; cHour = getValidIntegerInput();

    if (courseExists(cCode)) {
        cout <<RED<< "\n[Error] Course Code " << cCode << " already exists!\n";
        return;
    }

    courses.push_back(Courses(cCode, cName, cHour));
    saveData();
    cout <<BRIGHT_GREEN<< "\nCourse Added Successfully!\n";
}

void CourseManager::displayCourses() {
    if (courses.empty()) {
        cout <<RED<<"No courses available.\n";
        return;
    }
    cout <<BRIGHT_BLUE<< "\n*****=== AVAILABLE COURSES ===*****\n";
    for (const auto &c : courses) {
        cout <<BRIGHT_RED<< "-----------------------------\n";
        c.displayCourses();
    }
    cout <<BRIGHT_RED<<"-----------------------------\n";
}

void CourseManager::searchCourse() {
    string cCode;
    cout <<BRIGHT_RED<< "Enter Course Code: "; cin >> cCode;

    const Courses* c = getCourse(cCode);
    if (c) {
        cout <<BRIGHT_GREEN<< "\nCourse Found:\n";
        c->displayCourses();
    } else {
        cout <<RED<< "Course Not Found.\n";
    }
}

void CourseManager::updateCourse() {
    string cCode;
    cout <<BRIGHT_RED<<"Enter Course Code: "; cin >> cCode;

    for (Courses &c : courses) {
        if (c.getCourseCode() == cCode) {
            int choice;
            cout << BRIGHT_BLUE<<"\n===== UPDATE MENU =====\n1. Change Name\n2. Change Credit Hours\n3. Cancel\nEnter Choice: ";
            choice = getValidIntegerInput();

            switch (choice) {
                case 1: {
                    string name;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter course name: ";
                    getline(cin, name);
                    c.setCourseName(name);
                    break;
                }
                case 2: {
                    int hour;
                    cout <<BRIGHT_RED<<"Enter Credit hour: ";
                    hour = getValidIntegerInput();
                    c.setCreditHour(hour);
                    break;
                }
                default: cout <<RED<<"Update Cancelled\n"; return;
            }
            saveData();
            cout << "\nCourse Updated Successfully!\n";
            return;
        }
    }
    cout <<RED<<"Course Not Found.\n";
}

void CourseManager::deleteCourse() {
    string cCode;
    cout <<BRIGHT_CYAN<< "Enter Course Code: "; cin >> cCode;

    auto original_size = courses.size();
    courses.erase(
        remove_if(courses.begin(), courses.end(), [cCode](const Courses &c) { return c.getCourseCode() == cCode; }),
        courses.end()
    );

    if (courses.size() < original_size) {
        saveData();
        cout <<BRIGHT_CYAN<< "Course Deleted Successfully.\n";
    } else {
        cout <<RED<< "Course Not Found.\n";
    }
}
