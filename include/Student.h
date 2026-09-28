#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student
{
private:
    int studentID;
    std::string firstName;
    std::string lastName;
    int age;
    std::string gender;
    std::string department;
    int level;
    std::string phoneNumber;
    std::string email;

public:
    Student();
    Student(int id,
            const std::string &fname,
            const std::string &lname,
            int age,
            const std::string &gender,
            const std::string &department,
            int level,
            const std::string &phone,
            const std::string &email);

    void displayStudent() const;

    // Getters
    int getStudentID() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getDepartment() const;
    int getLevel() const;
    std::string getPhone() const;
    std::string getEmail() const;

    // Setters
    void setFirstName(const std::string &fname);
    void setLastName(const std::string &lname);
    void setAge(int age);
    void setDepartment(const std::string &dept);
    void setPhone(const std::string &phone);
    void setEmail(const std::string &mail);
    void setLevel(int lvl);
};

#endif
