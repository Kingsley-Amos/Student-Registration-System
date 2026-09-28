#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include <vector>
#include "Courses.h"

class CourseManager
{
private:
    std::vector<Courses> courses;
    int getValidIntegerInput();

public:
    CourseManager();
    void courseMenu();
    void addCourse();
    void displayCourses();
    void searchCourse();

    void updateCourse();
    void deleteCourse();

    // Integration & File Helpers
    bool courseExists(const std::string &cCode) const;
    const Courses* getCourse(const std::string &cCode) const;
    void saveData() const;
    void loadData();
};

#endif
