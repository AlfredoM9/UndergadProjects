// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       11/18/18
// Assignment: Lab 9 Part 2
// Compiler:   Visual C++ 2017

/**********************************************************************************
Description: This program will calculate the future value. It first open a file   *
             and read data from the file. It will read in the present value, the  *
             interest rate and the number of months. If the read data is invalid  *
             it will display an error message. Once the data is gathered it will  *
             calculate the future value. Once the future value is calculated it   *
             will write the data (future value, present value, interest rate,     *
             number of months)  in a spreedsheet file called "output.xls".        *
***********************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

// Function prototypes
double calculateFutureValue(double presentValue, double interestRate, int months);
unsigned int readData(ifstream & inputFile, double & presentValue, double & interestRate, int & months);
void displayData(ofstream & outputFile, double futureValue, double presentValue, double interestRate, int months);

// main function
int main ()
{
   // Variables
   string fileName;
   ifstream inputFile;

   // Read in file name to be opened and read
   cin >> fileName;

   // Open file
   inputFile.open(fileName);

   // If open unsuccessfully display error message and stop processing
   if (inputFile.fail())
      cout << "File \"" << fileName << "\" could not be opened" << endl;

   // If opened successfully
   else
   {
      // Variables
      double presentValue, interestRate;
      int months;
      unsigned int value;
      ofstream outputFile;

      // Open file "output.xls" to write data on
      outputFile.open("output.xls");

      // If opened unsuccessfully display error message and stop processing
      if (outputFile.fail())
         cout << "File \"output.xls\" could not be opened" << endl;

      // If opened successfully
      else
      {
         // Write headers to the file
         outputFile << "Future Value\tPresent Value\tMonthly Interest\tMonths" << endl;

         // Read in data from the input file
         do
         {
            // Call readData function to read the present value, interest rate, and months (all passed by reference)
            value = readData(inputFile, presentValue, interestRate, months);

            // If return is 2 (other wise if the values are negative) display data and error message
            if (value == 2)
            {
               cout << fixed << setprecision(2);
               cout << presentValue << " " << interestRate << " " << months << endl;
               cout << "One or more of the above values are not greater than zero" << endl;
            } // end if (value == 2)

            // If the readData function returns a 1 (meaning it has valid data) pass the data to the calculateFuture value
            // function and calculate future value and call displayData to write it to the file
            else if (value == 1)
            {
               double futureValue;

               // Convert percentage to decimal
               interestRate /= 100;

               // Call calculation function
               futureValue = calculateFutureValue(presentValue, interestRate, months);

               // Convert decimal to percentage
               interestRate *= 100;

               // Call function to write on file
               displayData(outputFile, futureValue, presentValue, interestRate, months);

            } // end else if (value == 1)
           
            // Once the return value is zero it has reached the end of the file and end of the loop
         } while (value != 0); // end do while loop

         // Close files
         inputFile.close();
         outputFile.close();

      } // end else output opens sucessfully

   } // end else input opens sucessfully 

   return 0;

} // end function main

// readData: This function will read in the data from the file passed through the argument into the parameter. It will first pass the value
// to the present value variable then the interest rate variable and the months variable. If any of the variables holds a zero or negative number
// it will return a 2. If the data is valid it will return a 1 and if there is no data to read then it will return a 0. The variables are passed
// by reference thus it will change the value of the arguments.
unsigned int readData(ifstream & inputFile, double & presentValue, double & interestRate, int & months)
{
   // Check for the end of the file
   if (inputFile >> presentValue)
   {
      // Copy data
      inputFile >> interestRate >> months;

      // If invalid data return a 2
      if (presentValue <= 0 || interestRate <= 0 || months <= 0)
         return 2;

      // If valid return a 1
      else
         return 1;
   } // end if (inputFile >> presentValue)

   // If end of file return a 0
   else
      return 0;

} // end function readData

// calculateFutureValue: This function will calculate the future value and return the future value. It will
// use a formula to get the future value using the parameters. It will then return the value.
double calculateFutureValue(double presentValue, double interestRate, int months)
{
   // Variable to hold futureValue
   double futureValue;

   // Calculate future value
   futureValue = presentValue * pow((1 + interestRate), months);

   // Return future value
   return futureValue;

} // end function calculateFutureValue

// displayData: This function will write the data into the file. It will gathered the data through its parameters and
// write to the file with tabs in between and a fixed format of two decimal places
void displayData(ofstream & outputFile, double futureValue, double presentValue, double interestRate, int months)
{
   // Fix format
   outputFile << fixed << setprecision(2);

   // Write data to file
   outputFile << futureValue << "\t" << presentValue << "\t" << interestRate << "\t" << months << endl;

} // end displayData