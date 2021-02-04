// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       12/8/18
// Assignment: HW 9 Excersie 1
// Compiler:   Visual C++ 2017

/*********************************************************************************************************************************
Description: This program will implement a linear search algorithm that scans a value                                            *
             through a data set looking for the value that matches. It will start at the beginning of the array                  *
             to the very end. If there is a match it will return the index(es) that match for the data set and if it             *
             doesn't match it will return a -1. Once that value is fully scanned from the data set it will then scan another     *
             value and so on until there is no more values to scan. It will then display the value it was scanning and,          *
             if any, the index(es) that were found to match. The data set and the values will be gathered from files.            *
                                                                                                                                 *
**********************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Function Prototypes
int readLSSfile(int LSSarray[], const int LSS_SIZE, ifstream & inputFileLSS);
int readLSTfile(int LSTarray[], const int LST_SIZE, ifstream & inputFileLST);
int searchList(int stdList[], int numElems, int value, int index[]);
void displayResults(int LSSarray[], int LSTarray[], int LSSsize, int LSTsize);

// main function
int main()
{
   // Declar const variables for array's size
   const int LSS_SIZE = 100, LST_SIZE = 50;

   // Create two ifstream variables for two files
   ifstream inputFileLSS, inputFileLST;

   // Open both files
   inputFileLSS.open("LSStandard.txt");
   inputFileLST.open("LSTest.txt");

   // If one of them fails to be opened: display error message
   if (inputFileLSS.fail() || inputFileLST.fail())
      cout << "One or more of the files was unable to be opened" << endl;

   // If the files opened successfully
   else
   {
      // Create two arrays to hold data from both files
      int LSSarray[LSS_SIZE];
      int LSTarray[LST_SIZE];

      // Create variables to hold the actual amount of data each files has
      int LSSsize, LSTsize;

      // Call readLSSfile function in which it will pass the data from the file into an array
      // It will return the actual amount of data and store in LSSsize
      LSSsize = readLSSfile(LSSarray, LSS_SIZE, inputFileLSS);

      // Call readLSTfile function in which it will pass the data from the file into an array
      // It will return the actual amount of data and store in LSTsize
      LSTsize = readLSTfile(LSTarray, LST_SIZE, inputFileLST);

      // Close files
      inputFileLSS.close();
      inputFileLST.close();

      // Call displayResults to display the results gathered
      displayResults(LSSarray, LSTarray, LSSsize, LSTsize);
   } // end else statement

   system("pause");
   return 0;

} // end function main

/***********************************************************************************************************************************
* Function: readLSSfile(int LSSarray[], const int LSS_SIZE, ifstream & inputFileLSS)
* Descr:    This function will read in the file from LSS, read in the array for LSS, and read in the size declared for LSS.
*           It will then use a while loop to read from the file into the LSS array. The loop will check for the file's end
*           and it will check for the array's boundaries. Then after all data has been stored in the array, it will use the count
*           variable to determine how many values were stored. It will then return the count value.
* Input:    LSSarray (an array of ints), LSS_SIZE (const int), inputFIleLSS (an inputfile)
* Return:   An int that will determine the exact number of values passed into the array
************************************************************************************************************************************/
int readLSSfile(int LSSarray[], const int LSS_SIZE, ifstream & inputFileLSS)
{
   // Create a counter variable
   int count = 0;

   // Use while loop to read from a file into an array
   while (count < LSS_SIZE && inputFileLSS >> LSSarray[count])
      count++;

   // Return the number of values passed
   return count;

} // end function readLSSfile

/************************************************************************************************************************************
*Function: readLSTfile(int LSTarray[], const int LST_SIZE, ifstream & inputFileLST)
*Descr:    This function will read in the file from LST, read in the array for LST, and read in the size declared for LST.
*          It will then use a while loop to read from the file into the LST array. The loop will check for the file's end
*          and it will check for the array's boundaries. Then after all data has been stored in the array, it will use the count
*          variable to determine how many values were stored. It will then return the count value.
* Input:   LSTarray (an array of ints), LST_SIZE (const int), inputFIleLST (an inputfile)
* Return:  An int that will determine the exact number of values passed into the array
*************************************************************************************************************************************/
int readLSTfile(int LSTarray[], const int LST_SIZE, ifstream & inputFileLST)
{
   // Create counter variable
   int count = 0;

   // Use while loop to read from a file into an array
   while (count < LST_SIZE && inputFileLST >> LSTarray[count])
      count++;

   // Return the number of values passed

   return count;
} // end function readLSTfile

