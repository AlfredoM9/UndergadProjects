/**********************************************************************************
                                                                                  *
Author:     Alfredo Mejia                                                         *
Course:     CS 1337.009                                                           *
Date:       2/10/19                                                               *
Assignment: HW Assignment 2                                                       *
Compiler:   Visual Studios C++ 2017                                               *
                                                                                  *
Description: This program will take input from a file. The file will contain      *
             two matrices or possibly more. The matrices will be passed to a      *
             dynamic array. Each matrix comes in pairs in order to do matrix      *
             multiplication It will check if the rows and columns are the same    *
             in order to do matrix multiplication (it's a law of matrix           *
             multiplication). If valid it will continue and calculate the product.*
             It will display the matrices mutiplied and the product. If invalid   *
             it will show an error message saying multiplication can't be done.   *
             This will be repeated until it has reached the end of the file.      *
                                                                                  *
**********************************************************************************/

#include<iostream>
#include<iomanip>
#include <string>
#include <fstream>


using namespace std;

// Function prototypes
bool obtainMatrices(ifstream &inputFile, int **&matrix1,int **&matrix2, int &rowMX1, int &rowMX2, int &colMX1, int &colMX2);
void multiplyMatrices(int **&matrix1, int **&matrix2, int rowMX1, int rowMX2, int colMX2);
int main()
{
   // Get file name
   string fileName;
   cin >> fileName;

   // Open file
   ifstream inputFile(fileName);

   // If it doesn't open, display error message
   if (inputFile.fail())
      cout << "The was unsuccessfully opened" << endl;

   // If it does open
   else
   {
      // Create variable for rows of matrix 1
      int rowMX1;

      // while it has content to read
      while (inputFile >> rowMX1)
      {
         // Create pointers to hold matrices later & create variables to hold rows & cols
         int **matrix1 = nullptr, **matrix2 = nullptr;
         int colMX1 = 0, rowMX2 = 0, colMX2 = 0;

         // Call obtain matrices and should return if true if multiplication can be performed otherwise false
         bool valid = obtainMatrices(inputFile, matrix1, matrix2, rowMX1, rowMX2, colMX1, colMX2);

         // If multpication can be performed call mutiply matrices
         if (valid)
            multiplyMatrices(matrix1, matrix2, rowMX1, rowMX2, colMX2);

         else
            cout << "Mutiplication could not be performed on the previous Matrices" << endl;

         delete[] matrix1;
         delete[] matrix2;

      } // end while loop

      cout << "The file has reached its end" << endl;
   } // end else

   system("pause");

   return 0;

} // end main

/*******************************************************************************************************
Funct: obtainMatrices
Descp: The function is going to take in an input file, two pointers to pointers, and reference
       variables to hold the rows and columns of each matrix. Because the file already passed a
       value to the number of rows for matrix 1 we start in the function by passing a value from
       the file to the number of columns of matrix1. When allocate enough memory to hold all values
       of the matrix and pass the values to the dynamic array. We then repeat it for the next matrix.
       We compare the columns of the first matrix with the rows of the second matrix. If they match
       then multiplication can be performed thus the function returns true, false otherwise.
********************************************************************************************************/

bool obtainMatrices(ifstream &inputFile, int **&matrix1, int **&matrix2, int &rowMX1, int &rowMX2, int &colMX1, int &colMX2)
{
   // Pass the number of columns to matrix 1
   inputFile >> colMX1;

   // Create enough memory to hold all values
   matrix1 = new int* [rowMX1];

   // Assign each pointer to a number of elements to serve as a 2D array
   for (int row = 0; row < rowMX1; row++)
      matrix1[row] = new int[colMX1];

   // Pass each value to the dynamic array and display it
   cout << "Matrix 1: " << rowMX1 << "X" << colMX1 << endl;
   for (int row = 0; row < rowMX1; row++)
   {
      for (int col = 0; col < colMX1; col++)
      {
         inputFile >> matrix1[row][col];
         cout << setw(6) << matrix1[row][col] << setw(6);
      } // end for (int col = 0; col < colMX1; col++)
      cout << endl;
   } // end for (int row = 0; row < rowMX1; row++)

   cout << endl;

   // Pass number of rows and columns for matrix 2
   inputFile >> rowMX2 >> colMX2;

   // Create a 2D dynamic array
   matrix2 = new int*[rowMX2];
   for (int row = 0; row < rowMX2; row++)
      matrix2[row] = new int[colMX2];

   // Pass all values to matrix 2 and display them
   cout << "Matrix 2: " << rowMX2 << "X" << colMX2 << endl;
   for (int row = 0; row < rowMX2; row++)
   {
      for (int col = 0; col < colMX2; col++)
      {
         inputFile >> matrix2[row][col];
         cout << setw(6) << matrix2[row][col] << setw(6);
      } // end for (int col = 0; col < colMX2; col++)
      cout << endl;
   } // end for (int row = 0; row < rowMX2; row++)

   cout << endl;

   // If multiplication is possible return true
   if (colMX1 == rowMX2)
      return true;
   else
      return false;
} // end obtainMatrices

/************************************************************************************************
Funct: multiplyMatrices
Descr: The function accepts the two dynamic arrays, and the number of columns and rows.
       The function will multiply the two matrices and display the result. The 
       multiplication will follow matrix multiplication meaning the dot product of 
       row of the first matrix with the column of the second matrix. The result will
       be displayed in a format that follows a matrix. It will have rows and columns.
*************************************************************************************************/
void multiplyMatrices(int **&matrix1, int **&matrix2, int rowMX1, int rowMX2, int colMX2)
{
   // Multiply the matrices and display the resulting matrix
   cout << "Resulting Matrix: " << rowMX1 << "X" << colMX2 << endl;
   for (int row = 0; row < rowMX1; row++)
   {
      int sum;
      for (int col = 0; col < colMX2; col++)
      {
         sum = 0;
         for (int count = 0; count < rowMX2; count++)
         {
            // Calculate
            sum += (matrix1[row][count] * matrix2[count][col]);
         } // end for (int count = 0; count < rowMX2; count++)

         // Display element
         cout << setw(6) << sum << setw(6);
      } // end for (int col = 0; col < colMX2; col++)
      cout << endl;
   } // end for (int row = 0; row < rowMX1; row++)

   cout << endl;
 
} // end multiplyMatrices