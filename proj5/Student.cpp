#include "Student.h"
#include <iomanip>

// Name: Student
// Description: Default Constructor
// Preconditions: None
// Postconditions: Creates new student object
Student::Student(){}

// Name: Student (fName, lName, id)
// Description: Overloaded Constructor
// Preconditions: Data being passed is valid
// Postconditions: Creates new student object
Student::Student(string fName, string lName, int id){
    SetFName(fName);
    SetLName(lName);
    SetID(id);
}

// Name: Getters and Setters
// Description: Either returns data or sets data in class
// Preconditions: Setter data is valid
// Postconditions: Either returns data or sets data
string Student::GetFName(){return m_fName;}
string Student::GetLName(){return m_lName;}
int Student::GetID(){return m_id;}
void Student::SetFName(string fName){m_fName = fName;}
void Student::SetLName(string lName){m_lName = lName;}
void Student::SetID(int id){m_id = id;}

// Name: Overloaded <<
// Description: Prints the details of a student
// Preconditions: all variables are set valid
// Postconditions: returns an ostream with output of student
ostream& operator<<(ostream& output, Student& student){
    output << student.GetFName() << " " << student.GetLName() << ", ID: " << student.GetID() << endl;
    return output;
}

// Name: Overloaded <
// Description: Overloaded comparison operator (used for sorting)
// Preconditions: Two students being compared
// Postconditions: Returns m_lName first and then m_fName if m_lName same
bool operator<(const Student &s1, const Student &s2){
    //last name for s1 and s2 is different
    if (s1.m_lName != s2.m_lName){
        return (s1.m_lName < s2.m_lName);
    }
    //last name for s1 and s2 is the same
    else{
        return (s1.m_fName < s2.m_fName);
    }
}