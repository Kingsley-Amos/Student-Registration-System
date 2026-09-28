#include "Registration.h"
#include <iostream>

using namespace std;

Registration::Registration() : studentID(0), courseCode("") {}

Registration::Registration(int sID, const string &cCode) : studentID(sID), courseCode(cCode) {}

int Registration::getStudentID() const { return studentID; }
string Registration::getCourseCode() const { return courseCode; }

void Registration::displayRegistration() const
{
    cout << "Student ID : " << studentID << endl;
    cout << "Course Code: " << courseCode << endl;
}
