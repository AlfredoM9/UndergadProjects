// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       12/8/18
// Assignment: HW 9 Excersie 2
// Compiler:   Visual C++ 2017

/***************************************************************************************************************************************************
Description: This program will read from two files, one containing correct answers to a test, and the other containing the answers from the
             students of the test. It will then compared each student's answers to the correct answers and determine their percentage of the
             test, the amount of questions missed, and if they passed or not. It will then display a report for each student and output a file 
             of the same report.
*****************************************************************************************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

// Global const: helps with 2D array & functions
const int ANSWERS = 20;

// Function prototypes
void displayReport(char correctAnswers[], char studentAnswers[][ANSWERS], int numOfStudents);
void outputReport(char correctAnswers[], char studentAnswers[][ANSWERS], int numOfStudents);
void readCorrectAnswers(char correctAnswers[], const int ANSWERS, ifstream & inputFile);
int readStudentAnswers(char studentAnswers[][ANSWERS], const int STUDENTS, ifstream & inputFile2);


// main function
int main()
{
   // Create ifstream variables
   ifstream inputFileCorrect, inputFileStudent;

   // Open both files
   inputFileCorrect.open("CorrectAnswers.txt");
   inputFileStudent.open("StudentAnswers.txt");

   // If any of the file failes to open: display error message
   if (inputFileCorrect.fail() || inputFileStudent.fail())
      cout << "One or more of the files was unable to be opened" << endl;

   // If both files opened successfully
   else
   {
      // Create const int for array boundaries
      const int STUDENTS = 15;

      // Create arrays to hold the answer key to the test and the student's choices to the test
      char correctAnswers[ANSWERS];
      char studentAnswers[STUDENTS][ANSWERS];

      // Create variable to hold the actual amount of students in the file
      int numOfStudents;

      // Call readCorrectAnswers for the array to hold the answer key from the file
      readCorrectAnswers(correctAnswers, ANSWERS, inputFileCorrect);

      // Call readStudentAnswers for the array to hold the student's choices and return the amount of students
      numOfStudents = readStudentAnswers(studentAnswers, STUDENTS, inputFileStudent);

      // Close both files
      inputFileCorrect.close();
      inputFileStudent.close();

      // Call displayReport to display the report with the information gathered
      displayReport(correctAnswers, studentAnswers, numOfStudents);

      // Call outputReport to create a file with the report with the information gathered
      outputReport(correctAnswers, studentAnswers, numOfStudents);

   } // end else statement

   system("pause");

   return 0;

} // end function main

/**************************************************************************************************************************************************************
*Function: readCorrectAnswers(char correctAnswers[], const int ANSWERS, ifstream & inputFileCorrect)
*Descr:    The function will read in an array of characters, a const integer which is the size declarator for the array, and input file to read from.
*          It will then use a while loop to read from the input file into the array of characters.
*Input:    correctAnswers (character array), ANSWERS (const int), inputFileCorrect (inputfile to be read from)
*Return:   void
***************************************************************************************************************************************************************/
void  readCorrectAnswers(char correctAnswers[], const int ANSWERS, ifstream & inputFileCorrect)
{
   // Create counter variable
   int counter = 0;

   // While loop to read data into an array
   while (counter < ANSWERS && inputFileCorrect >> correctAnswers[counter])
      counter++;

} // end function readCorrectAnswers

/****************************************************************************************************************************************************************************
Function: readStudentAnswers(char studentAnswers[][ANSWERS], const int STUDENTS, ifstream & inputFileStudent)
Descr:    This function will read in a character 2D array to hold each student's choice to the test. It will read in the size declarator
          for students, and it will read in an input file to read in all of the student's choices. It will first use a outer for loop to control
          which student the choices belong to. Then in the inner while loop it will go through each answer for that one student. It will read in the data
          into a 2D array using an outer and inner loop. It will then use a boolean variable to determine if the student had choices in the file. This will
          help determine how many students there are in the file. The number of students will be assigned to a variable and returned in order to help with other
          functions and the 2D array.
Input:    studentAnswers (character array), STUDENTS (size declarator for number of students), inputFileStudent (file that has all student's choices)
Return:   A integer that holds the number of students in the file
*****************************************************************************************************************************************************************************/
int readStudentAnswers(char studentAnswers[][ANSWERS], const int STUDENTS, ifstream & inputFileStudent)
{
   // Create variable to hold actual number of students
   int numOfStudents = 0;

   // Outer for loop to control which student is being stored
   for (int counter1 = 0; counter1 < STUDENTS; counter1++)
   {
      // Boolean variable to help with determining the number of actual students
      bool trueFalse = false;

      // Another counter variable
      int counter2 = 0;

      // While loop to read inputfile into the 2D array
      while (counter2 < ANSWERS && inputFileStudent >> studentAnswers[counter1][counter2])
      {
         counter2++;
         trueFalse = true;
      } // end while (counter2 < ANSWERS && inputFileStudent >> studentAnswers[counter1][counter2]) loop

      // If true: that means a student is in the file
      if (trueFalse)
         numOfStudents++;
   } // end for (int counter1 = 0; counter1 < STUDENTS; counter1++)

   return numOfStudents;
} // end function readStudentAnswers

