// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       10/7/18
// Assignment: Lab 4 Part 1
// Compiler:   Visual C++ 2017

//Description:
// This program will read in the mass of an object and calculate
// the weight (in N) on the Earth, on the Moon, and on Venus, and determine 
// if the object is light or heavy.

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   const double earthAcceleration = 9.81;   // Acceleration of the earth due to gravity
   const double moonAcceleration = 1.62;    // Acceleration of the moon due to gravity
   const double venusAcceleration = 8.87;   // Acceleration of venus due to gravity

   double massObject, earthWeight, moonWeight, venusWeight;

   cout << fixed << setprecision(4);    // Allows for the outcome to be printed to 4 decimal places to the right

   // Store the input of the mass of the object
   cin >> massObject;

   // Validating the user's input if postive or negative
   if (massObject > 0)
   {
      // Calculate the weight on earth
      earthWeight = massObject * earthAcceleration;

      // Calculate the weight on the moon
      moonWeight = massObject * moonAcceleration;

      // Calculate the weight on venus
      venusWeight = massObject * venusAcceleration;

      // Display the mass given
      cout << "The mass is " << massObject << " kg" << endl;

      // Display the weights calculated with the words on the left and the weights on the right
      cout << left << setw(8) << "Location" << right << setw(14) << "Weight (N)" << endl;
      cout << left << setw(8) << "Earth" << right << setw(14) << earthWeight << endl;
      cout << left << setw(8) << "Moon" << right << setw(14) << moonWeight << endl;
      cout << left << setw(8) << "Venus" << right << setw(14) << venusWeight << endl;

      // Determine if the weight is heavy or light
      if (earthWeight >= 1500)
         cout << "The object is heavy" << endl;
      else if ((earthWeight < 5) && (earthWeight >= 0))
         cout << "The object is light" << endl;

   } // end if (massObject >= 0) block

   // If less than zero display a message for a greater input
   else
   {
      cout << "The mass is " << massObject << " kg" << endl;
      cout << "The mass must be greater than zero" << endl;

   } // end else block

   return 0;

} // end function main