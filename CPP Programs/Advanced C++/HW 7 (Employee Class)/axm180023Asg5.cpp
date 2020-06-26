/*************************************************************************************
                                                                                     *
Author:     Alfredo Mejia                                                            *
Course:     CS 1337.009                                                              *
Date:       3/24/19                                                                  *
Assignment: HW Assignment 2                                                          *
Compiler:   Visual Studios C++ 2017                                                  *
                                                                                     *
Description: This program will track the information of the employees. The           *
             program will first read in from a file (if it exists) and record        *
             each employee information into an allocated object: ID, name, DOB,      *
             gender, start date, and salary. If the file doesn't exist this skip     *
             will be ignored. Then a menu will be displayed. Option 1 would be if    *
             new employee information wants to be entered (if there is 100 employees *
             in the record already an error message will appear). If option 1 is     *
             selected then the new information of the employee will be gathered      *
             and stored in an object. Option 2 is to display all employees by        *
             alphabetical order by last name. Option 3 is to search up a employee    *
             by ID and display its information. Option 4 is to remove an empployee   *
             and the last option is to save all the actions done by the user in      *
             a file called "Employee.txt" and exit the program                       *
                                                                                     *
***********************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
#include "Employee.h"
using namespace std;

// Function Prototypes
int displayMenu();
bool checkFile(ifstream &inputFile);
int getData(Employee* employee[], const int MAX_EMPLOYEES, ifstream &inputFile);
void getEmployeeInfo(Employee* employee[], int &numOfEmployees, const int MAX_EMPLOYEES);
bool checkID(const string ID, const Employee* const employee[], const int numOfEmployees);
void displayEmployeeInfo(Employee* employee[], const int numOfEmployees);
string searchID(Employee* employee[], const int numOfEmployees);
void removeEmployee(Employee* employee[], int &numOfEmployees);
void saveData(Employee* employee[], const int numOfEmployees);

// main function
int main()
{
   // Create ifstream object
   ifstream inputFile;

   // Call checkFile, if file exists then it will return true otherwise it returns false
   bool fileStored = checkFile(inputFile);

   // Create a variable to hold the number of employees on record
   int numOfEmployees = 0;      

   // Create an array of pointers pointing to the Employee object 
   const int MAX_EMPLOYEES = 100;
   Employee* employee[MAX_EMPLOYEES];

   // Set all pointers to null
   for (int count = 0; count < MAX_EMPLOYEES; count++)
      employee[count] = nullptr;

   // If there is a file, call getData and return the number of employees recorded
   if (fileStored)
      numOfEmployees = getData(employee, MAX_EMPLOYEES, inputFile);

   // do-while for the menu
   int userChoice;
   do
   {
      // Call display menu and store it to use switch case
      userChoice = displayMenu();
      switch (userChoice)
      {
      case 1:
         getEmployeeInfo(employee, numOfEmployees, MAX_EMPLOYEES);
         break;
      case 2:
         displayEmployeeInfo(employee, numOfEmployees);
         break;
      case 3:
         searchID(employee, numOfEmployees);
         break;
      case 4:
         removeEmployee(employee, numOfEmployees);
         break;
      case 5:
         saveData(employee, numOfEmployees);
      } // end switch case
   } while (userChoice != 5); // while the user doesn't choose option 5 (save & exit)

   // close file
   inputFile.close();

   system("pause");
   return 0;
} // end main

/************************************************************************************************
FUNCT: displayMenu
DESCR: This function will display a menu and store the user's choice. It will validate 
       the choice of the user and display an error message if an invalid choice has 
       been entered. It will then return the user's choice.
*************************************************************************************************/
int displayMenu()
{
   // Create a flag and to store user's choice
   int userChoice;
   bool notValid = true;

   // Display Menu
   do
   {
      cout << "Please select a choice from the following:" << endl;
      cout << "1. Enter new employee information" << endl;
      cout << "2. Display all employee information in alphabetical order by last name" << endl;
      cout << "3. Look up an an employee by ID" << endl;
      cout << "4. Remove an employee" << endl;
      cout << "5. Save all data to Employee.txt & exit" << endl;

      // If a valid int is entered
      if (cin >> userChoice)
      {
         // If the choice out of range display error message
         if (userChoice < 1 || userChoice > 5)
            cout << "An invalid entry has been entered" << endl;

         // If choice valid set the flag to false
         else
            notValid = false;
      } // end if statement

      // If an int wasn't entered display error message and clear the buffer
      else
      {
         cin.clear();
         cin.ignore();
         cout << "An invalid entry has been entered" << endl;
      } // end else statement

   } while (notValid); // while the user's choice is not valid

   return userChoice;
} // end displayMenu

