// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       11/5/18
// Assignment: HW 7 Excersie 2
// Compiler:   Visual C++ 2017

/***************************************************************************
Description: This program will read in numbers from a file and calculate   *
             a series of tasks. It will count how many numbers are in the  *
             file. It will find the sum of the numbers in the file. It     *
             calculate the average of the numbers in the file. It will     *
             find the largest number in the file. It will find the smallest*
             number in the file. And it will find the second largest and   *
             second smallest number in the file. (All numbers are in the   *
             range of 0 to 1000)                                           *
****************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
   ifstream inputFile;

   // Open file
   inputFile.open("random.txt");

   // If opened successfully
   if (inputFile)
   {
      int numbers, totalNumbers, sumOfNumbers, largestNumber,
         smallestNumber, secondSmallestNum, secondLargestNum;
      double averageOfNumbers;

      // Initialize variables
      totalNumbers = 0;
      sumOfNumbers = 0;
      smallestNumber = 1100;
      secondSmallestNum = 1100;
      largestNumber = -1;
      secondLargestNum = -1;

      // Read all numbers and check for the end of the file
      while (inputFile >> numbers)
      {
         // Each number is added to the sum
         sumOfNumbers += numbers;

         // Count how many numbers are in the file
         totalNumbers++;

         // Check for the smallest number and second smallest
         if (numbers < smallestNumber)
         {
            secondSmallestNum = smallestNumber;
            smallestNumber = numbers;
         }

         // else check for the second smallest number
         else if (numbers > smallestNumber && numbers < secondSmallestNum)
            secondSmallestNum = numbers;

         // Check for the largest number and second largest
         if (numbers > largestNumber)
         {
            secondLargestNum = largestNumber;
            largestNumber = numbers;
         }

         // else check for the second largest number
         else if (numbers < largestNumber && numbers > secondLargestNum)
            secondLargestNum = numbers;


      } // end while (inputFile >> numbers)

      // Calculate average
      averageOfNumbers = sumOfNumbers / totalNumbers;

      // Display a report with information gathered
      cout << "Number of numbers: " << setw(15) << totalNumbers << endl;
      cout << "Sum of numbers:    " << setw(15) << sumOfNumbers << endl;
      cout << "Average of numbers:" << setw(15) << fixed << setprecision(1)
           << averageOfNumbers << endl;
      cout << "Largest number:    " << setw(15) << largestNumber << endl;
      cout << "Smallest number:   " << setw(15) << smallestNumber << endl;
      cout << "Second largest number: " << setw(11) << secondLargestNum << endl;
      cout << "Second smallest number: " << setw(10) << secondSmallestNum << endl;

      // Close file
      inputFile.close();

   } // end if (inputFile)

   // If file not opened: display error message
   else
      cout << "File \"random.txt\" could not be opened";

   return 0;

} // end function main