// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       9/24/18
// Assignment: HW 3 Excerise 2
// Compiler:   Visual C++ 2017

// Description:
// This program will calculate the monthly payment of a loan and
// display the values dealt with a loan.

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
   cout << fixed << setprecision(2);                                     // Allows for the output to be placed to two decimal places

   double loanAmount, annualInterestRate, monthlyInterestRate,           // Stores decimal values
          monthlyPayment, amountPaidBack, interestPaid,
          numeratorMonthlyPayment, denomenatorMonthlyPayment;

   int numberOfTerms;                                                    // Stores the integer value of months

   // Display a request of the loan amount and store it
   cout << "Please enter the amount of the loan:   ";
   cin >> loanAmount;

   // Display a request of the annual interest rate and store it
   cout << "Please enter the annual interest rate: ";
   cin >> annualInterestRate;

   // Calculate monthly interest rate and convert it from a percentage into a decimal value
   monthlyInterestRate = (annualInterestRate / 100) / 12;

   // Display a request for the number of payments and store it
   cout << "Please enter the number of payments:   ";
   cin >> numberOfTerms;

   // Calculate monthly payment
   numeratorMonthlyPayment = (monthlyInterestRate * pow((1 + monthlyInterestRate), numberOfTerms));

   denomenatorMonthlyPayment = (pow((1 + monthlyInterestRate), numberOfTerms) - 1);

   monthlyPayment = (numeratorMonthlyPayment / denomenatorMonthlyPayment) * loanAmount;

   //Calculate amount paid back
   amountPaidBack = monthlyPayment * numberOfTerms;

   //Calculate the interest being paid
   interestPaid = amountPaidBack - loanAmount;

   //Calculate monthly interest rate as a percentage
   monthlyInterestRate = monthlyInterestRate * 100;

   cout << endl;

   //Display values
   cout << "Loan Amount:              $" << setw(10) << loanAmount << endl;
   cout << "Monthly Interest Rate:     " << setw(9) <<monthlyInterestRate << "%" << endl;
   cout << "Number of Payments:        " << setw(10) << numberOfTerms << endl;
   cout << "Monthly Payments:         $" << setw(10) << monthlyPayment << endl;
   cout << "Amount Paid Back:         $" << setw(10) << amountPaidBack << endl;
   cout << "Interest Paid:            $" << setw(10) << interestPaid << endl;

   system("pause");

   return 0;
} // end function main