/*********************************************************************************************************************************************************
*Function: displayResults(int LSSarray[], int LSTarray[], int LSSsize, int LSTsize)
*Descr:    This function will accept two arrays that were created that hold the data from the files. It will also accept the
          actual sizes (ints) of both arrays. It will then create another array of ints in order to hold multiple indexes if the value
          matches. Afterwards, it will use a for loop to pass the value being scanned to the function searchList in order to determine
          if the value passed matches in the data set. The function will return it a -1 or the number of times it matched. It will use this
          to display a report. The return will be stored into a variable and if the return is a -1 the value is not in the data set scanned.
          However if it returns the number of times it matched (other than negative one) it will use that to create a test expression in a for loop
          displaying the indexes stored in the array created initally and passed into the searchList function. It will then repeat the process
          with another value to match until there is no more values to match.
*Input:   LSSarray (an array of ints), LSTarray (an array of ints), LSSsize (int), LSTsize(int)
*Return:  void
*********************************************************************************************************************************************************/
void displayResults(int LSSarray[], int LSTarray[], int LSSsize, int LSTsize)
{
   // Create an array to hold multiple indexes
   const int INDEX_SIZE = 25;
   int indexArray[INDEX_SIZE];

   // Create a variable to hold the return value
   int returnValue;

   // for loop to scan one value into a data set
   for (int counter1 = 0; counter1 < LSTsize; counter1++)
   {
      // Begin displaying report
      cout << "Number " << setw(2) << left << (counter1 + 1) << " (" << setw(3) << right << LSTarray[counter1] << ")";

      // Call searchList, pass the value scanning, the array to determine the data set, and the indexArray to store indexes
      returnValue = searchList(LSSarray, LSSsize, LSTarray[counter1], indexArray);

      // If the return is -1: display not in file message
      if (returnValue == -1)
         cout << " was not in the file." << endl;

      // If returns other than -1
      else
      {
         // Diplay "it was located" message
         cout << " was located at index ";

         // For loop to display all the indexes that match the value
         for (int counter2 = 0; counter2 < returnValue; counter2++)
         {
            cout << indexArray[counter2];
            if (counter2 < (returnValue - 1))
               cout << ", ";
         } // end for (int counter2 = 0; counter2 < returnValue; counter2++)
         cout << ".";
         cout << endl;
      } // end else statement

   } // end for (int counter1 = 0; counter1 < LSTsize; counter1++)

} // end function displayResults

/*******************************************************************************************************************************************************
*Function: searchList(int stdList[], int numElems, int value, int index[])
*Descr:    This function will read in an array that holds the data set that will be scanned through. It will read in the size
*          of the array of the data set. It will accept the value that is going to be scanned through the data set. And it will read
*          in an array to input the indexes of the values that match with the value being scanned. It will first use a for loop to loop
*          through each value in the data set and if any of the values matches with the value being scanned the index of the data set will
*          be stored in the index array and a counter variable for be incremented. Once it finishes if the counter varaible was incremented it
*          will return the counter variable which will help determine how many values are stored in the index array and help use a for loop to
*          display the values of the index array in another function. However if the counter variable wasn't incremented it will return a negative one.
*Input:   stdList (an array of ints), numElems (int), value (int), index (an array of ints)
*Return:  A integer that is either the number of times the value matched or a negative one meaning it never matched.
********************************************************************************************************************************************************/
int searchList(int stdList[], int numElems, int value, int index[])
{
   // Create counter variables
   int counter1, counter2 = 0;

   //For loop to iterate through each value in the data set
   for (counter1 = 0; counter1 < numElems; counter1++)
   {
      // If the values match
      if (stdList[counter1] == value)
      {
         // Store index
         index[counter2] = counter1;

         //Increment counter2
         counter2++;

      } // end if (stdList[counter1] == value) statement

   } // end for (counter1 = 0; counter1 < numElems; counter1++)

   // If it matched once: return the times it matched
   if (counter2 > 0)
      return counter2;

   //Otherwise return -1
   else
      return -1;

} // end function searchList

