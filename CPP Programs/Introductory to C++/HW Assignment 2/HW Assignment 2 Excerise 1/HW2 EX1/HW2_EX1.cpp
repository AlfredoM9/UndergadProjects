// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       9/18/18
// Assignment: Homework Assignment 2 Excerise 1
// Compiler:   Visual C++ 2017

//Description:
// This program will calculate the amount 
// of gallons needed in order to complete the
// user's trip.

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
   cout << fixed << setprecision(1);               // Allows for the total amount of gallons to be set to one decimal point.

   double inTownMiles, highwayMiles, gallons;      // Holds the type number for inTownMiles, highwayMiles, & gallons


   // Display a request asking for the in town driving miles from the user
   cout << "Please enter the number of in-town driving miles:";

   //Store user's input of in town driving miles
   cin >> inTownMiles;


   //Display a request asking for the highway driving miles from the user
   cout << "Please enter the number of highway driving miles:";

   //Store user's input of highway driving miles
   cin >> highwayMiles;


   //Skips a line for improved readability
   cout << endl;


   //Calculate the gallons needed for the miles indicated
   gallons = ((inTownMiles / 23.5) + (highwayMiles / 28.9));

   //Display the amount of gallons needed for the miles indicated
   cout << "The total amount of gallons required is:" << gallons << endl;

   system("pause");

   return 0;

} //end function main