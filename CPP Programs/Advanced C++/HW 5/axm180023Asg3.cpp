/**********************************************************************************
                                                                                  *
Author:     Alfredo Mejia                                                         *
Course:     CS 1337.009                                                           *
Date:       2/24/19                                                               *
Assignment: HW Assignment 2                                                       *
Compiler:   Visual Studios C++ 2017                                               *
                                                                                  *
Description:                                                                      *
                                                                                  *
***********************************************************************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool openFile(string fileName, ifstream &inputFile);
int sortFile(ifstream &inputFile, double sortedArray[], const int MAX_SIZE);
void displayArray(int size, double sortedArray[]);

int main()
{
   const int MAX_SIZE = 100;
   double sortedArray[100];

   string fileName;
   ifstream inputFile;
   bool valid = openFile(fileName, inputFile);

   if (!valid)
      cout << "The program has ended." << endl;

   else
   {
      int size = 0;
      size = sortFile(inputFile, sortedArray, MAX_SIZE);
      displayArray(size, sortedArray);
   }


   system("pause");
   return 0;


}

bool openFile(string fileName, ifstream &inputFile)
{
   do
   {
      cout << "Please enter a file name to which the contents will be sorted. Or enter a single \"*\""
           << "to end the program" << endl;
      cin >> fileName;
      inputFile.open(fileName);

      if (inputFile.fail())
         cout << "An error has occured." << endl;
   } while (inputFile.fail());

   if (fileName == "*")
      return false;
   else
      return true;
}

int sortFile(ifstream &inputFile, double sortedArray[], const int MAX_SIZE)
{
   inputFile >> sortedArray[0];
   int size = 1;
   for (int count = 1; count < MAX_SIZE && inputFile >> sortedArray[count]; count++)
   {
      int count2 = 0;
      while (sortedArray[count] > sortedArray[count2])
         count2 += 1;
      int val = sortedArray[count];
      for (int count3 = 0; count < (count - count2 - 1); count3++)
         sortedArray[count - count3] = sortedArray[count - count3 - 1];
      sortedArray[count2] = val;
      size++;
   }

   return size;
/*if (sortedArray[count] < sortedArray[0])
      {
         int val = sortedArray[count];
         for (int count2 = count; count > 0; count--)
         {
            sortedArray[count2] = sortedArray[count2 - 1];
         }
         sortedArray[0] = val;
      }

      else
      {
         for (int count2 = 1; count2 < count; count2++)
         {
            int val;
            if (sortedArray[count] < sortedArray[1])
            {
               val = sortedArray[count];
               for (int count3 = count2; count3 > 0; count2--)
               {
                  sortedArray[count3] = sortedArray[count3 - 1];
               }
            }
         }
      }
      */
}

void displayArray(int size, double sortedArray[])
{
   for (int count = 0; count < size; count++)
      cout << sortedArray[count] << endl;
   return;
}