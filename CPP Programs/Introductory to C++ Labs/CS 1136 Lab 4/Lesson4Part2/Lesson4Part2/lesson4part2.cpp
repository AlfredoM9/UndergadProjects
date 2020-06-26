// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       10/7/18
// Assignment: Lab 4 Part 2
// Compiler:   Visual C++ 2017

/* Description: This program will read in the number of seconds and covert
it to days, hours, minutes, and remaining seconds.
*/

#include <iostream>

using namespace std;

int main()
{
   long long int totalSeconds, totalDays, totalHours1,       // Used to hold large integer values but no decimals
                 totalHours2, totalMinutes1, 
                 totalMinutes2, remainingSeconds;

   // Store the input of seconds
   cin >> totalSeconds;

   // Display the total seconds inputed
   cout << "Total seconds: " << totalSeconds << endl;
   cout << endl;

   //Validating the user's input if positive or negative
   if (totalSeconds > 0)
   {
      // Calculate the number of days, hours, minutes, and seconds from the input
      totalDays = totalSeconds / 86400;
      totalHours1 = totalSeconds - (totalDays * 86400);
      totalHours2 = totalHours1 / 3600;
      totalMinutes1 = totalHours1 - (totalHours2 * 3600);
      totalMinutes2 = totalMinutes1 / 60;
      totalSeconds = totalMinutes1 - (totalMinutes2 * 60);

      // If the days are greater than zero it will display
      if (totalDays > 0)
         cout << totalDays << " day(s)" << endl;

      // If the total hours are greater than zero it will display
      if (totalHours2 > 0)
         cout << totalHours2 << " hour(s)" << endl;

      // If the total minutes are greater than zero it will display
      if (totalMinutes2 > 0)
         cout << totalMinutes2 << " minute(s)" << endl;

      // If the total seconds are greater than zero it will display
      if (totalSeconds > 0)
         cout << totalSeconds << " second(s)" << endl;


   } // end if block

   // If the input is negative it display a message indicating to insert a positive
   else
      cout << "Total seconds must be greater than zero" << endl;

   return 0;

} // end function main