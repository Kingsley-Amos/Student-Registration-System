#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>

class Registration
{
private:
    int studentID;
    std::string courseCode;

public:
    Registration();
    Registration(int sID, const std::string &cCode);

    int getStudentID() const;
    std::string getCourseCode() const;
    void displayRegistration() const;
};

#endif