/********************************************************************************************
FUNCT: checkFile
DESCR: This function will accept an ifstream object and determine if a file already exists.
       It will return a boolean variable determining if the file exists.
**********************************************************************************************/
bool checkFile(ifstream & inputFile)
{
   // Open the file
   inputFile.open("Employee.txt");

   // If not opened successfully return false
   if (inputFile.fail())
      return false;
   else
      return true;
} // end checkFile

/***************************************************************************************************************************
FUNCT: getData
DESCR: This function will accept an array of pointers, the size of the maximum amount of pointers and a ifstream object.
       The function will only execute if a file exist. The function will then read in the information from the file into
       a dynamically allocated object. It will then return the number of employees recorded.
****************************************************************************************************************************/
int getData(Employee* employee[], const int MAX_NUM, ifstream & inputFile)
{
   // Create counters and flag variables
   int count = 0, numOfEmployees = 0;
   bool fileValid = true;
   string tempID;

   // While there is stuff to read from the file and the flag is set to true
   while (inputFile >> tempID && fileValid)
   {
      // While count is not greater than the maximum allowed employees
      if (count < MAX_NUM)
      {
         // Dynamically allocate an object
         employee[count] = new Employee;

         // Call the member function setData
         employee[count]->setData(inputFile, tempID);

         //Count the number of employees
         numOfEmployees++;
      } // end if statement

      else
         fileValid = false;

      count++;
   } // end while loop

   // If file has over 100 employees display error message
   if (!fileValid)
   {
      cout << "An error has occured. The size of the file is too large for the maximum number of employees." << endl << "All the data following employee ID: "
         << employee[99]->getEmployeeID() << " was not recorded in the program." << endl << endl;
   } // end if(!fileValid)

   return numOfEmployees;
} // end getData

/***********************************************************************************************************************************
FUNCT: getEmployeeInfo
DESCR: This function will get a new employee's information. It will accept the array of pointers, the number of employees,
       and the maximum allowed employees. It will first check if the array of pointers isn't full, otherwise it will ask
       the employee's information and store them in variables. Input validation will occur in some variables. Then it
       will dynamically allocate a new object and initialize it with those variables. The number of employees will be 
       incremented. It will then ask the user if a new employee wants to be added. If no, the function will be done.
*************************************************************************************************************************************/
void getEmployeeInfo(Employee* employee[], int &numOfEmployees, const int MAX_EMPLOYEES)
{
   // If the number of employees reached it maximum display error message.
   if (numOfEmployees == 100)
      cout << "The maximum number of employees on record have been reached. Please either remove an employee or check the file for issues" << endl << endl;

   else
   {
      bool valid = true;
      char userChoice;

      // Otherwise display the information needed of the employee
      do
      {
         string tempID, tempLastName, tempFirstName, tempDOB, tempStartDate;
         char tempGender;
         double tempSalary;

         cout << "Please enter the following information: " << endl;

         // If there employees on record
         if (numOfEmployees > 0)
         {
            bool validID = false;
            do
            {
               cout << "Employee ID: ";
               cin >> tempID;

               // Check the ID entered is occupied by another employee
               validID = checkID(tempID, employee, numOfEmployees);

               // If so display error message
               if (!validID)
                  cout << "This ID has been used by another employee. Please try again" << endl;

            } while (!validID); // end do-while and while the ID entered is not valid
         } // end if 

         else
         {
            cout << "Employee ID: ";
            cin >> tempID;
         }
         
         cout << "Employee last name: ";
         cin >> tempLastName;
         cout << "Employee first name: ";
         cin >> tempFirstName;
         cout << "Employee Date of Birth (MM/DD/YYYY): ";
         cin >> tempDOB;

         // Check valid character is entered
         do
         {
            cout << "Employee's gender M or F: ";
            cin >> tempGender;
            if (toupper(tempGender) != 'M' && toupper(tempGender) != 'F')
               cout << "Please enter a valid character" << endl;
         } while (toupper(tempGender) != 'M' && toupper(tempGender) != 'F'); // end do while

         cout << "Employee's start date (MM/DD/YYYY): ";
         cin >> tempStartDate;
         bool notValidPay = true;

         // Check valid salary is entered
         do
         {
            cout << "Employee's salary per year: ";
            if (cin >> tempSalary)
            {
               if (tempSalary <= 0)
                  cout << "Please enter a valid salary" << endl;
               else
                  notValidPay = false;
            } // end if
            else
            {
               cout << "Please enter a valid salary" << endl;
               cin.clear();
               cin.ignore();
            } // end else

         } while (notValidPay); // end do-while and while a tempSalary is not valid

         // Create a new object with the information gathered
         employee[numOfEmployees] = new Employee(tempID, tempLastName, tempFirstName, tempDOB, tempGender, tempStartDate, tempSalary);

         // Increment the number of employees
         numOfEmployees++;

         // If the maximum has been reached display message
         if (numOfEmployees == MAX_EMPLOYEES)
         {
            cout << "The maximum number of employees has been reached." << endl << endl;
            valid = false;
         } // end if

         // Otherwise ask if another employee wants to be entered
         else
         {
            // Check valid character is entered
            do
            {
               cout << "Would you like to add another employee (Y or N): ";
               cin >> userChoice;
               userChoice = toupper(userChoice);
               if (userChoice != 'Y' && userChoice != 'N')
                  cout << "Please enter a valid character" << endl;
            } while (userChoice != 'Y' && userChoice != 'N'); // end do-while and while a valid character is entered
         }
      } while (valid && userChoice == 'Y'); // end do-while (outter) until the maximum has been reached or the user enters 'N'
   } // end outter most else

} // end getData

