// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       9/18/18
// Assignment: Homework Assignment 2 Excerise 2
// Compiler:   Visual C++ 2017

//Description:
// This program will calculate different temperatures into
// different temperature units.

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
   cout << fixed << setprecision(2);                      //This allows for every outcome to be set to two decimal places

   double kelvin, celsius, fahrenhiet;                    //Holds the type of number that is going to used by Kelvin, Celsius, and Fahrenhiet


   //Display a request for a number in degrees Celsius
   cout << "Please enter a number in degrees Celsius:    ";

   //Store user's input of Celsius number
   cin >> celsius;

   //Skip a line for readability
   cout << endl;

   //Calculate Fahrenhiet temperature by the Celsius number inserted by the user
   fahrenhiet = (((9.0 / 5)*celsius) + 32);

   //Calculate Kelvin temperature by the Celsius number inserted by the user
   kelvin = (celsius + 273.15);

   //Display the equivalent Fahrenhiet temperature to the Celsius temperature inserted
   cout << "The equivalent Fahrenhiet temperature is:    " << fahrenhiet << " degrees" << endl;

   //Display the equivalent Kelvin temperature to the Celsius temperature inserted
   cout << "The equivalent Kelvin temperature is:        " << kelvin << " K" << endl;


   //Skips a line for readability
   cout << endl;


   //Display a request for a number in degrees Fahrenhiet
   cout << "Please enter a number in degrees Fahrenhiet: ";

   //Store user's input of Fahrenhiet number
   cin >> fahrenhiet;

   //Skips a line for readbility
   cout << endl;

   //Calculate Celsius temperature by the Fahrenhiet number inserted by the user
   celsius = ((5.0*(fahrenhiet - 32) / 9));

   //Calculate Kelvin temperature by the Fahrenhiet number inserted by the user.
   kelvin = (celsius + 273.15);

   //Display the equivalent Celsius temperature to the Fahrenhiet temperature inserted
   cout << "The equivalent Celsius temperature is:       " << celsius << " degrees" << endl;

   //Display the equivalent Kelvin temperature to the Fahrenhiet temperature inserted
   cout << "The equivalent Kelvin temperature is:        " << kelvin << " K" << endl;


   //Skip a line for readbility
   cout << endl;


   //Display a request for a number in Kelvin
   cout << "Please enter a number in Kelvin:             ";

   //Store user's input of Kelvin number
   cin >> kelvin;

   //Skip a line for readability
   cout << endl;

   //Calculate Celsius temperature by the Kelvin number inserted by the user
   celsius = (kelvin - 273.15);

   //Calculate Fahrenhiet temperature by the Kelvin number inserted by the user
   fahrenhiet = (((9.0 / 5)*celsius) + 32);

   //Display the equivalent Celsius temperature to the Kelvin temperature inserted
   cout << "The equivalent Celsius temperature is:       " << celsius << " degrees" << endl;

   //Display the equivalent Fahrenhiet temperature to the Kelvin temperature inserted
   cout << "The equivalent Fahrenhiet temperature is:    " << fahrenhiet << " degrees" << endl;

   system("pause");

   return 0;
} //end function main