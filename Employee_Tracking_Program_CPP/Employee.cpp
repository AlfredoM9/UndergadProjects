#include <fstream>
#include "Employee.h"
using namespace std;

// Deafult constructor
Employee::Employee()
{
   // Initlize to empty data
   employeeID = "";
   lastName = "";
   firstName = "";
   birthDate = "";
   gender = 0;
   startDate = "";
   salary = 0;
} // end default constructor

// Constructor with only ID entered
Employee::Employee(string ID)
{
   // Sent the ID to the employee ID and initialize the rest to empty data
   employeeID = ID;
   lastName = "";
   firstName = "";
   birthDate = "";
   gender = 0;
   startDate = "";
   salary = 0;
} // end constructor with ID as parameter

// Constructor that accepts every argument
Employee::Employee(string ID, string lastN, string firstN, string DOB, char MorF, string firstDay, double pay)
{
   // Initializes the member variables to the arguments entered
   employeeID = ID;
   lastName = lastN;
   firstName = firstN;
   birthDate = DOB;
   gender = MorF;
   startDate = firstDay;
   salary = pay;
} // Constructor that accepts every argument

// Member function for a file
void Employee::setData(ifstream & inputFile, string tempID)
{
   // Stores data from a file to the member variabbles
   employeeID = tempID;
   inputFile >> lastName;
   inputFile >> firstName;
   inputFile >> birthDate;
   inputFile >> gender;
   inputFile >> startDate;
   inputFile >> salary;
} // end setData

// Mutator for employee ID
void Employee::setEmployeeID(string ID)
{
   employeeID = ID;
}

// Mutator for employee last name
void Employee::setLastName(string lastN)
{
   lastName = lastN;
}

// Mutator for employee first name
void Employee::setFirstName(string firstN)
{
   firstName = firstN;
}

// Mutator for employee birth date
void Employee::setBirthDate(string DOB)
{
   birthDate = DOB;
}

// Mutator for employee gender
void Employee::setGender(char MorF)
{
   gender = MorF;
}

// Mutator for employee start date
void Employee::setStartDate(string firstDate)
{
   startDate = firstDate;
}

// Mutator for employee salary
void Employee::setSalary(double pay)
{
   salary = pay;
}

// Accessor for employee ID
string Employee::getEmployeeID() const
{
   return employeeID;
}

// Accessor for employee last name
string Employee::getLastName() const
{
   return lastName;
}

// Accessor for employee first name
string Employee::getFirstName() const
{
   return firstName;
}

// Accessor for employee birth date
string Employee::getBirthDate() const
{
   return birthDate;
}

// Accessor for employee gender
char Employee::getGender() const
{
   return gender;
}

// Accessor for employee start date
string Employee::getStartDate() const
{
   return startDate;
}

// Accessor for employee salary
double Employee::getSalary() const
{
   return salary;
}