// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       10/1/18
// Assignment: HW 4 Excerise 1
// Compiler:   Visual C++ 2017

// Description: This program will calculate the balance in a savings
// account after one year with a given formula.

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
   cout << fixed << setprecision(2);
   double amount, principal, interestRate, interestAmount;
   int timesCompounded;

   // Display a request for the balance of the account and store it
   cout << "Please enter the balance in the savings account: ";
   cin >> principal;

   // Display a request for the interest rate and store it
   cout << "Please enter the interest rate: ";
   cin >> interestRate;

   // Display a request for the times the interest will be compounded and store it
   cout << "Please enter the number of times the interest is compounded during a year: ";
   cin >> timesCompounded;

   cout << endl;

   // Convert the percentage into a decimal
   interestRate = interestRate / 100;

   // Calculate the balance in the account
   amount = principal * pow ( (1+ (interestRate / timesCompounded)), timesCompounded);

   // Convert the decimal into a percentage
   interestRate = interestRate * 100;

   // Calculate the amount of the interest only
   interestAmount = amount - principal;


   // Display values calculated and given
   cout << "Interest Rate:         " << setw(9) << interestRate << "%" << endl;
   cout << "Times Compounded:      " << setw(10) << timesCompounded << endl;
   cout << "Principal:            $" << setw(10) << principal << endl;
   cout << "Interest:             $" << setw(10) << interestAmount << endl;
   cout << "Amount in Savings:    $" << setw(10) << amount << endl;

   system("pause");

   return 0;

} // end function main