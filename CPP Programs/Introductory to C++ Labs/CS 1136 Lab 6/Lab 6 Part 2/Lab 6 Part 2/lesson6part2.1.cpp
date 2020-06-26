// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       10/21/18
// Assignment: Lab 6 Part 1
// Compiler:   Visual C++ 2017

// Description: This program will convert a set of 
// temperatures from Fahrenheit to Celsius.

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   double startingValue, endingValue, incrementValue, celsiusValue;

   // Store input from the user
   cin >> startingValue >> endingValue >> incrementValue;

   // Validate user's input
   while ((startingValue > endingValue) || (incrementValue <= 0))
   {
      // If the input is invalid display error message and store reentry
      cout << "Starting temperature must be <= ending temperature and increment must be > 0.0";
      cin >> startingValue >> endingValue >> incrementValue;
   } // end while loop

   // Establish the print field to 18 and print headers
   cout << setw(18) << "Fahrenheit" << setw(18) << "Celsius" << endl;

   // Create loop to display all temperatures
   for (; startingValue <= endingValue; (startingValue += incrementValue))
   {
      // Set the decimal places to 5 digits
      cout << fixed << setprecision(5);

      // Calculate celsius
      celsiusValue = (startingValue - 32) / 1.8;

      // Display temperatures
      cout << setw(18) << startingValue << setw(18) << celsiusValue << endl;
   }

   return 0;
} // end function main