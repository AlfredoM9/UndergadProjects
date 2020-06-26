// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       11/4/18
// Assignment: Lab 7 Part 1
// Compiler:   Visual C++ 2017

// Description: This program will read sales information from
// a file and write out a bar chart for each of the stores
// based on the sales information given from the file.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
   string fileName;

   // Read in the file name given by the user
   cin >> fileName;

   ifstream inputFile;

   // Open file given by the user
   inputFile.open(fileName);

   // If the file opens successfully
   if (inputFile)
   {
      unsigned int storeNumber;
      long long int salesNumber, numberofXs, counter;

      ofstream outputFile;

      // Create a file for data of sales chart
      outputFile.open("saleschart.txt");

      // If opened succesfully
      if (outputFile)
      {
         // Write the header onto the file created
         outputFile << "SALES BAR CHART" << endl;
         outputFile << "(Each X equals 1,000 dollars)" << endl;

         // Read data from the file given by the user and check for the end of the file
         while (inputFile >> storeNumber >> salesNumber)
         {
            // Validate store number being read: if invalid display error message and terminate the iteration
            if (storeNumber < 1 || storeNumber > 99)
            {
               cout << "The store number " << storeNumber << " is not valid" << endl;
               continue;
            } // end if (storeNumber < 1 || storeNumber > 99)

            // Validate sales data being read: if invalid display error message and terminate the iteration
            if (salesNumber < 0)
            {
               cout << "The sales value for store " << storeNumber << " is negative" << endl;
               continue;
            } // end if (salesNumber < 0)

            // Calculate "X"s needed to be printed
            numberofXs = salesNumber / 1000;

            // Write the store number onto the file created
            outputFile << "Store " << setw(2) << storeNumber << ": ";

            // for loop to print the necessary "X"s for each store onto the file created
            for (counter = 1; counter <= numberofXs; counter++)
            {
               outputFile << "X";
            } // end for (counter = 1; counter <= numberofXs; counter++)

            // Print new line
            outputFile << endl;

         } // end while (inputFile >> storeNumber >> salesNumber)

      } // end if (outputFile)

      // If saleschart.txt doesn't open successfully display error message and close file opened
      else
      {
         cout << "File \"saleschart.txt\" could not be opened";
         inputFile.close();
      } // end else statement of outputFile
      
      // Close both files when finished
      inputFile.close();
      outputFile.close();

   } // end if (inputFile)

   // If the file given by the user does not open successfully display error message
   else
      cout << "File \"" << fileName << "\" could not be opened" << endl;

   return 0;

} // end function main