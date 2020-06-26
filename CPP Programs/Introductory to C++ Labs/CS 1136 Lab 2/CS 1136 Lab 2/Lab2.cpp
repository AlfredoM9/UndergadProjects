// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       9/23/18
// Assignment: Lab 2
// Compiler:   Visual C++ 2017



#include <iostream>
using namespace std;

int main()
{
   // start of lab 2 part 1

   /* Description: This program will
   compute the total sales tax on a
   $95 purchase. Assuming the state
   sales tax is 6% and the county
   sales tax is 2%
*/

   double pricePurchase, stateSalesTax, countySalesTax, totalSalesTax;
   pricePurchase = 95.00,             // The price of purchase without taxes
      stateSalesTax = 0.06,             // State's sales tax
      countySalesTax = 0.02,             // County's sales tax

// Calculate total sales tax of the price purchase
totalSalesTax = pricePurchase * (stateSalesTax + countySalesTax);

   //Display total sales tax being added to the price purchase
   cout << totalSalesTax << endl;



   cout << endl;
   // start of lab 2 part 2
   cout << endl;

   // Description: Calculate rising ocean levels based on the estimated rate of rising (in millimeters). This 
// estimated value is read from cin into variable risingLevel. Then it will calculate rising ocean levels
// over 5 years, 10 years, and 50 years.

   double risingLevel, riseLevel_5years, riseLevel_10years, riseLevel_50years;

   // read in the estimated rising ocean level
   cin >> risingLevel;

   // Display estimated rising level
   cout << "Level: " << risingLevel << endl;

   //Calculate rising level in 5 years
   riseLevel_5years = risingLevel * 5;

   //Display rising level in 5 years
   cout << "Years: 5, Rise: " << riseLevel_5years << endl;

   //Calculate rising level in 10 years
   riseLevel_10years = (risingLevel * 10);

   //Display rising level in 10 years
   cout << "Years: 10, Rise: " << riseLevel_10years << endl;

   //Calculate rising level in 50 years
   riseLevel_50years = risingLevel * 50;

   //Display rising level in 50 years
   cout << "Years: 50, Rise: " << riseLevel_50years << endl;








   cout << endl;
   //Start of lab 2 part 3
   cout << endl;

   //Display a rectangle (10x10) with @ characters
   cout << "@@@@@@@@@@" << endl;
   cout << "@        @" << endl;
   cout << "@        @" << endl;
   cout << "@        @" << endl;
   cout << "@        @" << endl;
   cout << "@        @" << endl;
   cout << "@        @" << endl;
   cout << "@        @" << endl;
   cout << "@        @" << endl;
   cout << "@@@@@@@@@@" << endl;

   //Skip a line for readability
   cout << endl;

   // Display a triangle (with a base of 11 characters) with % characters
   cout << "     %     " << endl;
   cout << "    % %    " << endl;
   cout << "   %   %   " << endl;
   cout << "  %     %  " << endl;
   cout << " %       % " << endl;
   cout << "%%%%%%%%%%%" << endl;

   system("pause");

   return 0; 

} // end function main