/**************************************************************************************************
FUNCT: checkID
DESCR: This function will accept a string, a pointer to objects, and the number of employees.
       It will search a string (ID) with the IDs stored in the employees' object. If one
       is found it will return true otherwise it will return false.
***************************************************************************************************/
bool checkID(const string ID, const Employee* const employee[], const int numOfEmployees)
{
   // Create a flag
   bool validID = true;

   for (int count = 0; count < numOfEmployees; count++)
   {
      // If ID entered matches an ID set the flag to false
      if (ID == employee[count]->getEmployeeID())
         validID = false;
   }

   return validID;
} // end checkID

/**********************************************************************************************************
FUNCT: displayEmployeeInfo
DESCR: This function will display the employee's information by alphabetical order by last name.
       It will accept the array of pointers to objects and the number of employees. If no employees
       on record the user will be adivsed. Otherwise the function will first sort the pointers to 
       objects by last name. Once it's finished it will display the sorted array of pointers to objects
       by last name.
************************************************************************************************************/
void displayEmployeeInfo(Employee* employee[], const int numOfEmployees)
{
   // If no employees are recorded display error message
   if (numOfEmployees == 0)
      cout << "There are no employees recorded" << endl;

   else
   {
      // Sort the employee information by last name
      for (int max = (numOfEmployees - 1); max > 0; max--)
         for (int count = 0; count < max; count++)
            if ((employee[count]->getLastName()) > (employee[count + 1]->getLastName()))
            {
               Employee temp(employee[count]->getEmployeeID(), employee[count]->getLastName(), employee[count]->getFirstName(), employee[count]->getBirthDate(), employee[count]->getGender(), employee[count]->getStartDate(), employee[count]->getSalary());

               // Switch the contents
               (*employee[count]) = (*employee[count + 1]);

               // Switch the cotents
               (*employee[count + 1]) = temp;
            } // end if
      // Display Headers
      cout << left << setw(10) << "ID" << left << setw(20) << "Last Name" << left << setw(20) << "First Name"
         << left << setw(20) << "DOB" << left << setw(10) << "Gender" << left << setw(20)
         << "Start Date" << "Salary" << endl;

      // Display sorted employee information
      for (int count = 0; count < numOfEmployees; count++)
      {

         cout << left << setw(10) << employee[count]->getEmployeeID()
            << left << setw(20) << employee[count]->getLastName()
            << left << setw(20) << employee[count]->getFirstName()
            << left << setw(20) << employee[count]->getBirthDate()
            << left << setw(10) << employee[count]->getGender()
            << left << setw(20) << employee[count]->getStartDate()
            << "$ " << static_cast<int>(employee[count]->getSalary() + 0.5) << endl;
      } // end for loop for displaying
     
   } // end else
   cout << endl;
} // end displayData

