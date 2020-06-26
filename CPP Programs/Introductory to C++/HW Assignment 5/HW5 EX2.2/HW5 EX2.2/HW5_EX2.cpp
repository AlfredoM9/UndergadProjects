// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       10/15/18
// Assignment: HW 5 Excerise 2
// Compiler:   Visual C++ 2017

//Description:This program will calculate a customer's
// monthly bill with the choice of the customer's desired
// package and estimated minutes.

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   char usersChoice;
   double costPackageA, costPackageB, costPackageC,
          bestPackage, totalMinutes;

   // Display menu and store user's choice
   cout << "Please select from one of the following packages (A, B, C)" << endl << endl;
   cout << "Package A:   For $39.99 per month 450 minutes are provided. ";
   cout << "Additional minutes are" << endl << "$0.45 per minute" << endl << endl;
   cout << "Package B:   For $59.99 per month 900 minutes are provided. ";
   cout << "Additional minutes are" << endl << "$0.40 per minute" << endl << endl;
   cout << "Package C:   For $69.99 per month unlimited minutes provided." << endl;
   cin >> usersChoice;

   // Display a request for the minutes that will be used and store it
   cout << "Please enter the following minutes that will be used." << endl;
   cin >> totalMinutes;

   // Validating users input of menu option and minutes
   if (((usersChoice >= 'A'&& usersChoice <= 'C') || (usersChoice >= 'a' && usersChoice <= 'c')) && (totalMinutes >= 0))
   {  
      // Calculate the price for all packages
      if (totalMinutes <= 450)
      {
         costPackageA = 39.99;
         costPackageB = 59.99;
         costPackageC = 69.99;
      } // end if (totalMinutes <= 450) function

      else if (totalMinutes > 450 && totalMinutes <= 900)
      {
         costPackageA = (((totalMinutes - 450) * 0.45) + 39.99);
         costPackageB = 59.99;
         costPackageC = 69.99;
      } // end else if (totalMinutes > 450 && totalMinutes <= 39.99) function

      else if (totalMinutes > 900)
      {
         costPackageA = (((totalMinutes - 450) * 0.45) + 39.99);
         costPackageB = (((totalMinutes - 900) * 0.40) + 59.99);
         costPackageC = 69.99;
      } // end else if (totalMinutes > 900) function

      // Calculate the best package available
      bestPackage = costPackageA;

      if (costPackageB < bestPackage)
         bestPackage = costPackageB;

      if (costPackageC < bestPackage)
         bestPackage = costPackageC;

      cout << fixed << setprecision(2);

      switch (usersChoice)
      {
         // Display the cost if package A chosen
         case 'a':
         case 'A':
            cout << "Your monthly bill will be $" << costPackageA << endl;

            // If bestPackage is package A congradulate the user for choosing the correct package
            if (bestPackage == costPackageA)
               cout << "Great Job! This package is well suited for your needs." << endl;

            // If the user didn't chose the best package advise the user to the best package
            else if (bestPackage == costPackageB)
            {
               cout << "There is a better option." << endl;
               cout << "Package B will be more suited for your needs costing $";
               cout << bestPackage << endl;
            } // end inner switch else if (bestpackage == costPackageB) function

            else if (bestPackage == costPackageC)
            {
               cout << "There is a better option." << endl;
               cout << "Package C will be more suited for your needs costing $";
               cout << bestPackage << endl;
            } // end inner switch else if (bestPackage == costPackageC) function

            break;

         // Display the cost if package B chosen
         case 'b':
         case 'B':
            cout << "Your monthly bill will be $" << costPackageB << endl;

            // If bestPackage is package B congradulate the user for choosing the correct package
            if (bestPackage == costPackageB)
               cout << "Great Job! This package is well suited for your needs." << endl;

            // If the user didn't chose the best package advise the user to the best package
            else if (bestPackage == costPackageA)
            {
               cout << "There is a better option." << endl;
               cout << "Package A will be more suited for your needs costing $";
               cout << bestPackage << endl;
            } // end inner switch else if (bestPackage == costPackageA) function

            else if (bestPackage == costPackageC)
            {
               cout << "There is a better option." << endl;
               cout << "Package C will be more suited for your needs costing $";
               cout << bestPackage << endl;
            } // end inner switch else if (bestPackage == costPackageC) function

            break;

         // Display the cost if package C chosen
         case 'c':
         case 'C':
            cout << "Your monthly bill will be $" << costPackageC << endl;

            // If bestPackage is package C congradulate the user for choosing the correct package
            if (bestPackage == costPackageC)
               cout << "Great Job! This package is well suited for your needs." << endl;

            // If the user didn't chose best package advise the user to the best package
            else if (bestPackage == costPackageA)
            {
               cout << "There is a better option." << endl;
               cout << "Package A will be more suited for your needs costing $";
               cout << bestPackage << endl;
            } // end inner switch else if (bestPackage == costPackageA) function

            else if (bestPackage == costPackageB)
            {
               cout << "There is a better option." << endl;
               cout << "Package B will be more suited for your needs costing $";
               cout << bestPackage << endl;
            } // end inner switch else if (bestPackage == costPackageB) function

      } // end switch function

   }// end first if function validating user's input

   // Validating user's input
   else
      cout << "Invalid Entry. Please enter a valid menu option and a positive number for minutes." << endl;

   system("pause");

   return 0;

}  // end function main