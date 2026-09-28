#include "Courses.h"
#include <iostream>

using namespace std;

Courses::Courses() : creditHour(0) {}

Courses::Courses(const string &cCode, const string &cName, int cHour)
    : courseCode(cCode), courseName(cName), creditHour(cHour) {}

void Courses::displayCourses() const
{
    cout << "Course Code: " << courseCode << endl;
    cout << "Course Name: " << courseName << endl;
    cout << "Credit Hour: " << creditHour << endl;
}

string Courses::getCourseCode() const { return courseCode; }
string Courses::getCourseName() const { return courseName; }
int Courses::getCreditHour() const { return creditHour; }

void Courses::setCourseName(const string &cName) { courseName = cName; }
void Courses::setCreditHour(int cHour) { creditHour = cHour; }
