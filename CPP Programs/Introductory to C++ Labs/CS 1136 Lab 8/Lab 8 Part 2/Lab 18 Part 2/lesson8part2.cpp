// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       11/11/18
// Assignment: Lab 8 Part 2
// Compiler:   Visual C++ 2017

/*********************************************************************************************************************
Program Description: This program will calculate the present value. The present value is the amount                  *
                     needed today (hence present) to have a certain amount in the future (future value)              *
                     corresponding to certain amount of years in the future. For example if you want                 *
                     $1,000 dollars in 5 years this program will calculate the present value needed.                 *
                     This program will first ask for the future value, the annual interest rate, and the             *
                     number of years from the user. It will then validate the input and calculate the                *
                     present value. Finally, it will display the results obtained.                                   *
                                                                                                                     *
**********************************************************************************************************************/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Function Protoypes
double calculatePresentValue(double futureValue, double interestRate, int numberYears);
double readFutureValue();
double readAnnualIntRate();
int readNumberOfYears();
void displayResults(double presentValue, double futureValue, double interestRate, int numberOfYears);

// main function
int main()
{
   double futureValue, interestRate, presentValue;
   int numberOfYears;

   // Call read future value function and set return value to futureValue
   futureValue = readFutureValue();

   // Call read annual int rate function and set return value to interestRate
   interestRate = readAnnualIntRate();

   // Call number of years function and set return value to numberOfYears
   numberOfYears = readNumberOfYears();

   // Call calculate present value function and set return value to presentValue
   presentValue = calculatePresentValue(futureValue, interestRate, numberOfYears);

   // Call display results to execute with the arguments being the variables initialize to the return values of
   // other functions
   displayResults(presentValue, futureValue, interestRate, numberOfYears);

   return 0;
} // end function main

// calculatePresentValue will calculate the present value using parameters and the arguments in the function call
// using a formula and then returning the value.
double calculatePresentValue(double futureValue, double interestRate, int numberYears)
{
   double presentValue;

   // Calculate present value using the parameters
   presentValue = futureValue / (pow((1 + interestRate), numberYears));

   // Return value
   return presentValue;
} // end function calculatePresentValue

// readFutureValue will read in the future value entered by the user and validate the input. If
// invalid an error message will display and another entry will be required by the user until
// valid data is entered.
double readFutureValue()
{
   double futureValue;

   // Loop the entry with prompt until valid data is entered
   do
   {
      cout << "Enter future value" << endl;
      cin >> futureValue;

      // Display error message if data invalid
      if (futureValue <= 0)
         cout << "The future value must be greater than zero" << endl;
   } while (futureValue <= 0);

   // return value entered by the user
   return futureValue;
} // end function readFutureValue

// readAnnualIntRate will read in the annual interest rate entered by the user and validate the input. If
// invalid an error message will display and another entry will be required by the user until
// valid data is entered.
double readAnnualIntRate()
{
   double annualIntRate;
   // Loop the entry with prompt until valid data is entered
   do
   {
      cout << "Enter annual interest rate" << endl;
      cin >> annualIntRate;

      // Display error message if data invalid
      if (annualIntRate <= -0)
         cout << "The annual interest rate must be greater than zero" << endl;
   } while (annualIntRate <= 0);
   annualIntRate /= 100;

   // return value entered by the user
   return annualIntRate;
} // end function readAnnualIntRate

// readNumberOfYears will read in the number of years entered by the user and validate the input. If
// invalid an error message will display and another entry will be required by the user until
// valid data is entered.
int readNumberOfYears()
{
   int numberOfYears;

   // Loop the entry with prompt until valid data is entered
   do
   {
      cout << "Enter number of years" << endl;
      cin >> numberOfYears;

      // Display error message if data invalid
      if (numberOfYears <= 0)
         cout << "The number of years must be greater than zero" << endl;
   } while (numberOfYears <= 0);

   // return value entered by the user
   return numberOfYears;
} // end function numberOfYears

// displayResults will display the data gathered by the previous functions and set the data to a 
// fixed format
void displayResults(double presentValue, double futureValue, double interestRate, int numberOfYears)
{
   // Display results with the parameters used. Set data to a fixed format.
   cout << "Present value: $" << fixed << setprecision(2) << presentValue << endl;
   cout << "Future value: $" << futureValue << endl;
   interestRate *= 100;
   cout << "Annual interest rate: " << fixed << setprecision(1) << interestRate << "%" << endl;
   cout << "Years: " << numberOfYears << endl;
} // end function displayResults


