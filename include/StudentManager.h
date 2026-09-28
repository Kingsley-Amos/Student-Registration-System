#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <vector>
#include "Student.h"

class StudentManager
{
private:
    std::vector<Student> students;
    int getValidIntegerInput();

public:
    void studentMenu();
    void addStudent();
    void displayStudents();
    void searchStudent();
    void updateStudent();
    void deleteStudent();


    // Integration & File Helpers
    bool studentExists(int id) const;
    const Student* getStudent(int id) const;
    void saveData() const;
    void loadData();
};

#endif
