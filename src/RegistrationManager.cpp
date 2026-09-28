#include "RegistrationManager.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_GREEN     "\033[92m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"
#define WHITE   "\033[37m"

using namespace std;

int RegistrationManager::getValidIntegerInput() const {
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

int RegistrationManager::calculateCurrentCredits(int studentID, const CourseManager &cm) const {
    int total = 0;
    for (const auto &r : registrations) {
        if (r.getStudentID() == studentID) {
            const Courses* c = cm.getCourse(r.getCourseCode());
            if (c) total += c->getCreditHour();        //check that course exist
        }
    }
    return total;
}

void RegistrationManager::saveData() const {
    ofstream outFile("registrations.txt");
    if (!outFile) return;
    for (const auto &r : registrations) {
        outFile << r.getStudentID() << " " << r.getCourseCode() << "\n";
    }
    outFile.close();
}

void RegistrationManager::loadData() {
    ifstream inFile("registrations.txt");
    if (!inFile) return;
    registrations.clear();
    int sID;
    string cCode;
    while (inFile >> sID >> cCode) {
        registrations.push_back(Registration(sID, cCode));
    }
    inFile.close();
}

void RegistrationManager::registrationMenu(const StudentManager &sm, const CourseManager &cm) {
    int choice;
    do {
        cout <<BRIGHT_BLUE<< "\n===== REGISTRATION MANAGEMENT =====\n";
        cout<<WHITE;
        cout << "1. Add Registration (Enroll Student)\n";
        cout << "2. Display Registrations (All Linkings)\n";
        cout << "3. Search Student Registration List\n";
        cout << "4. Delete/Drop Registration\n";
        cout << "5. View Student Schedule (Cross-Referenced)\n";
        cout << "6. View Course Roster (All enrolled Students)\n";
        cout << "7. Back to Main Menu\n";
        cout <<BRIGHT_GREEN<< "Enter choice: ";
        choice = getValidIntegerInput();

        switch (choice) {
            case 1: addRegistration(sm, cm); break;
            case 2: displayRegistration(); break;
            case 3: searchRegistration(); break;
            case 4: deleteRegistration(); break;
            case 5: displayStudentSchedule(sm, cm); break;
            case 6: displayCourseRoster(sm, cm); break;
            case 7: saveData(); cout << "Data saved. Returning...\n"; break;
            default: cout <<RED<< "Invalid choice.\n";
        }
    } while (choice != 7);
}

void RegistrationManager::addRegistration(const StudentManager &sm, const CourseManager &cm) {
    int studentID;
    string courseCode;

    cout <<BRIGHT_GREEN<< "Enter Student ID: ";
    studentID = getValidIntegerInput();

    // 1. Integration Verification: Does Student Exist?
    if (!sm.studentExists(studentID)) {
        cout <<RED<< "[Error] This Student ID is not in our system.\n";
        return;
    }

    cout <<BRIGHT_GREEN<< "Enter Course Code: ";
    cin >> courseCode;

    // 2. Integration Verification: Does Course Exist?
    if (!cm.courseExists(courseCode)) {
        cout <<RED<< "[Error] This Course Code is not in our system.\n";
        return;
    }

    // 3. Double-Enrollment Check
    for (const auto &r : registrations) {
        if (r.getStudentID() == studentID && r.getCourseCode() == courseCode) {
            cout <<RED<< "[Error] Student " << studentID << " is already enrolled in " << courseCode << "!\n";
            return;
        }
    }

    // 4. Business Rule Verification: Max Credit hours limit (18)
    int pendingCredits = cm.getCourse(courseCode)->getCreditHour();
    int currentCredits = calculateCurrentCredits(studentID, cm);
    if (currentCredits + pendingCredits > 18) {
        cout << "[Error] Enrolling would put student at " << (currentCredits + pendingCredits)
             << " credits. Limit is 18 (Current: " << currentCredits << ").\n";
        return;
    }

    registrations.push_back(Registration(studentID, courseCode));
    saveData();
    cout << "Registration Successful! Current workload: " << (currentCredits + pendingCredits) << " credit(s).\n";
}

void RegistrationManager::displayRegistration() const {
    if (registrations.empty()) {
        cout <<RED<< "No active registrations.\n";
        return;
    }
    cout <<BRIGHT_BLUE<< "\n*****=== REGISTRATION LIST ===*****\n";
    for (const auto &r : registrations) {
        r.displayRegistration();
        cout <<RED<< "-----------------------------\n";
    }
}

void RegistrationManager::searchRegistration() const {
    int studentID;
    cout <<BRIGHT_GREEN<< "Enter Student ID: ";
    studentID = getValidIntegerInput();

    bool found = false;
    cout << "\nStudent Registrations found:\n";
    for (const auto &r : registrations) {
        if (r.getStudentID() == studentID) {
            cout <<BRIGHT_GREEN<< "Enrolled in: " << r.getCourseCode() << "\n";
            found = true;
        }
    }
    if (!found) cout <<RED<< "No active registrations found for this Student ID.\n";
}

void RegistrationManager::deleteRegistration() {
    int studentID;
    string courseCode;
    cout <<BRIGHT_GREEN<< "Enter Student ID: ";
    studentID = getValidIntegerInput();
    cout << "Enter Course Code: ";
    cin >> courseCode;

    auto original_size = registrations.size();
    registrations.erase(
        remove_if(registrations.begin(), registrations.end(),
                  [studentID, courseCode](const Registration &r) {
                      return r.getStudentID() == studentID && r.getCourseCode() == courseCode;
                  }),
        registrations.end()
    );

    if (registrations.size() < original_size) {
        saveData();
        cout <<RED<< "Registration Dropped/Deleted successfully.\n";
    } else {
        cout <<MAGENTA<< "No matching registration found.\n";
    }
}

void RegistrationManager::displayStudentSchedule(const StudentManager &sm, const CourseManager &cm) const {
    int studentID;
    cout <<BRIGHT_GREEN<< "Enter Student ID: ";
    studentID = getValidIntegerInput();

    const Student* s = sm.getStudent(studentID);
    if (!s) {
        cout <<RED<< "Student not found.\n";
        return;
    }

    cout <<BRIGHT_BLUE<< "\n=========================================\n";
    cout << " SCHEDULE FOR: " << s->getFirstName() << " " << s->getLastName() << " (ID: " << studentID << ")\n";
    cout << "=========================================\n";

    int totalHours = 0;
    for (const auto &r : registrations) {
        if (r.getStudentID() == studentID) {
            const Courses* c = cm.getCourse(r.getCourseCode());
            if (c) {
                cout << "- " << c->getCourseCode() << ": " << c->getCourseName() << " (" << c->getCreditHour() << " credits)\n";
                totalHours += c->getCreditHour();
            }
        }
    }
    cout <<BRIGHT_GREEN<< "Total Credit Load: " << totalHours << "  credits\n";
    cout << "=========================================\n";
}

void RegistrationManager::displayCourseRoster(const StudentManager &sm, const CourseManager &cm) const {
    string courseCode;
    cout <<MAGENTA<< "Enter Course Code: ";
    cin >> courseCode;

    const Courses* c = cm.getCourse(courseCode);
    if (!c) {
        cout <<RED<< "Course not found.\n";
        return;
    }

    cout <<BRIGHT_BLUE<< "\n=========================================\n";
    cout << " ROSTER FOR: " << c->getCourseName() << " (" << courseCode << ")\n";
    cout << "=========================================\n";

    int count = 0;
    for (const auto &r : registrations) {
        if (r.getCourseCode() == courseCode) {
            const Student* s = sm.getStudent(r.getStudentID());
            if (s) {
                cout << "- ID: " << s->getStudentID() << " | Name: " << s->getFirstName() << " " << s->getLastName() << "\n";
                count++;
            }
        }
    }
    cout <<BRIGHT_GREEN<< "Total Registered Students: " << count << "\n";
    cout <<WHITE<< "=========================================\n";
}
