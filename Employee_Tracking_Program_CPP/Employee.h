#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <fstream>
using namespace std;

// Create class
class Employee
{
private:
   // Information of an employee
   string employeeID;
   string lastName;
   string firstName;
   string birthDate; 
   char gender;
   string startDate;
   double salary;
  

public:
   // Constructors
   Employee();
   Employee(string);
   Employee(string, string, string, string, char, string, double);

   // Set and get functions for each member variable
   void setData(ifstream &, string);
   void setEmployeeID(string);
   void setLastName(string);
   void setFirstName(string);
   void setBirthDate(string);
   void setGender(char);
   void setStartDate(string);
   void setSalary(double);
   string getEmployeeID() const;
   string getLastName() const;
   string getFirstName() const;
   string getBirthDate() const;
   char getGender() const;
   string getStartDate() const;
   double getSalary() const;

}; // end of class declaration

#endif