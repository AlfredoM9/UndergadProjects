/**********************************************************************************
                                                                                  *
Author:     Alfredo Mejia                                                         *
Course:     CS 1337.009                                                           *
Date:       3/12/19                                                               *
Assignment: HW Assignment 4                                                       *
Compiler:   Visual Studios C++ 2017                                               *
                                                                                  *
Description: This program will create an array of pointers while each pointer     *
             is going to point to a dynamically allocated structure. The structure*
             will be assigned to one student containing the student's ID, name,   *
             test scores for 3 tests and the average score of those 3 tests. A    *
             file will contain that information. The program will loop and assign *
             each pointer to a dynamic allocated structure for each student in    *
             the file. At the same time it will assign all the information of the *
             student (in the file) into that structure. Once that is complete     *
             the array of pointers will be pointing to a structure for each       *
             student. A menu will be displayed for the user to choose from.       *
             The program will either sort the students by name or average grade.  *
             Or the program will search for a specific student based on ID.       *
             Once the user has choosen an option it will display in a fixed format*
             the information of a specific student or the list of all students.   *
             The menu will then reappear asking for the user to choose again.     *
             The menu will repeat until the user enters 0 and ends the program.   *
                                                                                  *
***********************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Create Struct
struct Student
{
   int studentID;
   string studentName;
   int testScore1, testScore2, testScore3;
   double avgScore;
};

// Create Prototypes
int getData(Student* stuList[], const int MAX_STUDENTS);
int displayMenu();
void sortInfo(Student* stuList[], int numStudents, int userChoice);
void searchStu(Student* stuList[], int numStudents);

int main()
{
   // Create array to pointers
   const int MAX_STUDENTS = 100;
   Student* stuList[MAX_STUDENTS];

   // Call getData and return the number of students
   int numStudents = getData(stuList, MAX_STUDENTS);
   int userChoice;
   do
   {
      // Call the menu function and return the user's choice
      userChoice = displayMenu();

      // If the user choose option 1 or option 2 call the sorting function
      if (userChoice == 1 || userChoice == 2)
         sortInfo(stuList, numStudents, userChoice);

      // Else if user chose option 3 call the searching function
      else if (userChoice == 3)
         searchStu(stuList, numStudents);

   } while (userChoice != 0); // end do while loop. It ends when the user entered a zero.

   // Delete any allocated memory used
   for (int count = 0; count < numStudents; count++)
      delete stuList[count];

   cout << "The program has ended" << endl;

   system("pause");
   return 0;
} // end main

/************************************************************************************************************************
FUNCT: getData
DESCR: This function will accept the array of pointers created and the maximum number of elements in the array.
       It will ask for the file name and open the file. If the file opens unsuccessfully it will display an 
       error message and ask again for the file name. Once the file opens successfully it will loop through
       the file and for each student it will create a dynamic allocated structure. It will also store the
       contents of that one student from the file into the newly created structure. It will do that until
       there is no more content in the file. The file will then be closed and the function will return the
       number of students in the file.
*************************************************************************************************************************/
int getData(Student* stuList[], const int MAX_STUDENTS)
{
   // Create string and ifstream object
   string fileName;
   ifstream inputFile;
   int numStudents = 0;

   do
   {
      // Store file name
      cin >> fileName;

      // Open the file
      inputFile.open(fileName);

      // If it fails display error message and ask again 
      if (inputFile.fail())
         cout << "An error has occured. Please reenter the file name." << endl;
   } while (inputFile.fail()); // end do while loop

   // Loop through each student and create a new structure
   for (int count = 0; count < MAX_STUDENTS && !inputFile.eof(); count++)
   {
      // Dynamically create a struct
      stuList[count] = new Student;

      // Pass all the contents for one student into that struct created
      inputFile >> (*stuList[count]).studentID  >> (*stuList[count]).studentName
                >> (*stuList[count]).testScore1 >> (*stuList[count]).testScore2
                >> (*stuList[count]).testScore3;

      // Calculate average and store it in the struct
      (*stuList[count]).avgScore = ((*stuList[count]).testScore1 + (*stuList[count]).testScore2 + (*stuList[count]).testScore3) / 3.0;

      // Increment the number of students in the file
      numStudents++;
   } // end for loop

   // Close file
   inputFile.close();

   // Return the number of students in the file
   return numStudents;
} // end getData

