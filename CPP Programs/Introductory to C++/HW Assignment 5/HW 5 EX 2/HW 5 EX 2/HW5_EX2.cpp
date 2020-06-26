// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       10/13/18
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
   double costPackage;
   int minutes;
   char usersChoice;

   cout << "Please select from one of the following packages (A, B, C)" << endl;
   cout << "Package A:   For $39.99 per month 450 minutes are provided. ";
   cout << "Additional minutes are" << endl << "$0.45 per minute" << endl << endl;
   cout << "Package B:   For $59.99 per month 900 minutes are provided. ";
   cout << "Additional minutes are" << endl << "$0.40 per minute" << endl << endl;
   cout << "Package C:   For $69.99 per month unlimited minutes provided." << endl;
   cin >> usersChoice;

   if ((usersChoice >= 'A' && usersChoice <= 'C') || (usersChoice >= 'a' && usersChoice <= 'c'))
   {
      cout << "Please enter the following minutes that will be used." << endl;
      cin >> minutes;

      if (minutes >= 0)
      {
         cout << fixed << setprecision(2);

         switch (usersChoice)
         {
            case 'A':
            case 'a':
               if (minutes <= 450)
                  cout << "Your monthly bill will be $39.99" << endl;

               else
               {
                  costPackage = (((minutes - 450)*0.45) + 39.99);
                  cout << "Your monthly bill will be $" << costPackage << endl;

                  if (costPackage > 59.99 && costPackage < 69.99)
                  {
                     cout << "There is a better option for you." << endl;
                     cout << "Package B would be more suited for your needs." << endl;
                  }

                  else if (costPackage >= 69.99)
                  {
                     cout << "There is a better option for you." << endl;
                     cout << "Package C would be more suited for your needs." << endl;
                  }

                  else
                     cout << "Great Job! This Package is well suited for your needs." << endl;
               }
              break;

            case 'B':
            case 'b':
               if (minutes <= 900)
               {
                  cout << "Your monthly bill will be $59.99" << endl;

                  if (minutes <= 494)
                  {
                     cout << "There is a better option for you." << endl;
                     cout << "Package A would be more suited for your needs." << endl;
                  }

                  else
                     cout << "Great Job! This package is well suited for your needs." << endl;

               }

               else
               {
                  costPackage = (((minutes - 900)*0.40) + 59.99);
                  cout << "Your monthly be will be $" << costPackage << endl;

                  if (costPackage < 69.99)
                     cout << "Great Job! This package is well suited for your needs." << endl;

                  else
                  {
                     cout << "There is a better option for you." << endl;
                     cout << "Package C would be more suited for your needs." << endl;
                  }
               }
              break;

            case 'C':
            case 'c':
               cout << "Your montly bill will be $69.99" << endl;

               if (minutes <= 494)
               {
                  cout << "There is a better option for you." << endl;
                  cout << " Package A would be more suited for your needs." << endl;
               }

               else if (minutes > 494 && minutes < 925)
               {
                  cout << "There is a better option for you." << endl;
                  cout << "Package B would be more suited for your needs." << endl;
               }

               else
                  cout << "Great Job! This package is well suited for you." << endl;
               break;
         }
      }

      else
         cout << "Please enter a positive number for minutes." << endl;
   }

   else
      cout << "Invalid Entry. Please run the program again and select from the following options given." << endl;
   system("pause");

   return 0;

}