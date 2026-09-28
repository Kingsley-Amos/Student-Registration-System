#include "Student.h"

using namespace std;

Student::Student()
{
    studentID = 0;
    age = 0;
    level = 0;
}
//constructor
Student::Student(int id, const string &fname, const string &lname, int Age,
                 const string &Gender, const string &Department, int Level,
                 const string &Phone, const string &Email)
{
    studentID = id;
    firstName = fname;
    lastName = lname;
    age = Age;
    gender = Gender;
    department = Department;
    level = Level;
    phoneNumber = Phone;
    email = Email;
}

void Student::displayStudent() const
{
    cout << "ID         : " << studentID << endl;
    cout << "Name       : " << firstName << " " << lastName << endl;
    cout << "Age        : " << age << endl;
    cout << "Gender     : " << gender << endl;
    cout << "Department : " << department << endl;
    cout << "Level      : " << level << endl;
    cout << "Phone      : " << phoneNumber << endl;
    cout << "Email      : " << email << endl;
}
//using getters
int Student::getStudentID() const { return studentID; }
string Student::getFirstName() const { return firstName; }
string Student::getLastName() const { return lastName; }
int Student::getAge() const { return age; }
string Student::getGender() const { return gender; }
string Student::getDepartment() const { return department; }
int Student::getLevel() const { return level; }
string Student::getPhone() const { return phoneNumber; }
string Student::getEmail() const { return email; }
//using setters
void Student::setFirstName(const string &fname) { firstName = fname; }
void Student::setLastName(const string &lname) { lastName = lname; }
void Student::setAge(int Age) { age = Age; }
void Student::setDepartment(const string &dept) { department = dept; }
void Student::setPhone(const string &phone) { phoneNumber = phone; }
void Student::setEmail(const string &mail) { email = mail; }
void Student::setLevel(int lvl) { level = lvl; }