/*******************************************************************************************
FUNCT: displayMenu
DESCR: This function will display a menu for the user to decide what needs to be done to
       the data collected from the file. It will cin the user's choice and if the user
       does not input a valid entry then it will display an error message and display
       the menu again until a valid entry is inserted. It will then return the choice
       given by the user
********************************************************************************************/
int displayMenu()
{
   int userChoice;
   bool notValid = true;

   do
   {
      // Display menu
      cout << "Please select one from the following choices: (0, 1, 2, 3)" << endl
           << "0. End Program" << endl
           << "1. Print the list of information of each student in order by name" << endl
           << "2. Print the list of information of each student in order by average grade, highest grade first." << endl
           << "3. Print the list of information of a SPECIFIC student based on student ID" << endl;

      // If an integer is entered
      if (cin >> userChoice)
      {
         // If the integer is entered the set the flag variable to false (to end the do-while)
         if (userChoice == 0 || userChoice == 1 || userChoice == 2 || userChoice == 3)
            notValid = false;

         // Otherwise display error message and ask again
         else
            cout << "An invalid entry has been entered." << endl;

      } // end out if

      // If something else is entered that is not an integer
      else
      {
         // Clear the buffer and ingore its content
         cin.clear();
         cin.ignore();

         // Display error message
         cout << "An invalid entry has been entered." << endl;
      } // end outter else
      cout << endl;
   } while (notValid); // end do while loop until a valid choice is entered

   // return the choice entered
   return userChoice;
} // end displayMenu

/**********************************************************************************************
FUNCT: sortInfo
DESCR: This function will accept the array of pointers, the number of actual students,
       the choice given by the user. Then if the user choose option 1 then the function
       will use bubble sort to sort the students based on name. It will then display
       the list of students and their information sorted by name. If the user choose 
       option 2 then the function will use bubble sort to sort the students based 
       on highest average score to lowest average score. It will then display the
       list of students and their information sorted by average score.
***********************************************************************************************/
void sortInfo(Student* stuList[], int numStudents, int userChoice)
{
   // If the first option was selected
   if (userChoice == 1)
   {
      // Sort the students by name using bubble sort
      for (int max = (numStudents - 1); max > 0; max--)
         for (int count = 0; count < max; count++)
            // Switch places if the left one is greater than the right one
            if (((*stuList[count]).studentName) > ((*stuList[count + 1]).studentName))
            {
               // Create a temporary struct to hold all the contents of one student
               Student temp = { (*stuList[count]).studentID, (*stuList[count]).studentName,
                               (*stuList[count]).testScore1, (*stuList[count]).testScore2,
                               (*stuList[count]).testScore3, (*stuList[count]).avgScore };

               // Switch the contents
               (*stuList[count]) = { (*stuList[count + 1]).studentID , (*stuList[count + 1]).studentName, (*stuList[count + 1]).testScore1,
                                     (*stuList[count + 1]).testScore2, (*stuList[count + 1]).testScore3 , (*stuList[count + 1]).avgScore };

               // Switch the cotents
               (*stuList[count + 1]) = { temp.studentID, temp.studentName, temp.testScore1, temp.testScore2, temp.testScore3, temp.avgScore };
            } // end if and for loops

      // Display all the students in the file based on name
      cout << left << setw(10) << "ID" << left << setw(20) << "Name" << left << setw(10) << "Score 1"
           << left << setw(10) << "Score 2" << left << setw(10) << "Score 3" << right << setw(7)
           << "AvgScore" << endl;
      for (int count = 0; count < numStudents; count++)
      {

         cout << left << setw(10) << (*stuList[count]).studentID
            << left << setw(20) << (*stuList[count]).studentName
            << left << setw(10) << (*stuList[count]).testScore1
            << left << setw(10) << (*stuList[count]).testScore2
            << left << setw(10) << (*stuList[count]).testScore3
            << right << setw(7) << fixed << setprecision(2) << (*stuList[count]).avgScore << endl;
      } // end for loop for displaying
      cout << endl;
   } // end outer most if statement

   // If the user choose option 2
   else if (userChoice == 2)
   {
      // Sort the students by average score using bubble sort
      for (int max = (numStudents - 1); max > 0; max--)
         for (int count = 0; count < max; count++)
            // If the greater score is on the right then switch them
            if (((*stuList[count]).avgScore) < ((*stuList[count + 1]).avgScore))
            {
               // Create a temporary struct to hold the contents of one student
               Student temp = { (*stuList[count]).studentID, (*stuList[count]).studentName,
                               (*stuList[count]).testScore1, (*stuList[count]).testScore2,
                               (*stuList[count]).testScore3, (*stuList[count]).avgScore };

               // Switch contents
               (*stuList[count]) = { (*stuList[count + 1]).studentID, (*stuList[count + 1]).studentName, (*stuList[count + 1]).testScore1,
                                     (*stuList[count + 1]).testScore2, (*stuList[count + 1]).testScore3, (*stuList[count + 1]).avgScore };

               // Switch contents
               (*stuList[count + 1]) = { temp.studentID, temp.studentName, temp.testScore1, temp.testScore2, temp.testScore3, temp.avgScore };
            } // end if and for loops

      // Display all the students in the file based on average score
      cout << left << setw(10) << "ID" << left << setw(20) << "Name" << left << setw(10) << "Score 1"
           << left << setw(10) << "Score 2" << left << setw(10) << "Score 3" << right << setw(7)
           << "AvgScore" << endl;
      for (int count = 0; count < numStudents; count++)
      {

         cout << left << setw(10) << (*stuList[count]).studentID
              << left << setw(20) << (*stuList[count]).studentName
              << left << setw(10) << (*stuList[count]).testScore1
              << left << setw(10) << (*stuList[count]).testScore2
              << left << setw(10) << (*stuList[count]).testScore3
              << right << setw(7) << fixed << setprecision(2) << (*stuList[count]).avgScore << endl;
      } // end for loop for displaying
      cout << endl;
   } // end outer most if statement
} // end sortInfo

