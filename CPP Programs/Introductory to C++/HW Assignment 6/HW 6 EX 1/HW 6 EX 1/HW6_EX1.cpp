// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       10/28/18
// Assignment: HW 6 Excersie 1
// Compiler:   Visual C++ 2017

/* Description: This program will complete 5 tasks. It will print out the
even integers between 2 and 100. It will print out the integers that are multiples 
of 3 from 99 down to 3. It will print out integers between 2 and 1,048,576 (2^20) that 
are integer powers of 2. It will print out integers between 1,048,576 down to 2 that 
are integer powers of 2. Finally the last task will be counting the total amount of iritations
done by the entire program and use that number to find the integers between the total amount down
to 0 and print out the odd numbers.
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   // Initialize all counter variables for all tasks
   unsigned int countA = 0, countB = 0, countC = 0, countD = 0,
                countE = 0;
   
   // Part A

   // Initialize starting value & print header
   unsigned int numberA = 2;
   cout << "Part A" << endl;

   // While loop to print even integers between 2 & 100
   while (numberA <= 100)
   {
      cout << setw(5) << numberA;
      numberA += 2;
      countA++;

      // Every 10th number print on new line
      if (countA % 10 == 0)
         cout << endl;

   } // end while (numberA <= 100)
   cout << endl;

   // Print the amount of numbers printed
   cout << "Number of numbers = " << countA << endl;

   cout << endl;
   cout << endl;
   cout << endl;

   // Part B

   // Initialize starting value & print header
   unsigned int numberB = 99;
   cout << "Part B" << endl;

   // do-while loop to print integers that are multiples of 3 from 99 to 3
   do
   {
      cout << setw(5) << numberB;
      numberB -= 3;
      countB++;

      // Every 10th number print new line
      if (countB % 10 == 0)
         cout << endl;

   } while (numberB >= 3);
   cout << endl;

   // Print the amount of numbers printed
   cout << "Number of numbers = " << countB << endl;

   cout << endl;
   cout << endl;
   cout << endl;

   // Part C

   // Initialize starting value & print header
   unsigned int numberC;
   cout << "Part C" << endl;

   // for loop to print integers that are powers of 2 from 2 to 1,048,576
   for (numberC = 2; numberC <= 1048576; numberC *= 2)
   {
      cout << setw(10) << numberC;
      countC++;

      // Every 5th number print new line
      if (countC % 5 == 0)
         cout << endl;

   }  // end for (numberC = 2; numberC <= 1048576; numberC *= 2)
   cout << endl;

   // Print the amount of numbers printed
   cout << "Number of numbers = " << countC << endl;

   cout << endl;
   cout << endl;
   cout << endl;

   // Part D

   // Initialize starting value & print header
   unsigned int numberD;
   cout << "Part D" << endl;

   // for loop to print integers from 1,048,576 to 2 that are powers of 2
   for (numberD = 1048576; numberD >= 2; numberD /= 2)
   {
      cout << setw(10) << numberD;
      countD++;

      // Every 5th number print new line
      if (countD % 5 == 0)
         cout << endl;
   }
   cout << endl;

   // Print the amount of numbers printed
   cout << "Number of numbers = " << countD << endl;

   cout << endl;
   cout << endl;
   cout << endl;

   // Part E

   // Initialize starting value & print header
   int numberE = countA + countB + countC + countD;
   cout << "Part E" << endl;

   // for loop to print the odd numbers between the total to 0
   for (; numberE >= 0; numberE -= 2)
   {
      cout << setw(5) << numberE;
      countE++;

      // Every 10th number print new line
      if (countE % 10 == 0)
         cout << endl;

   } // end for (; numberE >= 0; numberE -= 2)
   cout << endl;

   // Print the amount of numbers printed
   cout << "Number of numbers = " << countE << endl;

   return 0;

} // end function main