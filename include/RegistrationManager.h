#ifndef REGISTRATIONMANAGER_H
#define REGISTRATIONMANAGER_H

#include <vector>
#include "Registration.h"
#include "StudentManager.h"
#include "CourseManager.h"

class RegistrationManager
{
private:
    std::vector<Registration> registrations;
    int getValidIntegerInput() const;

public:
    void registrationMenu(const StudentManager &sm, const CourseManager &cm);
    void addRegistration(const StudentManager &sm, const CourseManager &cm);
    void displayRegistration() const;
    void searchRegistration() const;
    void deleteRegistration();


    // Cross-Referencing Schedule/Roster Features
    void displayStudentSchedule(const StudentManager &sm, const CourseManager &cm) const;
    void displayCourseRoster(const StudentManager &sm, const CourseManager &cm) const;

    // Credit check business logic helper
    int calculateCurrentCredits(int studentID, const CourseManager &cm) const;

    void saveData() const;
    void loadData();
};

#endif
