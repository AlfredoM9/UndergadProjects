// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       9/28/18
// Assignment: Lab 3 Part 3

/* Description: This program will read in the number of
 share of stocks, a stock's purchase price, and a stock's
 sales price. Then the program will calculate the cost of stock
 the cost of commision, and then the total cost. Plus it will calculate
 income from stock, the cost of commision, and the total income.
 Finally it will calculate the difference between the cost of the stock
 and the income of the stock.
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()

{
   cout << fixed << setprecision(2);                                // Allows for the outcome to be set to two decimal places

   int numberOfShares;                                              // Stores whole numbers

   double stockPurchasePrice, stockSalesPrice,                      // Stores decimal values
      costOfStock, commission4Purchase, totalCost,
      incomeStock, commission4Sale, totalIncome, profit;

   const double commissionPercentage = 0.035;                       // Allows for the commission rate to be constant

   string companyName;                                              // Allows for a string to be a variable

   // Stores values of the number of shares, stock price when purchased and sold
   getline(cin, companyName);
   cin >> numberOfShares >> stockPurchasePrice >> stockSalesPrice;

   // Calculates cost of stock, the commission fee, and total cost
   costOfStock = numberOfShares * stockPurchasePrice;
   commission4Purchase = costOfStock * commissionPercentage;
   totalCost = costOfStock + commission4Purchase;

   // Calculates income of the stock, the commission fee, and total income w/ fee
   incomeStock = numberOfShares * stockSalesPrice;
   commission4Sale = incomeStock * commissionPercentage;
   totalIncome = incomeStock - commission4Sale;

   // Calculates the profit taken into account the cost and income
   profit = totalIncome - totalCost;

   // Displayes company's name and number of shares
   cout << "Company: " << companyName << endl;
   cout << "Share: " << numberOfShares << endl;
   cout << endl;

   // Displays stock's purchase price, cost of stock, commission fee, and total cost
   cout << "Purchase/share: $" << stockPurchasePrice << endl;
   cout << "Cost of stock: $" << costOfStock << endl;
   cout << "Cost of commision: $" << commission4Purchase << endl;
   cout << "Toal cost: $" << totalCost << endl;

   cout << endl;

   // Displays stock's sales price, income from the stock, commission fee, and total income
   cout << "Sale/share: $" << stockSalesPrice << endl;
   cout << "Income from stock: $" << incomeStock << endl;
   cout << "Cost of commission: $" << commission4Sale << endl;
   cout << "Total income: $" << totalIncome << endl;

   cout << endl;

   // Displays the total profit from cost and income
   cout << "Gain or loss: $" << profit << endl;
   
   system("pause");
   return 0;


}
