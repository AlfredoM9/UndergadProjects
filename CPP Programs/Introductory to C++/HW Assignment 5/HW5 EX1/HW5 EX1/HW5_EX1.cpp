// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       10/13/18
// Assignment: HW 5 Excersie 1
// Compiler:   Visual C++ 2017

/* Description:
   This program will prompt the user for some number of seconds.
   If it's less than 60 seconds it will display the seconds, if it is greater
   than 60 but less than 3,600 it will display the minutes, if the input is greater than 3,600
   but less than 86,400 seconds it will display the hours, and if it is greater
   than 86,400 then it will display the days equivalent to the seconds inputted.
*/ 

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   cout << fixed << setprecision(2);  // Allows for the output to have two digits after the decimal
   double totalSeconds, totalMinutes, totalHours, totalDays;
   int secondsInputted;

   // Displays a prompt for seconds and store it
   cout << "Please enter the number of seconds: ";
   cin >> secondsInputted;

   // If true calculate the seconds and display it
   if (secondsInputted < 60 && secondsInputted > 0)
   {
      totalSeconds = secondsInputted / 1.0;
      cout << secondsInputted << " seconds is " << totalSeconds << " seconds." << endl;
   } // end if function

   // If true calculate the minutes and display it
   else if (secondsInputted >= 60 && secondsInputted < 3600)
   {
      totalMinutes = secondsInputted / 60.0;
      cout << secondsInputted << " seconds is " << totalMinutes << " minutes." << endl;
   } // end else if minutes function

   // If true calculate the hours and display it
   else if (secondsInputted >= 3600 && secondsInputted < 86400)
   {
      totalHours = secondsInputted / 3600.0;
      cout << secondsInputted << " seconds is " << totalHours << " hours." << endl;
   } // end else if hours function

   // If true calculate the days and display it
   else if (secondsInputted >= 86400)
   {
      totalDays = secondsInputted / 86400.0;
      cout << secondsInputted << " seconds is " << totalDays << " days." << endl;
   } // end else if days function

   // Validating user's input
   else
      cout << "Please enter a positive number" << endl;

   system("pause");

   return 0;
} // end function main