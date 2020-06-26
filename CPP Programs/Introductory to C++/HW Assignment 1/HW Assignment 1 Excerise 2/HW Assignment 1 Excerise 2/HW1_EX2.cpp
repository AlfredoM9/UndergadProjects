// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       9/12/18
// Assignment: Homework Assignment 1, Excerise 2
// Compiler:   Visual Studios C++ 2017

// Description:
// Calculate the distrance traveled 
// under acceleration and time.

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
   cout << fixed << setprecision(1);

   float timeVal;

   timeVal = 5.36;                                            // timeVal is the time given
                                                              
   float acceleration;
                                                              
   acceleration = 32.0;                                       // acceleration is given
                                                              
   double distanceVal;                                        
                                                              
   distanceVal = ( (1.0/2)*acceleration*timeVal*timeVal);     //formula is given to calculate distance

   cout << "The time was:               " << timeVal      << "   seconds"     << endl;
   cout << "The acceleration was:       " << acceleration << "  feet/sec/sec" << endl;
   cout << "The distance traveled was:  " << distanceVal  << " feet"          << endl;

   system("pause");

   return 0;
}  // end function main