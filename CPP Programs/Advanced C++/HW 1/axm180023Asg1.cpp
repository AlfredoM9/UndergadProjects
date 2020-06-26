/**********************************************************************************
                                                                                  *
Author:     Alfredo Mejia (NET ID: AXM180023)                                     *
Course:     CS 1337.009                                                           *
Date:       1/25/19                                                               *
Assignment: HW Assignment 1                                                       *
Compiler:   Visual Studios C++ 2017                                               *
                                                                                  *
Description: This prgram will request a number from the user. It will             *
             then verify if the input is greater than 1. If zero is               *
             entered the program will stop; however, if the input is              *
             equal to 1 or less than zero an error message will be                *
             displayed .It will re-prompt until a valid integer is entered.       *
             Finally it will use a formula to calculate the sum of the            *
             series of 1/N + 2/N-1 + 3/N-2 + ... and so on until the              *
             denominated is 1. N will be the input from the user. It will          *
             then display oringal number and the sum.                             *
                                                                                  *
**********************************************************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

// Function Prototypes
int requestNum();
double calculateSum(int numEntered);
void displayResults(int numEntered, double totalSum);

// main function
int main()
{
   // Variables to hold number entered by the user and the total sum
   int numEntered;
   double totalSum;

   // Re-prompt until user enters a zero
   do
   {
      // Call requestNum and returns a valid number entered by the user
      numEntered = requestNum();

      // If the user doesn't want to end the program
      if (numEntered != 0)
      {
         // Call calculateSum to calulate total and return the total
         totalSum = calculateSum(numEntered);

         // Call displayResults
         displayResults(numEntered, totalSum);
      }

      // If the user did enter zero display message about ending the program
      else
         cout << "The program has ended." << endl;

   } while (numEntered != 0); // end do-while 

   return 0;
} // end main

/*********************************************************************************************
Function
Name: requestNum

Description: This function will display a message requesting for a number greater
             than one. If the input is invalid a error message will appear and ask
             the user to enter the data again. If the input is zero it will return
             immediately a zero. Finally once a valid data is entered it will return
             the valid input

**********************************************************************************************/
int requestNum() 
{
   // Variables to hold data
   int numEntered;
   string userInput;
   bool validInput;

   // Prompt a message until user enter zero or valid data
   do
   {
      // Display message and store input
      cout << "Please enter a number greater than 1 or enter 0 to end the program: ";
      cin >> userInput;

      // If the string has characters display error message and reprompt valid data
      if ((userInput >= "A" && userInput <= "Z") || (userInput >= "a" && userInput <= "z"))
      {
         cout << "Invalid Entry. Characters are not allowed. Please read carefully." << endl;
         validInput = false;
      } // end if ((userInput >= "A" && userInput <= "Z") || (userInput >= "a" && userInput <= "z"))

      // Else if numbers are present
      else
      {
         // Convert the string into an int
         numEntered = atoi(userInput.c_str());

         // If the value is zero return immediately 
         if (numEntered == 0)
            return numEntered;

         // If valid data
         else if (numEntered > 1)
            validInput = true;

         // If the value is not valid data and not zero display error message and re-prompt for valid data
         else
         {
            cout << "Invalid Entry. Negative numbers and/or one are invalid. Please read carefully." << endl;
            validInput = false;
         } // end inner else

      } // end outter else

   } while (!validInput); // end do-while

   // return valid data
   return numEntered;

} // end requestNum

/******************************************************************************************************
Function
Name: calculateSum

Description: The function will read in the valid number gathered from the user and use it in
             the formula provided. This will give us the total sum. The total sum will be calculated
             using a for loop and once it's finish it will return the total sum.

********************************************************************************************************/
double calculateSum (int numEntered)
{
   // Variable to hold total sum
   double totalSum = 0.0;

   // For loop to calculate total sum
   for (int counter = 0; counter < numEntered; counter++)
      totalSum += ((counter + 1.0) / (numEntered - counter));

   // Return total sum
   return totalSum;
} // end calculateSum

/*************************************************************************************************
Function
Name: displayResults

Description: The function will read in the valid data inputted by the user and the total sum
             calulated by the function. It will then display the results.
***************************************************************************************************/
void displayResults(int numEntered, double totalSum)
{
   // Display Results
   cout << endl;
   cout << "You have entered number : "  << numEntered <<  endl;
   cout << "The sum of the number is: " << totalSum << fixed << setprecision(2) <<  endl;
   cout << endl;
} // end displayResults