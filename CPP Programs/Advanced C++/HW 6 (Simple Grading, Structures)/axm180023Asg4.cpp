/**********************************************************************************
                                                                                  *
Author:     Alfredo Mejia                                                         *
Course:     CS 1337.009                                                           *
Date:       2/24/19                                                               *
Assignment: HW Assignment 2                                                       *
Compiler:   Visual Studios C++ 2017                                               *
                                                                                  *
Description:                                                                      *
                                                                                  *
***********************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Student
{
   int studentID;
   string studentName;
   int testScore1, testScore2, testScore3;
   double avgScore;
};

int getData(Student* stuList[], const int MAX_STUDENTS);
int displayMenu();
void sortInfo(Student* stuList[], int numStudents, int userChoice);
void searchStu(Student* stuList[], int numStudents);
int main()
{
   const int MAX_STUDENTS = 100;
   Student* stuList[MAX_STUDENTS];
   int numStudents = getData(stuList, MAX_STUDENTS);
   int userChoice;
   do
   {
      userChoice = displayMenu();
      if (userChoice == 1 || userChoice == 2)
         sortInfo(stuList, numStudents, userChoice);

      else if (userChoice == 3)
         searchStu(stuList, numStudents);

   } while (userChoice != 0);
   
   for (int count = 0; count < numStudents; count++)
      delete stuList[count];

   cout << "The program has ended" << endl;
   system("pause");
   return 0;
}

int getData(Student* stuList[], const int MAX_STUDENTS)
{
   string fileName;
   ifstream inputFile;
   int numStudents = 0;
   do
   {
      cin >> fileName;
      inputFile.open(fileName);
      if (inputFile.fail())
         cout << "An error has occured. Please reenter the file name." << endl;
   } while (inputFile.fail());

   for (int count = 0; count < MAX_STUDENTS && !inputFile.eof(); count++)
   {
      stuList[count] = new Student;
      inputFile >> (*stuList[count]).studentID >> (*stuList[count]).studentName
                >> (*stuList[count]).testScore1 >> (*stuList[count]).testScore2 
                >> (*stuList[count]).testScore3;

      (*stuList[count]).avgScore = ((*stuList[count]).testScore1 + (*stuList[count]).testScore2 + (*stuList[count]).testScore3) / 3.0;
      numStudents++;
   }

   inputFile.close();
   return numStudents;
}

int displayMenu()
{
   int userChoice;
   bool notValid = true;
   do
   {   
         
      cout << "Please select one from the following choices: (0, 1, 2, 3)" << endl
           << "0. End Program" << endl
           << "1. Print the list of information of each student in order by name" << endl
           << "2. Print the list of information of each student in order by average grade, highest grade first." << endl
           << "3. Print the list of information of a SPECIFIC student based on student ID" << endl;
      if (cin >> userChoice)
      {
         if (userChoice == 0 || userChoice == 1 || userChoice == 2 || userChoice == 3)
         notValid = false;

         else
         {
            cout << "An invalid entry has been entered." << endl;
            notValid = true;
         }
      }
      else
      {
         cin.clear();
         cin.ignore();
         cout << "An invalid entry has been entered." << endl;
      }
         

   } while (notValid);

   return userChoice;
}

void sortInfo(Student* stuList[], int numStudents, int userChoice)
{
   if (userChoice == 1)
   {
      for (int max = (numStudents - 1); max > 0; max--)
         for (int count = 0; count < max; count++)
            if (((*stuList[count]).studentName) > ((*stuList[count + 1]).studentName))
            {
               Student temp = { (*stuList[count]).studentID, (*stuList[count]).studentName,
                               (*stuList[count]).testScore1, (*stuList[count]).testScore2,
                               (*stuList[count]).testScore3, (*stuList[count]).avgScore };

               (*stuList[count]) = { (*stuList[count + 1]).studentID, (*stuList[count + 1]).studentName, (*stuList[count + 1]).testScore1,
                                     (*stuList[count + 1]).testScore2, (*stuList[count + 1]).testScore3, (*stuList[count + 1]).avgScore };

               (*stuList[count + 1]) = { temp.studentID, temp.studentName, temp.testScore1, temp.testScore2, temp.testScore3, temp.avgScore };
            }
      cout << left << setw(10) << "ID" << left << setw(20) << "Name" << left << setw(10) << "Score 1" << left << setw(10) << "Score 2" << left << setw(10) << "Score 3" << right << setw(7) << "AvgScore" << endl;
      for (int count = 0; count < numStudents; count++)
      {
         
         cout << left << setw(10) << (*stuList[count]).studentID
            << left << setw(20) << (*stuList[count]).studentName
            << left << setw(10) << (*stuList[count]).testScore1
            << left << setw(10) << (*stuList[count]).testScore2
            << left << setw(10) << (*stuList[count]).testScore3
            << right << setw(7) << fixed << setprecision(2) << (*stuList[count]).avgScore << endl;
      }
   }

   else if (userChoice == 2)
   {
      for (int max = (numStudents - 1); max > 0; max--)
         for (int count = 0; count < max; count++)
            if (((*stuList[count]).avgScore) < ((*stuList[count + 1]).avgScore))
            {
               Student temp = { (*stuList[count]).studentID, (*stuList[count]).studentName,
                               (*stuList[count]).testScore1, (*stuList[count]).testScore2,
                               (*stuList[count]).testScore3, (*stuList[count]).avgScore };
               
               (*stuList[count]) = { (*stuList[count + 1]).studentID, (*stuList[count + 1]).studentName, (*stuList[count + 1]).testScore1,
                                     (*stuList[count + 1]).testScore2, (*stuList[count + 1]).testScore3, (*stuList[count + 1]).avgScore };

               (*stuList[count + 1]) = { temp.studentID, temp.studentName, temp.testScore1, temp.testScore2, temp.testScore3, temp.avgScore };
            }
      cout << left << setw(10) << "ID" << left << setw(20) << "Name" << left << setw(10) << "Score 1" << left << setw(10) << "Score 2" << left << setw(10) << "Score 3" << right << setw(7) << "AvgScore" << endl;
      for (int count = 0; count < numStudents; count++)
      {

         cout << left << setw(10) << (*stuList[count]).studentID
            << left << setw(20) << (*stuList[count]).studentName
            << left << setw(10) << (*stuList[count]).testScore1
            << left << setw(10) << (*stuList[count]).testScore2
            << left << setw(10) << (*stuList[count]).testScore3
            << right << setw(7) << fixed << setprecision(2) << (*stuList[count]).avgScore << endl;
      }
   }
}

void searchStu(Student* stuList[], int numStudents)
{
   int IDentered;
   cout << "Please enter the ID of the student" << endl;
   cin >> IDentered;

   int position = -1;
   bool notFound = true;

   for (int count = 0; count < numStudents && notFound; count++)
   {
      if (IDentered == (*stuList[count]).studentID)
      {
         position = count;
         notFound = false;
      }
   }
   if (notFound)
      cout << "There is student whose's ID matches the one entered. Please try again." << endl;
   else
   {
      cout << "Student ID     Student Name     Test Score 1     Test Score 2     Test Score 3     Average Score" << endl;
      cout << left << setw(10) << (*stuList[position]).studentID
         << left << setw(20) << (*stuList[position]).studentName
         << left << setw(7) << (*stuList[position]).testScore1
         << left << setw(7) << (*stuList[position]).testScore2
         << left << setw(7) << (*stuList[position]).testScore3
         << right << setw(7) << fixed << setprecision(2) << (*stuList[position]).avgScore << endl;
   }
}
