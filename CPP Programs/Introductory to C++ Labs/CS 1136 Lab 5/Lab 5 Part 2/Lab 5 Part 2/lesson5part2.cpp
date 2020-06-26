// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       10/14/18
// Assignment: Lab 5 Part 2
// Compiler:   Visual C++ 2017

// Description: This menu-driven program will calculate the
// distance it will take for sound to travel through 
// a medium by an input of seconds.

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   unsigned int usersChoice;
   double totalSeconds, distance;

   // Values given of meters traveled in one second
   const double CARBON_DIOXIDE = 258.0;
   const double AIR = 331.5;
   const double HELIUM = 972.0;
   const double HYDROGEN = 1270.0;

   // Display menu and store user's choice
   cout << "Select the medium that sound is traveling through:" << endl;
   cout << "1 Carbon Dioxide" << endl;
   cout << "2 Air" << endl;
   cout << "3 Helium" << endl;
   cout << "4 Hydrogen" << endl;
   cin >> usersChoice;

   // Validating user's choice if invalid
   if (usersChoice <= 0 || usersChoice > 4)
      cout << "The menu value is invalid. Please run the program again." << endl;

   // User's choice valid
   else
   {
      // Display a request for seconds and store it
      cout << "Enter time (in seconds)" << endl;
      cin >> totalSeconds;

      // Validating user's input of seconds if invalid
      if (totalSeconds < 0 || totalSeconds > 30)
         cout << "The time must be between 0.00 and 30.00 (inclusive)" << endl;

      // Valid input of seconds
      else
      {
         // If user selected menu option 1
         if (usersChoice == 1)
         {
            // Display medium selected and total seconds inputted
            cout << fixed << setprecision(2) << "Carbon Dioxide: ";
            cout << totalSeconds << " seconds" << endl;

            // Calculate the distance
            distance = totalSeconds * CARBON_DIOXIDE;

            // Display calculated distance in meters
            cout << fixed << setprecision(3) << "Traveled ";
            cout << distance << " meters" << endl;

         } // end if (usersChoice == 1) function

         // If user selected menu option 2
         else if (usersChoice == 2)
         {
            // Display medium selected and total seconds inputted
            cout << fixed << setprecision(2) << "Air: ";
            cout << totalSeconds << " seconds" << endl;

            // Calculate the distance
            distance = totalSeconds * AIR;

            // Display calculated distance in meters
            cout << fixed << setprecision(3) << "Traveled ";
            cout << distance << " meters" << endl;

         } // end else if (usersChoice == 2) function

         // If user selected menu option 3
         else if (usersChoice == 3)
         {
            // Display medium selected and total seconds inputted
            cout << fixed << setprecision(2) << "Helium: ";
            cout << totalSeconds << " seconds" << endl;

            // Calculate the distance
            distance = totalSeconds * HELIUM;

            // Display calculated distance in meters
            cout << fixed << setprecision(3) << "Traveled ";
            cout << distance << " meters" << endl;

         } // end else if (usersChoice == 3) function

         // If user selected menu option 4
         else if (usersChoice == 4)
         {
            // Display medium selected and total seconds inputted
            cout << fixed << setprecision(2) << "Hydrogen: ";
            cout << totalSeconds << " seconds" << endl;

            // Calculate the distance
            distance = totalSeconds * HYDROGEN;

            // Display calculated distance in meters
            cout << fixed << setprecision(3) << "Traveled ";
            cout << distance << " meters" << endl;

         } // end else if (usersChoice == 4) function

      } // end else function of user's input of seconds is valid

   } // end else fucntion of user's menu option is valid

   return 0;

} // end function main