/**************************************************************************************************************************************************************************
*Function: displayReport(char correctAnswers[], char studentAnswers[][ANSWERS], int numOfStudents)
*Descr:    This function will read in the character array of correct answers, read in the character array of student answers, and the amount of students in
*          the file. It will then create variables to determine which student got the higher and lowest percentage, and create variables to hold those percentages.
*          The function will create two arrays, an int array to hold the number missed, and a character array to hold the choice that the student choose. It will
*          then display a report each student. It will have which student it is, how many questions missed, the percentage the student obtained, which
*          reponse the student choose compared to the right one, and if the student passed or not. At the end, the report will have which student had the lowest
*          and highest percentage and what percentage was it.
*Input:    correctAswers (character array), studentAnswers (character array), numOfStudents (int)
*Return:   void
***************************************************************************************************************************************************************************/
void displayReport(char correctAnswers[], char studentAnswers[][ANSWERS], int numOfStudents)
{
   // Hold which student has the highest/lowest
   int studentMax;
   int studentMin;

   // Create variables to determine which percentage is the highest/lowest
   int maxPercentage = -1;
   int minPercentage = 110;

   // Create arrays to hold the student's wrong choice and the question number
   int incorrectQuestion[ANSWERS];
   char incorrectAnswer[ANSWERS];

   // for loop to iterate through the specific student
   for (int counter1 = 0; counter1 < numOfStudents; counter1++)
   {
      // Hold the student's percentage
      int studentPercentage;

      // Counter variables
      int numQuestionsRight = 0;
      int numQuestionsMissed = 0;

      // Begin displaying report
      cout << "Report for student " << (counter1 + 1) << ":" << endl;
      cout << "---------------------" << endl;

      // for loop to compare the student's choices with the answer key
      for (int counter2 = 0; counter2 < ANSWERS; counter2++)
      {
         // If they match increment a counter variable (indicating how many they got right)
         if (correctAnswers[counter2] == studentAnswers[counter1][counter2])
            numQuestionsRight++;

         // If they don't match
         else
         {
            // Store the number they missed & the student's choice
            incorrectQuestion[numQuestionsMissed] = counter2;
            incorrectAnswer[numQuestionsMissed] = studentAnswers[counter1][counter2];

            // Increment a counter variable
            numQuestionsMissed++;
         } // end else statement
      } // end for (int counter4 = 0; counter4 < ANSWERS; counter4++)

      // Calculate percentage & display information gathered
      studentPercentage = ((numQuestionsRight * 100) / ANSWERS);
      cout << "Missed " << (numQuestionsMissed) << " out of " << ANSWERS << " questions for " << studentPercentage << "% correct" << endl;
      cout << "Questions missed: " << endl;

      // If the student missed none then display the student missed none
      if (numQuestionsMissed == 0)
         cout << "NONE" << endl;

      // Otherwise
      else
      {
         // for loop to display the question number missed, the student's choice, and the correct choice
         for (int counter3 = 0; counter3 < numQuestionsMissed; counter3++)
         {
            cout << (incorrectQuestion[counter3] + 1) << "(" << incorrectAnswer[counter3] << "/" << correctAnswers[incorrectQuestion[counter3]] << ")";
            if (counter3 < (numQuestionsMissed - 1))
               cout << ", ";
         } // end for (int counter5 = 0; counter5 < counter3; counter5++)
         cout << endl;
      } // end else statment

      // If the percentage is higher than 70 the student passed : display message
      if (studentPercentage >= 70)
         cout << "This student passed the exam!" << endl;

      // Otherwise the student failed: display message
      else
         cout << "This student failed the exam." << endl;

      // If the student's percentage is higher than the max, then the student percentage becomes the max percentage
      // Then store which student it is
      if (studentPercentage > maxPercentage)
      {
         maxPercentage = studentPercentage;
         studentMax = counter1;
      } // end if (studentPercentage > maxPercentage)

      // If the student's percentage is lower than the min, then the student percentage becomes the min percentage
      // Then store which student it is
      if (studentPercentage < minPercentage)
      {
         minPercentage = studentPercentage;
         studentMin = counter1;
      } // end if (studentPercentage < minPercentage)
      cout << endl;
      cout << endl;
   } // end for (int counter1 = 0; counter1 < numOfStudents; counter1++)

   // Display which student had the lowest/highest percentage and with what percentage
   cout << "Student " << (studentMax + 1) << " had the best grade with " << maxPercentage << "%." << endl;
   cout << "Student " << (studentMin + 1) << " had the worst grade with " << minPercentage << "%." << endl;

} // end function displayReport

