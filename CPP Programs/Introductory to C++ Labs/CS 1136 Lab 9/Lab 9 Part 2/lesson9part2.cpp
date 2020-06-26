// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       11/16/18
// Assignment: Lab 9 Part 2
// Compiler:   Visual C++ 2017

/******************************************************************************
Description: 
*******************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

double calculateFutureValue(double presentValue, double interestRate, int months);
unsigned int readData(ifstream & inputFile, double & presentValue, double & interestRate, int & months);
void displayData(ofstream & outputFile, double futureValue, double presentValue, double interestRate, int months);

int main()
{
   string fileName;
   cin >> fileName;

   ifstream inputFile;
   inputFile.open(fileName);

   if (inputFile.fail())
      cout << "File \"" << fileName << "\" could not be opened" << endl;
   else
   {
      double presentValue, interestRate;
      int months;
      ofstream outputFile;
      outputFile.open("ouput.xls");

      int returnValue;
      do
      {
         if (outputFile.fail())
         {
            cout << "File \"output.xls\" could not be opened" << endl;
            inputFile.close();
         }
         else
         {
            outputFile << "FutureValue\tPresent Value\tMonthly Interest\tMonths" << endl;
            returnValue = readData(inputFile, presentValue, interestRate, months);

            if (returnValue == 2)
            {
               cout << fixed << setprecision(1);
               cout << presentValue << " " << interestRate << " " << months;
               cout << "One or more of the above values are not greater than zero" << endl;
            }

            else
            {
               double futureValue;
               futureValue = calculateFutureValue(presentValue, interestRate, months);
               displayData(outputFile, futureValue, presentValue, interestRate, months);
            }
         }
      } while (returnValue != 0);

      inputFile.close();
      outputFile.close();

   }


   return 0;
}

unsigned int readData(ifstream & inputFile, double & presentValue, double & interestRate, int & months)
{
   double value;
   int number;
   for (number = 1; inputFile >> value; number++)
   {
      if (number == 1)
         presentValue = value;
      else if (number == 2)
         interestRate = value;
      else if (number == 3)
         months = value;
   }

   if (number != 4)
      return 0;
   else if (presentValue > 0 && interestRate > 0 && months > 0)
      return 1;
   else if (presentValue <= 0 || interestRate <= 0 || months <= 0)
      return 2;


}

double calculateFutureValue(double presentValue, double interestRate, int months)
{
   interestRate /= 100;
   double futureValue = presentValue * pow((1 + interestRate), months);
   return futureValue;
}

void displayData(ofstream & outputFile, double futureValue, double presentValue, double interestRate, int months)
{
   outputFile << fixed << setprecision(2);
   outputFile << futureValue << "\t" << presentValue << "\t" << interestRate << "\t" << months << endl;
}