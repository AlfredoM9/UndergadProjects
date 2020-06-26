/**********************************************************************************
                                                                                  *
Author:     Alfredo Mejia                                                         *
Course:     CS 1337.009                                                           *
Date:       3/1/19                                                               *
Assignment: HW Assignment 2                                                       *
Compiler:   Visual Studios C++ 2017                                               *
                                                                                  *
Description: This program will sort a file using the insertion sort algorithm.    *
             It will first create an array of 200 doubles, it will then ask the   *
             user for a file name. If the user enters a single asterisk then the  *
             program will end. Otherwise it will ask for a valid file name until  *
             it obtains one it will open the file. It will then sort the file into*
             the array using the insertion sort algorithm. It takes in the first  *
             value and then the second compare them and switch them if needed. It *
             will take the third compare it with the first and if it less than it,*
             places it in the first otherwise it goes on to compare the elements  *
             in between until it reaches its approiate position. Then it compares *
             the fourth to the first and repeat. Then it repeats until no more is *
             needed to be compared. It will finally display the sorted array and  *
             ask for another file name.                                           *
                                                                                  *
***********************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Function Prototypes
bool openFile(ifstream &inputFile);
int sortFile(ifstream &inputFile, double sortedArray[], const int MAX_SIZE);
void displayArray(int size, double sortedArray[]);

int main()
{
   // Create array
   const int MAX_SIZE = 200;
   double sortedArray[MAX_SIZE];

   bool valid;

   do
   {
      // Create file object
      ifstream inputFile;

      // Call open file to open the file
      valid = openFile(inputFile);

      // If a valid file name is entered
      if (valid)
      {
         // Sort the file and display sorted contents
         int size = sortFile(inputFile, sortedArray, MAX_SIZE);
         displayArray(size, sortedArray);

         // Close file
         inputFile.close();

      } // end if (valid)

      // Else, the user enter a asterisk to end program
      else
         cout << "The program has ended" << endl;

   } while (valid); // end do-while

   system("pause");

   return 0;

} // end main

/************************************************************************************************
Func: openFile
Desc: The function will accept a file object. It will read into a string, check if the user
      entered an asterisk. If so it will immediately return a false. Otherwise it will try
      to open the file, if it fails a message will appear and will ask the user to try again.
      Until a valid name is entered the function will return a true.
*************************************************************************************************/
bool openFile(ifstream &inputFile)
{
   // Create string object
   string fileName;
   do
   {
      // Display prompt and store the input
      cout << "Please enter a file name to which the contents will be sorted. Or enter a single \"*\" "
           << "to end the program" << endl;
      cin >> fileName;

      // If a single asterisk is entered return false
      if (fileName == "*")
         return false;

      // Open file
      inputFile.open(fileName);

      // If invalid name display error message
      if (inputFile.fail())
         cout << "An error has occured" << endl;


   } while (inputFile.fail()); // end do while loop

   return true;
} // end openFile

/**********************************************************************************************
Func: sortFile
Decr: The function will use the insertion sort algorithm to sort the contents of the 
      file into the array. So it accepts the file, the array, and the max size of the array
      It gets the first value, then the second and compares them.
      If switching is needed then it is done. Then the third is compared to the first
      and puts it in the first position if it is less otherwise it compares the elements
      in between the first position and the position of the current element. It places it
      in the appropriate position. It does the same for all other elements. In the end
      the file is sorted from least to most.
************************************************************************************************/
int sortFile(ifstream &inputFile, double sortedArray[], const int MAX_SIZE)
{
   // Insert the first number into the array
   inputFile >> sortedArray[0];

   // Variable for the size
   int size = 1;

   // Sort array
   for (int position = 1; position < MAX_SIZE && inputFile >> sortedArray[position]; position++)
   {
      // If the element is less than the first element
      if (sortedArray[position] < sortedArray[0])
      {
         // Store that element
         double val = sortedArray[position];

         // Shift all the elements so far in the array to the right
         for (int pos2 = position; pos2 > 0; pos2--)
         {
            sortedArray[pos2] = sortedArray[pos2 - 1];
         } // end for (int pos2 = position; pos2 > 0; pos2--)

         // Place the element in the first position
         sortedArray[0] = val;
      } // end if (sortedArray[position] < sortedArray[0])

      // Otherwise
      else
      {
         // Compare the elements after the first position but before the position of the element you're comparing
         for (int pos3 = 1; pos3 < position; pos3++)
         {
            // If an element is greater than the element you are comparing
            if (sortedArray[position] < sortedArray[pos3])
            {
               // Store the element being compared
               double val = sortedArray[position];

               // Shift all the elements from the position that you found to be greater to the right
               for (int pos4 = position; pos4 > pos3; pos4--)
               {
                  sortedArray[pos4] = sortedArray[pos4 - 1];
               } // end for (int pos4 = position; pos4 > pos3; pos4--)

               // Store the element being compared in the position that the previous element that was greater was in
               sortedArray[pos3] = val;

            } // end if (sortedArray[position] < sortedArray[pos3])
         } // end for (int pos3 = 1; pos3 < position; pos3++)
      } // end else

      // Increment size
      size++;
   } // end for (int position = 1; position < MAX_SIZE && inputFile >> sortedArray[position]; position++)

   return size;
} // end sortFile

/*******************************************************************************
Func: displayArray
Desr: The function accepts the actual size of the array and the array itself.
      It then displays the contents of the array.
********************************************************************************/
void displayArray(int size, double sortedArray[])
{
   // Display array
   for (int count = 0; count < size; count++)
   {
      cout << sortedArray[count] << endl;
   } // end for loop
} // end displayArray