/**************************************************************************************************************************************************************************
*Function: outputReport(char correctAnswers[], char studentAnswers[][ANSWERS], int numOfStudents)
*Descr:    This function will read in the character array of correct answers, read in the character array of student answers, and the amount of students in
*          the file. It will then create variables to determine which student got the higher and lowest percentage, and create variables to hold those percentages.
*          The function will create two arrays, an int array to hold the number missed, and a character array to hold the choice that the student choose. It will
*          then output a file with a report each student. It will have which student it is, how many questions missed, the percentage the student obtained, which
*          reponse the student choose compared to the right one, and if the student passed or not. At the end, the report will have which student had the lowest
*          and highest percentage and what percentage was it.
*Input:    correctAswers (character array), studentAnswers (character array), numOfStudents (int)
*Return:   void
***************************************************************************************************************************************************************************/
void outputReport(char correctAnswers[], char studentAnswers[][ANSWERS], int numOfStudents)
{
   // Create ofstream variable
   ofstream outputFile;

   // Open an output file
   outputFile.open("ExamAnalysis.txt");

   // If it fails to open: display error message
   if (outputFile.fail())
      cout << "The output file was unable to be opened" << endl;

   // If opened sucessfully
   else
   {
      // Hold which student has the highest/lowest percentage
      int studentMax;
      int studentMin;

      // Create variables to determine which percentage is the highest/lowest
      int maxPercentage = -1;
      int minPercentage = 110;

      // Create arrays to hold the student's wrong choice and the question number
      int incorrectQuestion[ANSWERS];
      char incorrectAnswer[ANSWERS];

      // for loop to iterate through the specific student
      for (int counter1 = 0; counter1 < numOfStudents; counter1++)
      {
         // Hold the student's percentage
         int studentPercentage;

         // Counter variables
         int numQuestionsRight = 0;
         int numQuestionsMissed = 0;

         // Begin outputting the report to the file
         outputFile << "Report for student " << (counter1 + 1) << ":" << endl;
         outputFile << "---------------------" << endl;

         // for loop to compare the student's choices with the answer key
         for (int counter2 = 0; counter2 < ANSWERS; counter2++)
         {
            // If they match increment a counter variable (indicating how many they got right)
            if (correctAnswers[counter2] == studentAnswers[counter1][counter2])
               numQuestionsRight++;

            // If they don't match
            else
            {
               // Store the number they missed & the student's choice
               incorrectQuestion[numQuestionsMissed] = counter2;
               incorrectAnswer[numQuestionsMissed] = studentAnswers[counter1][counter2];

               // Increment a counter variable
               numQuestionsMissed++;

            } // end else statement

         } // end for (int counter4 = 0; counter4 < ANSWERS; counter4++)

         // Calculate percentage & output to the file information gathered
         studentPercentage = ((numQuestionsRight * 100) / ANSWERS);
         outputFile << "Missed " << (numQuestionsMissed) << " out of " << ANSWERS << " questions for " << studentPercentage << "% correct" << endl;
         outputFile << "Questions missed: " << endl;

         // If the student missed none then output to the file the student missed none
         if (numQuestionsMissed == 0)
            outputFile << "NONE" << endl;

         // Otherwise
         else
         {
            // for loop to output to the file the question number missed, the student's choice, and the correct choice
            for (int counter3 = 0; counter3 < numQuestionsMissed; counter3++)
            {
               outputFile << (incorrectQuestion[counter3] + 1) << "(" << incorrectAnswer[counter3] << "/" << correctAnswers[incorrectQuestion[counter3]] << ")";
               if (counter3 < (numQuestionsMissed - 1))
                  outputFile << ", ";

            } // end for (int counter5 = 0; counter5 < counter3; counter5++)

            outputFile << endl;

         } // end else statment

         // If the percentage is higher than 70 the student passed: output message
         if (studentPercentage >= 70)
            outputFile << "This student passed the exam!" << endl;

         // Otherwise the student failed: output message
         else
            outputFile << "This student failed the exam." << endl;

         // If the student's percentage is higher than the max, then the student percentage becomes the max percentage
         // Then store which student it is
         if (studentPercentage > maxPercentage)
         {
            maxPercentage = studentPercentage;
            studentMax = counter1;
         } // end if (studentPercentage > maxPercentage)

         // If the student's percentage is lower than the min, then the student percentage becomes the min percentage
         // Then store which student it is
         if (studentPercentage < minPercentage)
         {
            minPercentage = studentPercentage;
            studentMin = counter1;
         } // end if (studentPercentage < minPercentage)

         outputFile << endl;
         outputFile << endl;

      } // end for (int counter1 = 0; counter1 < numOfStudents; counter1++)

      // Output to the file which student had the lowest/highest percentage and with what percentage
      outputFile << "Student " << (studentMax + 1) << " had the best grade with " << maxPercentage << "%." << endl;
      outputFile << "Student " << (studentMin + 1) << " had the worst grade with " << minPercentage << "%." << endl;

      outputFile.close();

   } // end else statement 

} // end function outputReport