/**********************************************************************************************
FUNCT: searchStu
DESCR: This function will accept the array of pointers and the number of actual students.
       It will ask for the ID that the user wants to look up. It will then search through
       each student using linear search to find the matching student with the ID entered.
       If there is no student with such ID then a error message will be displayed. Otherwise
       if a student is found then the information of that specific student will be printed.
***********************************************************************************************/
void searchStu(Student* stuList[], int numStudents)
{
   // Request for the ID
   int IDentered;
   cout << "Please enter the ID of the student" << endl;
   cin >> IDentered;
   cout << endl;

   int position = -1;
   bool notFound = true;

   // Search for the ID using linear search
   for (int count = 0; count < numStudents && notFound; count++)
   {
      // If found then give the position found and set the flag variable to false
      if (IDentered == (*stuList[count]).studentID)
      {
         position = count;
         notFound = false;
      } // end if 
   } // end for loop

   // If the ID is never found request an error message
   if (notFound)
      cout << "The ID entered does not match any student on the file. Please try again." << endl;

   // Else display the contents of the student whose ID matched
   else
   {
      cout << left << setw(10) << "ID" << left << setw(20) << "Name" << left << setw(10) << "Score 1"
         << left << setw(10) << "Score 2" << left << setw(10) << "Score 3" << right << setw(7)
         << "AvgScore" << endl;
      cout << left << setw(10) << (*stuList[position]).studentID
         << left << setw(20) << (*stuList[position]).studentName
         << left << setw(10) << (*stuList[position]).testScore1
         << left << setw(10) << (*stuList[position]).testScore2
         << left << setw(10) << (*stuList[position]).testScore3
         << right << setw(7) << fixed << setprecision(2) << (*stuList[position]).avgScore << endl;
   } // end else
   cout << endl;
} // end searchStu