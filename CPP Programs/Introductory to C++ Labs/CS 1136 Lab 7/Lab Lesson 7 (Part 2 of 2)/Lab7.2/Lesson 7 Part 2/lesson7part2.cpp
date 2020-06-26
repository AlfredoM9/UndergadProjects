// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       11/4/18
// Assignment: Lab 7 Part 2
// Compiler:   Visual C++ 2017

/****************************************************************
Description: This program will read numbers from                *
a file with the name given by the user. The program             *
will then determine how many numbers are in the file,           *
determine the amount of numbers that are valid numbers          *
(between 0 and 110), and determine the amount of invalid        *
numbers that are not in that range. It will then calculate      *
the average of the VALID numbers.                               *
*****************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
   // Store file name
   string fileName;
   cin >> fileName;

   ifstream inputFile;

   // Open file given by the user
   inputFile.open(fileName);

   // If the file opens successfully
   if (inputFile)
   {
      double number, average = 0;
      int totalNumbers = 0, totalInvalidNums = 0,
         totalValidNums = 0;

      ofstream outputFile;

      // Open a file to write the invalid numbers into it
      outputFile.open("invalid-numbers.txt");

      // Read all the data in the file
      while (inputFile >> number)
      {
         // If number being read is valid
         if (number >= 0 && number <= 110)
         {
            // Add it to the average
            average += number;

            // Count the times a valid number is read
            totalValidNums++;

         } // end if (number >= 0 && number <= 110)

         // If the number is not valid
         else
         {
            // Set the numbers to 4 decimal places to the right and write the number to file created
            outputFile << fixed << setprecision(4) << number << endl;

            // Count the times a invalid number is read
            totalInvalidNums++;

         } // end else for invalid numbers

         // Count the times ALL numbers are read
         totalNumbers++;

      } // end while (inputFile >> number)

      // Display the file name, the total amount of numbers read, total invalid and valid numbers
      cout << "Reading from file \"" << fileName << "\"" << endl;
      cout << "Total values: " << totalNumbers << endl;
      cout << "Invalid values: " << totalInvalidNums << endl;
      cout << "Valid values: " << totalValidNums << endl;

      // If all numbers are invalid display error message
      if (totalValidNums == 0)
         cout << "An average cannot be calculated" << endl;

      // If there is some valid numbers: calculate average
      else
      {
         // Calculate average of valid numbers & display value
         average /= totalValidNums;
         cout << "Average of valid values: " << fixed << setprecision(3) << average << endl;

      } // end else if total valid nums is NOT equal to zero

      // Close both files opened and created
      inputFile.close();
      outputFile.close();

   } // end if (inputFile)

   // If the file given by the user isn't opened display error message
   else
      cout << "File \"" << fileName << "\" could not be opened" << endl;

   return 0;

} // end function main