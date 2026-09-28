#include <iostream>
#include <limits>
#include "StudentManager.h"
#include "CourseManager.h"
#include "RegistrationManager.h"


using namespace std;
// Console text colors
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
#define BRIGHT_CYAN     "\033[96m"
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_YELLOW     "\033[93m"



void welcomeScreen()
{
    cout << CYAN;
    cout << "=========================================================\n";
    cout << "        UNIVERSITY OF MINES AND TECHNOLOGY (UMaT)\n";
    cout << "=========================================================\n";

    cout << GREEN;
    cout << "          STUDENT REGISTRATION SYSTEM\n\n";

    cout << YELLOW;
    cout << "      OBJECT ORIENTED PROGRAMMING PROJECT\n\n";

    cout <<BRIGHT_BLUE;
    cout << "Developed by: Group 1\n\n";

    cout << WHITE;
    cout << "Press Enter to continue...";
    cin.get();

    cout << RESET;
}


int getSafeSelection() {
    int value;
    while (true) {
        if (cin >> value) {
            return value;
        } else {
            cout << "Invalid input. Enter a number (1-4): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
#include <fstream>

// ... (your existing main.cpp code)

void resetFileSystem() {
    // Opening files with ios::trunc completely empties them
    std::ofstream studentFile("students.txt", std::ios::trunc);
    std::ofstream courseFile("courses.txt", std::ios::trunc);
    std::ofstream regFile("registrations.txt", std::ios::trunc);

    studentFile.close();
    courseFile.close();
    regFile.close();

    std::cout <<GREEN<< "\n[System] All data files successfully wiped/reset!\n";
    std::cout <<CYAN<< "Please restart the application to apply the default course catalog.\n";
}

int main() {
    welcomeScreen();
    StudentManager sm;
    CourseManager cm;
    RegistrationManager rm;

    // Load saved database configurations on startup
    sm.loadData();
    cm.loadData();
    rm.loadData();

    int choice;
    do {
        cout << "\n=========================================\n";
        cout <<BRIGHT_BLUE<< "    UNIVERSITY REGISTRATION SYSTEM       \n";
        cout<<WHITE;
        cout << "=========================================\n";
        cout << "1. Manage Students\n";
        cout << "2. Manage Courses\n";
        cout << "3. Manage Registrations\n";
        cout << "4. ** RESET ENTIRE SYSTEM **\n";
        cout <<RED<< "5. Save & Exit System\n";
        cout <<WHITE<< "=========================================\n";
        cout <<BRIGHT_YELLOW<< "Enter your choice: ";
        choice = getSafeSelection();

        switch (choice) {
            case 1:
                sm.studentMenu();
                break;
            case 2:
                cm.courseMenu();
                break;
            case 3:
                rm.registrationMenu(sm, cm);
                break;
            case 4: {
                char confirm;
                cout <<RED<< "WARNING!: This will permanently delete all students, courses, and registrations. Proceed? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    resetFileSystem();
                    return 0; // Exit program so memory vectors don't write dirty data back on close
                }
                break;
            }
            case 5:
                sm.saveData();
                cm.saveData();
                rm.saveData();
                cout <<BRIGHT_GREEN<< "\nGoodbye!\n";
                break;
            default:
                cout <<RED<< "Invalid choice!\n";
                cout <<BRIGHT_RED<< "Invalid choice! Please select 1, 2, 3, or 4.\n";

        }
    } while (choice != 4);

    return 0;
}
