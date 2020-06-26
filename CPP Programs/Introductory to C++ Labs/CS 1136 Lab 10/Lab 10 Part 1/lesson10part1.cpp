// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       12/8/18
// Assignment: Lab 10 Part 1
// Compiler:   Visual C++ 2017

/**********************************************************************************************************************************
Description: This program will read in two file names from a test. One is for the student and the other is for the answer key.
             The file of the student will be opened and stored into the a character array. The answer key file will be opened
             and stored in a character array. The student array has the answers choosen by the student. The other array will
             have the correct answers for the test. The program will compare both and determine if the student passed or not.
             It will display the question missed, the incorrect answer choosen by the student, and the correct answer. At the 
             end of the report it will show total questions missed and determine if the student passed or failed.
************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function prototypes
bool readData(char answers[], const int NUM_QUESTIONS,string fileName);
void displayResults(char correctAnswers[], char studentAnswers[], const int ANSWERS);

int main()
{
   // Create string variables for the user input
   string studentFile, adminFile;

   // Gather the files' name
   cin >> studentFile;
   cin >> adminFile;

   // Each file has 20 answers
   const int ANSWERS = 20;

   // Create arrays to hold the answers for the student and the answer key
   char studentAnswers[ANSWERS];
   char correctAnswers[ANSWERS];

   // Will determine if the file was successfully read or not
   bool successOrNot;

   // Call readData to pass the data into the array of the student
   successOrNot = readData(studentAnswers, ANSWERS, studentFile);

   // If successfully read: continue
   if (successOrNot)
   {
      // Call readData again but with a different file for a different array
      successOrNot = readData(correctAnswers, ANSWERS, adminFile);

      // If sucessfully read: continue & call displayResults to display the report
      if (successOrNot)
         displayResults(correctAnswers, studentAnswers, ANSWERS);

      // Otherwise display error message
      else
         cout << "File \"" << adminFile << "\" could not be opened" << endl;
   } // end if (successOrNot)

   // Otherwise display error message
   else
      cout << "File \"" << studentFile << "\" could not be opened" << endl;

   return 0;
} // end function main

/******************************************************************************************************************
Function: readData (char answers[], const int NUM_QUESTIONS, string fileName, ifstream & inputFile)
Descr:    This function will read an array, a size delcarator, a file name, and a file. It will open
          the file given by the file name, if it doesn't opened it will return a false. If it does open
          sucessfully the function will use a while loop to insert data into the array.
Return:   Boolean variable (determines if the file was successfully read or not)
********************************************************************************************************************/
bool readData(char answers[], const int NUM_QUESTIONS, string fileName)
{
   // Create ifstream variables
   ifstream inputFile;

   // Open file
   inputFile.open(fileName);

   // If failed return false
   if (inputFile.fail())
      return false;

   // If opened
   else
   {
      // Use while loop to insert data into an array
      int count = 0;
      while (count < NUM_QUESTIONS && inputFile >> answers[count])
         count++;

      // Close file after using
      inputFile.close();

      // return true
      return true;

   } // end else statement

} // end function readData

/********************************************************************************************************************************
Function: displayResults(char correctAnswers[], char studentAnswers[], const int ANSWERS)
Descr:    This function will read in two character arrays, one holding the student's answers, and the other
          holding the answer key. It will also read into the size declarator for both arrays. The function will
          use a for loop to compare each answer of the student with the answer key. If the student answered incorrectly
          it will display the question number, the incorrect choice the student chose, and the correct answer the answer
          key has. At the end it will display how many questions the student missed and determine if the student passed
          or not.
Return:   Void
***********************************************************************************************************************************/
void displayResults(char correctAnswers[], char studentAnswers[], const int ANSWERS)
{
   // Variable for the questionsMissed
   unsigned int questionsMissed = 0;

   // for loop to compare answers
   for (int count = 0; count < ANSWERS; count++)
   {
      // If it doesn't match (that means the student is incorrect)
      if (correctAnswers[count] != studentAnswers[count])
      {
         // Display report, question missed, what the student chose, and what the correct answer was
         cout << "Question " << (count + 1) << " has incorrect answer '" << studentAnswers[count] << "', ";
         cout << "the correct answer is '" << correctAnswers[count] << "'" << endl;
         questionsMissed++;
      } // end if (correctAnswers[count] != studentAnswers[count])
   } // end for (int count = 0; count < ANSWERS; count++)

   // Display the total missed questions
   cout << questionsMissed << " questions were missed" << endl;

   // If student has 70% or more: display passing message
   if (questionsMissed <= 6)
      cout << "The student passed" << endl;

   // Otherwise display failing message
   else
      cout << "The student failed" << endl;
} // end function displayResults
