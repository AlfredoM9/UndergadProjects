// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       12/1/18
// Assignment: Lab 11 Part 1
// Compiler:   Visual C++ 2017

/******************************************************************************
Description: // Never finished error in the diagonal
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_SIZE = 21;

bool validateSquare(const int square[MAX_SIZE][MAX_SIZE], int size);
int readSquare(int square[MAX_SIZE][MAX_SIZE], string inputFileName);
void displayValues(int square[MAX_SIZE][MAX_SIZE], int dimensions);

int main()
{
   string fileName;
   cin >> fileName;

   int values[MAX_SIZE][MAX_SIZE];
   int dimensions;

   dimensions = readSquare(values, fileName);

   if (dimensions == 0)
      cout << "File \"" << fileName << "\" could not be opened" << endl;

   else
   {
      bool valid;
      displayValues(values, dimensions);
      valid = validateSquare(values, dimensions); 

      if (valid)
         cout << "Valid magic square" << endl;
      else
         cout << "Invalid magic square" << endl;
   }
   system("pause");

   return 0;

}

int readSquare(int square[MAX_SIZE][MAX_SIZE], string inputFileName)
{
   ifstream inputFile;

   inputFile.open(inputFileName);

   if (inputFile.fail())
      return 0;
   else
   {
      int dimensions;
      inputFile >> dimensions;

      for (int count = 0; count < dimensions; count++)
      {
         int count2 = 0;
         while (count2 < dimensions && inputFile >> square[count][count2])
            count2++;
      }

      inputFile.close();

      return dimensions;
   }
}

void displayValues(int square[MAX_SIZE][MAX_SIZE], int dimensions)
{
   cout << "Magic square" << endl;
   for (int count = 0; count < dimensions; count++)
   {
      for (int count2 = 0; count2 < dimensions; count2++)
         cout << square[count][count2] << " ";
      cout << endl;
   }
}

bool validateSquare(const int square[MAX_SIZE][MAX_SIZE], int size)
{
   int column = 0, row;
   bool valid;
   for (int count = 0; count < size; count++)
   {
      int column2 = 0;
      valid = false;
      for (int count2 = 0; count2 < size; count2++)
      {
         column2 += square[count][count2];
      }

      if (count == 0)
         column = column2;

      if (column == column2)
         valid = true;
   }

   if (valid)
   {
      for (int count = 0; count < size; count++)
      {
         int row2 = 0;
         valid = false;
         for (int count2 = 0; count2 < size; count2++)
         {
            row2 += square[count2][count];
         }

         if (count == 0)
            row = row2;

         if (row == row2)
            valid = true;
      }

      if (valid)
      {
         int row2 = 0;
         for (int count = 0; count < size; count++)
            row2 += square[count][count];
         if (row2 == row)
           
            return valid = true;
         else
            return valid = false;
      }

      else
         return valid;
   }

   else
      return valid;
}