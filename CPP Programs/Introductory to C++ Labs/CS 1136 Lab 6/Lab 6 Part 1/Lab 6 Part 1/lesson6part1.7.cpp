// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       10/14/18
// Assignment: Lab 6 Part 1
// Compiler:   Visual C++ 2017

// Description: This program will display the ASCII character within
// the lower bound and upper bound inserted by the user but the user must
// insert a value between the ASCII code 32 through 126.

#include <iostream>

using namespace std;

int main()
{
   unsigned int lowerBound, upperBound, counter;
   unsigned char lowerASCIIcode;

   // Counter will hold the number of iterations of the for loop
   counter = 0;

   // Display the prompt for upper and lower bound and store it
   cout << "Enter lower and upper values";
   cin >> lowerBound >> upperBound;

   // Validate user's input
   while (lowerBound < 32 || upperBound > 126 || lowerBound > upperBound)
   {
      // If input is invalid display error message and request for the input again
      cout << "Values must be in range 32 to 126 inclusive" << endl;
      cout << "Enter lower and upper values";
      cin >> lowerBound >> upperBound;
      cout << endl;
   } // end while loop

   cout << endl;

   // Display a header for the information displayed
   cout << "Characters for ASCII values between " << lowerBound << " and ";
   cout << upperBound << endl;

   cout << "----+----+----+-" << endl;

   // Display the ASCII character between the given bounds
   for (lowerASCIIcode = lowerBound; lowerASCIIcode <= upperBound; lowerASCIIcode++)
   {
      cout << lowerASCIIcode;
      counter++;

      // For each time the loop iterates 16 times go to the next line and reset the counter
      while (counter == 16)
      {
         cout << endl;
         counter = 0;
      } // end while (counter == 16) loop

   } // end for loop

   if (counter == 0)
      cout << "----+----+----+-" << endl;

   else
      cout << endl;
      cout << "----+----+----+-" << endl;

   return 0;
} // end function main