// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       12/9/18
// Assignment: Lab 10 Part 2
// Compiler:   Visual C++ 2017

/****************************************************************************************************************************************
Description: This program will read the contents of a file into an array and calculate various values based on the
             contents of the file. It will first read the file, if opened successfully, all data will be transferred 
             into an array. Then another function will calculate the average of all the elements of the array. Afterward
             another function will calculate the column average and the smallest value in each row. All of these data
             will be stored in two other arrays. Finally the last function will display the information gathered. It will
             display how many rows there are, how many columns, the average of all elements, the average of each column, and 
             the average of each row.
*****************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Const global variable: helps with 2D arrays & functions
const int MAX_COLUMNS = 5;

// Function Prototypes
int readFile(double values[][MAX_COLUMNS], int maxRows, string inputFilename);
double average(double values[][MAX_COLUMNS], int numberRows);
double columnAverage(double values[][MAX_COLUMNS], int column, int numberRows);
double getSmallestValue(double values[][MAX_COLUMNS], int numberRows, int column);
void displayResults(double columnAverage[], double smallestValues[], double average, const int MAX_COLUMNS, int numRows);

// main function
int main()
{
   // Create string and store file name
   string fileName;
   cin >> fileName;

   // Declare a const for rows
   const int MAX_ROWS = 20;

   // Create an array with two const created
   double values[MAX_ROWS][MAX_COLUMNS];

   // Variable for the actual number of rows in the file
   int numRows;

   // Call readFile and it will return the number of rows in the file, unless if the file didn't open successfully or there is no complete rows
   numRows = readFile(values, MAX_ROWS, fileName);

   // If returns -1: file failed to open: display message
   if (numRows == -1)
      cout << "File \"" << fileName << "\" could not be opened" << endl;

   // If returns 0: there is no complete rows : Display message
   else if (numRows == 0)
      cout << "The input file \"" << fileName << "\" did not contain any data" << endl;

   // Otherwise the file opened successfully and has complete data
   else
   {
      // Create arrays to hold the average for each column and the smallest value for each row
      double averageColumn[MAX_COLUMNS];
      double smallestValue[MAX_ROWS];

      // Create variable to hold the average of the entire array
      double arrayAverage;

      // Call average function: the return is the average of the array and store it
      arrayAverage = average(values, numRows);

      // for loop to go through each column and calculate the average by calling the columnAverage function
      for (int count = 0; count < MAX_COLUMNS; count++)
         averageColumn[count] = columnAverage(values, count, numRows);

      // for loop to go through each row and calculate the smallest value by calling the getSmallestValue function
      for (int count = 0; count < numRows; count++)
         smallestValue[count] = getSmallestValue(values, count, MAX_COLUMNS);

      // Display results
      displayResults(averageColumn, smallestValue, arrayAverage, MAX_COLUMNS, numRows);
   } // end else statement

   return 0;
} // end function main

/****************************************************************************************************************
Function: readFile(double values[][MAX_COLUMNS], int maxRows, string inputFilename)
Descr:    This function will read a 2D array, a size declarator, and a string for the file name.
          The function will create an ifstream variable, open a file using the string as a file name.
          The data in the file will be read into a 2D array and it will count the actual rows in the 
          file. It will then close the file and return the number of the actual rows.
Input:    values (2D double array), maxRows (int), inputFilename (string)
Return:   A int that holds the amount of rows in the file
******************************************************************************************************************/
int readFile(double values[][MAX_COLUMNS], int maxRows, string inputFilename)
{
   // Create ifstream variable
   ifstream inputFile;

   // Open file
   inputFile.open(inputFilename);

   // If it fails to open return a -1
   if (inputFile.fail())
      return -1;

   // If opened successfully
   else
   {
      // Create variable to hold number of rows
      int numRows = 0;

      // for loop to control the number of rows
      for (int counter = 0; counter < maxRows; counter++)
      {
         // boolean variable to help with calculate the number of rows
         bool trueFalse = false;

         int counter2 = 0;

         // while loop to read data into a 2D array
         while (counter2 < MAX_COLUMNS && inputFile >> values[counter][counter2])
         {
            counter2++;

            // If it reads then it counts as one row
            trueFalse = true;
         } // end  while (counter2 < MAX_COLUMNS && inputFile >> values[counter][counter2])

         // If it is true: increment numRows
         if (trueFalse)
            numRows++;
      } // end for (int counter = 0; counter < maxRows; counter++)

      // Close fail
      inputFile.close();

      // If numRows is less than 1 return 0
      if (numRows < 1)
         return 0;

      // else return the number of rows
      else
         return numRows;
   } // end else statement
} // end function readFile

