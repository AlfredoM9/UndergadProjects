// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       11/5/18
// Assignment: HW 7 Excersie 1
// Compiler:   Visual C++ 2017

/* Description: This program will ask the user
to input a number between 1 and 15 and will print
out a series of four pattern of asterisks with
a height of the number inputted by the user
*/

#include <iostream>
using namespace std;

int main()
{
   int height, columnPattern1, rowPattern1, numberofAsterisks,
      columnPattern2, rowPattern2, numberofAsterisks2, spaces;

   do
   {
      cout << "Please enter an integer between 1 and 15 ";
      cin >> height;
      cout << endl;

      if (height < 1 || height > 15)
         cout << "Error!: Please read the instructions carefully" << endl;

   } while (height < 1 || height >15);

   rowPattern1 = height;

   for (columnPattern1 = height; columnPattern1 > 1; columnPattern1--)
   {
      for (numberofAsterisks = 1; numberofAsterisks <= rowPattern1; numberofAsterisks++)
      {
         cout << "*";

         if (numberofAsterisks == rowPattern1)
            rowPattern1 -= 1;

      }
      cout << endl;
   }
   system("pause");
   return 0;
}