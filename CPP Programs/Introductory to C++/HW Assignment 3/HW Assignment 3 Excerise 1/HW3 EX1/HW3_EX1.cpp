// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       9/24/18
// Assignment: HW 3 Excerise 1
// Compiler:   Visual C++ 2017

// Description:
// This program will calculate the average rainfall
// for three months entered by the user.

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
   cout << fixed << setprecision(2);
   string month1, month2, month3;                                                 // Allows for the storage of a string
   double rainfallMonth1, rainfallMonth2, rainfallMonth3, averageRainfall;        // Allows for the storage of decimal numbers

   // Display a request for the name of month 1 and store it
   cout << "Please enter the name of month 1: ";
   cin >> month1;

   // Display a request for the rainfall of month 1 and store it
   cout << "Please enter the amount of rainfall (in inches) of " << month1 << ": ";
   cin >> rainfallMonth1;


   cout << endl;


   // Display a request for the name of month 2 and store it
   cout << "Please enter the name of month 2: ";
   cin >> month2;

   // Display a request for the rainfall of month 2 and store it
   cout << "Please enter the amount of rainfall (in inches) of " << month2 << ": ";
   cin >> rainfallMonth2;


   cout << endl;


   // Display a request for the name of month 3 and store it
   cout << "Please enter the name of month 3: "; 
   cin >> month3;

   // Display a request for the rainfall of month 3 and store it
   cout << "Please enter the amount of rainfall (in inches) of " << month3 << ": ";
   cin >> rainfallMonth3;


   cout << endl;


   // Calculate average rainfall of all three months
   averageRainfall = (rainfallMonth1 + rainfallMonth2 + rainfallMonth3) / 3;

   // Display average rainfall of all three months
   cout << "The average rain fall for " << month1 << ", " << month2 << ", and " << month3 << " was ";
   cout << averageRainfall << " inches." << endl;

   system("pause");

   return 0;
} // end function main

