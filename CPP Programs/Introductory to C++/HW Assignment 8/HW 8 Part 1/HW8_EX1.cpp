// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       11/18/18
// Assignment: HW 8 Excersie 1
// Compiler:   Visual C++ 2017

/***********************************************************************
Description: This program will output a set of prime numbers           *
             depending on the number inputted by the user between      *
             1 and 100 that will determine the amount of prime         *
             numbers shown. In addition those prime numbers will be    *
             printed to an output file named "PrimeOut.txt".           *
                                                                       *
************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Function Prototype
bool isPrime(int number);

// main function
int main()
{
   // Varibles
   int number;
   bool primeOrNot;
   ofstream outputFile;

   // Open file
   outputFile.open("PrimeOut.txt");

   // If failed to open display error message
   if (outputFile.fail())
      cout << "File \"PrimeOut.txt\" was unsuccessful in opening" << endl;

   // If opened successfully
   else
   {
      // Variables for loops
      int counter1, counter2 = 0;

      // Display prompt for number: store it and validate input
      do
      {
         cout << "Please enter an integer between 1 and 100" << endl;
         cin >> number;
            if (number < 1 || number > 100)
               cout << "Error! Please read instructions carefully" << endl;
      } while (number < 1 || number > 100); // end do while loop

      // Loop to check every number between 1 and the variable called number if it is a prime number
      for (counter1 = 1; counter2 < number; counter1++)
      {
         // Call isPrime function to determine if counter1 is prime (returns a bool variable)
         primeOrNot = isPrime(counter1);

         // If true (if prime)
         if (primeOrNot)
         {
            // Write the number to the file and console in a fixed format
            outputFile << setw(5) << counter1;
            cout << setw(5) << counter1;

            // Increment counter2 (if prime)
            counter2++;

            // If counter2 arrives to a tenth number
            if (counter2 % 10 == 0)
            {
               // Write a newline on the file and console
               outputFile << endl;
               cout << endl;

            } // end if (counter2 % 10 == 0)

         } // end if (primeOrNot)

      } // end for (counter1 = 1; counter2 < number; counter1++)

   } // end else (if opened successfully)

   return 0;

} // end function main

// isPrime: This function will determine the number passed by value if the number is
// prime or not. If the number is prime it will return a true, if isn't it will return
// a false.
bool isPrime(int number)
{
   // Variables
   bool trueOrFalse;
   int count1, count2 = 0;

   // Loop to determine how many factors each number has. A prime number should only have two.
   for (count1 = 1; count1 <= number; count1++)
   {
      // If a factor is found increment count2
      if (number % count1 == 0)
         count2++;

   } // end for (count1 = 1; count1 <= number; count1++)

   // If only two factors found then it is a prime number
   if (count2 == 2)
      trueOrFalse = true;

   // Otherwise it is not
   else
      trueOrFalse = false;

   // Return true or false for that number (which was passed by value)
   return trueOrFalse;

} // end isPrime function