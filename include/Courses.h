#ifndef COURSES_H
#define COURSE_H
#include <string>

class Courses
{
private:
    std::string courseCode;
    std::string courseName;
    int creditHour;

public:
    Courses();
    Courses(const std::string &cCode, const std::string &cName, int cHour);

    void displayCourses() const;

    // Getters
    std::string getCourseCode() const;
    std::string getCourseName() const;
    int getCreditHour() const;

    // Setters
    void setCourseName(const std::string &cName);
    void setCreditHour(int cHour);
};

#endif
