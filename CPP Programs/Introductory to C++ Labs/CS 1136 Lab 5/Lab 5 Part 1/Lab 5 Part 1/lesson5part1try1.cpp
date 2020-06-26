// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       10/14/18
// Assignment: Lab 5 Part 1
// Compiler:   Visual C++ 2017

//Description: This menu-driven program will calculate the
// number of seconds it will take for sound to travel through 
// a medium.

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   unsigned int usersChoice;
   double distance, totalSeconds;

   cout << fixed << setprecision(3);

   // Display a menu and allow the user to select an option from 1-3
   cout << "Select the medium that sound is traveling through: " << endl;
   cout << "1 Air" << endl;
   cout << "2 Water" << endl;
   cout << "3 Water" << endl;

   // Store the option chosen
   cin >> usersChoice;

   // Respond to the user's selection
   switch (usersChoice)
   {
      // If user selects option 1
      // Display a request for distance and store it
      case 1:
         cout << "Enter distance (in feet) " << endl;
         cin >> distance;

         // Validating user's input
         if (distance <= 0)
            cout << "The distance must be greater than zero" << endl;

         // Calculate the seconds and display it
         else
         {
            totalSeconds = distance / 1100.00;
            cout << "Air: " << distance << endl;
            cout << "Traveled for " << totalSeconds << " seconds" << endl;
         }
         break;

      // If user selects option 2
      // Display a request for distance and store input
      case 2:
         cout << "Enter distance (in feet) " << endl;
         cin >> distance;

         // Validating user's input
         if (distance <= 0)
            cout << "The distance must be greater than zero" << endl;

         // Calculate the seconds and display it
         else
         {
            totalSeconds = distance / 4, 900.00;
            cout << "Water: " << distance << endl;
            cout << "Traveled for " << totalSeconds << " seconds" << endl;
         }
         break;

      // Option 3
      // Display a request for distance and store input
      case 3:
         cout << "Enter distance (in feet) " << endl;
         cin >> distance;

         // Validating user's input
         if (distance <= 0)
            cout << "The distance must be greater than zero" << endl;

         // Calculate the seconds and display it
         else
         {
            totalSeconds = distance / 16400;
            cout << "Steel: " << distance << endl;
            cout << "Traveled for " << totalSeconds << " seconds" << endl;
         }
         break;

      // Validating user's menu choice
      default:
         cout << "The menu value is invalid. Please run the program again." << endl;
   }

   return 0;
} // end function main