/*******************************************************************************************************
Function: average(double values[][MAX_COLUMNS], int numberRows)
Descr:    This function will read in a double array, and a size declarator for the rows.
          The function will add the values of the array into the variable and divide the 
          total with the number of elements to get the average. It will then return the average.
Input:    values(2D double array) numberRows(int)
Return:   A double that is the average
*********************************************************************************************************/
double average(double values[][MAX_COLUMNS], int numberRows)
{
   // Create variable to hold average
   double average = 0;

   // for loop and inner for loop to add each element to average
   for (int count = 0; count < numberRows; count++)
   {
      for (int count2 = 0; count2 < MAX_COLUMNS; count2++)
         average += values[count][count2];
   } // end for (int count = 0; count < numberRows; count++)

   // Once all elements are added divide by total number elements to get the average of the array
   average /= (numberRows * MAX_COLUMNS);

   return average;
} // end function average

/*****************************************************************************************************
Function: columnAverage(double values[][MAX_COLUMNS], int column, int numberRows)
Descr: This function will read a 2D array, the number of column that it is calculating
       and number of rows both are which are integers. It will read all the total 
       values of the array in that specific column. It will then add all the values
       and divide by the total number of rows to get the average for that specific column.
       It will then return the average for that column.
Input: value(2D double array) column (int), numberRows (int)
Return: The average of a specific column
*******************************************************************************************************/
double columnAverage(double values[][MAX_COLUMNS], int column, int numberRows)
{
   // Create variable to hold average for a specific column
   double average = 0;

   // for loop to add all the values of the array of a specific column
   for (int count = 0; count < numberRows; count++)
      average += values[count][column];

   // Divide with the number of rows to get average
   average /= numberRows;

   // Return the average of the specific column
   return average;
} // end columnAverage

/*********************************************************************************************************************
Function: getSmallestValue(double values[][MAX_COLUMNS], int numberRows, int column)
Descr:    This function will read in a 2D array, the number of a specific row, and the number of
          columns. It will then read all the values in a specific row and calculate the smallest value in
          that specific row. Once the smallest value is found it will return the smallest value.
Input:    values (2D double array), numberRows (int), column(int)
Return:   A double that holds the smallest value
***********************************************************************************************************************/
double getSmallestValue(double values[][MAX_COLUMNS], int numberRows, int column)
{
   // Create a variable with a high value in order to calculate the smallest value
   double smallestValue = 10000.0;

   // for loop to go through each value in a specific row
   for (int count = 0; count < column; count++)
   {
      // If the value found is smaller than the variable initialized : the value is assigned to variable
      if (values[numberRows][count] < smallestValue)
         smallestValue = values[numberRows][count];
   } // end for (int count = 0; count < column; count++)

   // return the smallest value found
   return smallestValue;
} // end function getSmallestValue

/****************************************************************************************************************************************************
Function: displayResults(double columnAverage[], double smallestValues[], double average, const int MAX_COLUMNS, int numRows)
Descr:    This function will read in a 1D double array holding the average for each column, it will read another 1D array holding
          the smallest value for each row, it will read in the average of all array elements, and it will read in the size declarators
          for each array being the number of columns and rows. It will then display in a fixed format the number of rows, the number of 
          columns, the average, and it will use  for loops to display the column average for each column and the smallest value for each  row.
Input:    columnAverage(double array), smallestValues (double array), average (double), MAX_COLUMNS (const int), numRows(int)
Return:   void
******************************************************************************************************************************************************/
void displayResults(double columnAverage[], double smallestValues[], double average, const int MAX_COLUMNS, int numRows)
{
   // Display in a fixed format the number of rows, columns, and the average of all elements in the array gathered from the file
   cout << fixed << setprecision(2);
   cout << "Processing " << numRows << " rows, and " << MAX_COLUMNS << " columns" << endl;
   cout << "Average for all values is " << average << endl;

   // for loop to display each average for each column
   for (int count = 0; count < MAX_COLUMNS; count++)
      cout << "Average for column " << count << " is " << columnAverage[count] << endl;

   // for loop to display each smallest value for each row
   for (int count = 0; count < numRows; count++)
      cout << "Smallest value for row " << count << " is " << smallestValues[count] << endl;
} // end function displayResults