/********************************************************************************************************************
FUNCT: searchID
DESCR: The function will accept the array of pointers to objects and the number of employees. It will search
       an ID entered by the user with the ID stored in the objects. If found then the information will be 
       displayed and the ID will be returned. Otherwise an error message will be printed and "notValid" will be
       return.
**********************************************************************************************************************/
string searchID(Employee* employee[], const int numOfEmployees)
{
   // Create flag
   bool notFound = true;
   string tempID;

   // If no employee on record display error message
   if (numOfEmployees == 0)
      cout << "There are no employees recorded" << endl;
   else
   {
      // Store ID looking up
      int position = -1;
      cout << "Please enter the ID you want to search: ";
      cin >> tempID;

      for (int count = 0; count < numOfEmployees && notFound; count++)
      {
         // If ID match then store the position and set the flag to false
         if (tempID == employee[count]->getEmployeeID())
         {
            position = count;
            notFound = false;
         } // end if
      } // end for

      // If not found display message
      if (notFound)
         cout << "The ID entered was not found. Please try again." << endl;

      //Otherwise display the information of the employee with that ID
      else
      {
         cout << left << setw(10) << "ID" << left << setw(20) << "Last Name" << left << setw(20) << "First Name"
            << left << setw(20) << "DOB" << left << setw(10) << "Gender" << left << setw(20)
            << "Start Date" << "Salary" << endl;
         cout << left << setw(10) << employee[position]->getEmployeeID()
            << left << setw(20) << employee[position]->getLastName()
            << left << setw(20) << employee[position]->getFirstName()
            << left << setw(20) << employee[position]->getBirthDate()
            << left << setw(10) << employee[position]->getGender()
            << left << setw(20) << employee[position]->getStartDate()
            << "$ " << static_cast<int>(employee[position]->getSalary() + 0.5) << endl;
      } // end inner else

   } // end outter most else
   cout << endl;

   if (notFound)
      return "notValid";
   else
      return tempID;
} // end searchID

/***************************************************************************************************************************
FUNCT: removeEmployee
DESCR: This function will accept the array of pointers to objects and the number of employees. It will
       delete the employee with the ID matched with the user's input. It will be overwritten by the employee
       following it. The employee information will all shift down making a duplicate at the very end. That memory will
       be freed and assigned to the nullptr. The employee entered has been deleted.
*****************************************************************************************************************************/
void removeEmployee(Employee* employee[], int &numOfEmployees)
{
   // Store the ID the user wants to delete
   string validID;
   validID = searchID(employee, numOfEmployees);
   
   // If ID is valid
   if (validID != "notValid")
   {
      // Set flag
      int loopDone = false;
      cout << "The following information of the employee above will be deleted" << endl;

      // Search employee with that ID
      for (int count = 0; count < numOfEmployees && !loopDone; count++)
      {
         // Once found
         if (validID == employee[count]->getEmployeeID())
         {
            // Move the contents to close the gap
            for (int count2 = count; count2 < (numOfEmployees - 1); count2++)
            {
               (*employee[count2]) = (*employee[count2 + 1]);
            } // end inner for loop
            loopDone = true;
         } // end if
      } // end outter for loop

      // If the employee was deleted
      if (loopDone)
      {
         // Create a temporary pointer pointing to the last object
         Employee *tempPtr;
         tempPtr = employee[numOfEmployees - 1];

         // Free the memory allocated to the object
         delete tempPtr;

         // Set the pointers to null
         tempPtr = nullptr;
         employee[numOfEmployees - 1] = nullptr;

         // Decrease the amount of employees on record
         numOfEmployees--;
      } // end inner if
      cout << "The following employee with the ID " << validID << " has been successfully deleted" << endl;
   } // end outter if
   cout << endl;
} // end removeEmployee

/***********************************************************************************************************
FUNCT: saveData
DESCR: This function will accept an array of pointers to objects and the number of employees on record.
       It will then create a ofstream object and pass all the information of all employees into the 
       file.
************************************************************************************************************/
void saveData(Employee* employee[], const int numOfEmployees)
{
   // Create file
   ofstream outputFile;
   outputFile.open("Employee.txt");

   // If no employees on record then display message
   if (numOfEmployees == 0)
      cout << "The following file has been created \"Employee.txt\", however there was no employees recorded, so the file is empty" << endl;

   else
   {
      // Store all the data of the employees in the file
      for (int count = 0; count < numOfEmployees; count++)
      {
         outputFile << employee[count]->getEmployeeID()
            << " " << employee[count]->getLastName()
            << " " << employee[count]->getFirstName()
            << " " << employee[count]->getBirthDate()
            << " " << employee[count]->getGender()
            << " " << employee[count]->getStartDate()
            << " " << employee[count]->getSalary() << endl;
      } // end for loop
      cout << "The file \"Employee.txt\" was succesfully created and the data has been transfered into the file" << endl;
   } // end else

   // Close file
   outputFile.close();
} // end saveData