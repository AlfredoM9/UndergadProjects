// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       11/5/18
// Assignment: HW 7 Excersie 1
// Compiler:   Visual C++ 2017

/* Description: 
This program will ask the user
to input a number between 1 and 15 and will print
out a series of four pattern of asterisks with 
a height of the number inputted by the user
*/

#include <iostream>
using namespace std;

int main()
{
   int height;

   // Display prompt to enter the height
   do
   {
      cout << "Please enter an integer between 1 and 15 ";
      cin >> height;
      cout << endl;

      // If outside the range display error message
      if (height < 1 || height > 15)
         cout << "Error!: Please read the instructions carefully" << endl;

   } while (height < 1 || height >15); // end do -while loop


   // Pattern 1
   int pattern1X, pattern1Y;

   // for loop for number of lines
   for (pattern1X = height; pattern1X >= 1; pattern1X--)
   {
      // for loop for the number of asterisks
      for ( pattern1Y = 1; pattern1Y <= pattern1X ; pattern1Y++)
         cout << "*";

      cout << endl;

   } // end for (pattern1X = height; pattern1X >= 1; pattern1X--)


   cout << endl;
   cout << endl;
   cout << endl;


   // Pattern 2
   int pattern2X, pattern2Y;

   // for loop for number of lines
   for (pattern2X = 1; pattern2X <= height; pattern2X++)
   {
      // for loop for number of asterisks and spaces
      for (pattern2Y = 1; pattern2Y <= height; pattern2Y++)
      {
         if (pattern2X <= pattern2Y)
            cout << "*";

         else
            cout << " ";

      } // end for (pattern2Y = 1; pattern2Y <= height; pattern2Y++)

      cout << endl;

   } // end for (pattern2X = 1; pattern2X <= height; pattern2X++)


   cout << endl;
   cout << endl;
   cout << endl;


   // Pattern 3
   int pattern3X, pattern3Y, pattern3Z;
   
   // for loop for number of lines
   for (pattern3X = 0; pattern3X < height; pattern3X++)
   {
      // for loop for the number of spaces
      for (pattern3Y = 0; pattern3Y < (height - pattern3X - 1); pattern3Y++)
         cout << " ";

      // for loop for the number of asterisks
      for (pattern3Z = 0; pattern3Z < (pattern3X * 2 + 1); pattern3Z++)
         cout << "*";

      cout << endl;

   } // end for (pattern3X = 0; pattern3X < height; pattern3X++)


   cout << endl;
   cout << endl;
   cout << endl;


   // Pattern 4
   int pattern4X, pattern4Y, pattern4Z;

   // for loop for the first line of the pattern
   for (pattern4X = 0; pattern4X < height - 1; pattern4X++)
      cout << " ";

   cout << "*" << endl;

   // for loop for the number of lines in the body
   for (pattern4X = 1; pattern4X <= (height - 2); pattern4X++)
   {
      // for loop for the number of spaces before the first asterisk
      for (pattern4Y = 0; pattern4Y < (height - pattern4X - 1); pattern4Y++)
         cout << " ";

      cout << "*";

      // for loop for the number of spaces before the second asterisk
      for (pattern4Z = 0; pattern4Z < (2 * pattern4X - 1); pattern4Z++)
         cout << " ";

      cout << "*" << endl;

   } // end for (pattern4X = 1; pattern4X <= (height - 2); pattern4X++)

   // for loop for the last line of the pattern
   for (pattern4X = 0; pattern4X < (2* height - 1); pattern4X++)
      cout << "*";

   return 0;

} // end function main