// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       11/8/18
// Assignment: Lab 8 Part 1
// Compiler:   Visual C++ 2017

/****************************************************************
Program Description: This program will calculate the distance an object
                     travels (in meters) on Earth for a specified number
                     of seconds. The time will be inputted by the user. 
                     This program will consist of the main function in 
                     addition to three other functions.

*****************************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double readSeconds();
double calculateDistance(double seconds);
void displayResults(double seconds, double distance);

// main function
int main ()
{
   // Variables for function's returns
   double seconds, distance;

   // Calculate the distance
   do
   {
      // First validate user's input
      do
      {
         // Input returned are seconds
         seconds = readSeconds();
      } while (seconds < 0); // end nested do -while loop

      // If seconds are zero terminate loop
      if (seconds == 0)
         break;

      // Otherwise calculate distance and display results by calling the functions
      distance = calculateDistance(seconds);
      displayResults(seconds, distance);

   } while (seconds != 0); // end do-while loop

   return 0;
} // end function main

/*****************************************************************************************************************
readSeconds Function Description: This function will read in the value from the user and display error message   *
                                  if the seconds are negative. It will then return the value inputted by the user*
******************************************************************************************************************/

// Read in value from user
double readSeconds()
{
   // Display prompt and store value
   double userInput;
   cout << "Enter the time (in seconds)" << endl;
   cin >> userInput;

   // If negative display an error message
   if (userInput < 0)
      cout << "The time must be zero or more" << endl;

   // Return the value inputted
   return userInput;
} // end function double readSeconds 

/********************************************************************************************************************************************
calculateDistance Function Description: This function will obtain a value from the argument into the parament that is going to be called    *
                                        seconds. From there the function will calculate the distance calculated using a formula. It will    *
                                        then return the calculated distance.                                                                *
                                                                                                                                            *
*********************************************************************************************************************************************/

// Calculate the distance an obect falls during the specified number of seconds
double calculateDistance(double seconds)
{
   double distanceCalculated;

   // Constant for accleration due to gravity
   const double accelerationOfGravity = 9.8;

   // Calculate distance
   distanceCalculated = 0.5 * accelerationOfGravity * pow(seconds, 2);

   // Return the distance calculated
   return distanceCalculated;
} // end function double calculateDistance

/***********************************************************************************************************************************************
displayResults Function Description: This function will display the seconds inputted by the user (after validation) and display the distance   *
                                     calculated to a fixed format.                                                                             *
************************************************************************************************************************************************/

// Display both the number of seconds an object has fallen as well as the distance
void displayResults(double seconds, double distance)
{
   // Display results
   cout << "The object traveled " << fixed << setprecision(3) << distance
        << " meters in " << fixed << setprecision(2) << seconds << " seconds" << endl;

} // end void function

