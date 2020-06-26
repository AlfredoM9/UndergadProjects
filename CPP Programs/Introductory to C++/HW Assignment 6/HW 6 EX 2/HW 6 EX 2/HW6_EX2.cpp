// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       10/28/18
// Assignment: HW 6 Excersie 1
// Compiler:   Visual C++ 2017

/* Description: This program will ask the user for the daily sales for
five stores. It will then display a bar graph with asterisks comparing each
store's sales. Each asterisk will represent $100 of sales.
*/

#include <iostream>

using namespace std;

int main()
{
   // Variables used to store user's data
   int storeSales1, storeSales2, storeSales3, storeSales4,
       storeSales5;

   // Input validation: display prompt again if user enter negative values
   do
   {
      // Display a prompt asking for sales and store it for each store
      cout << "Enter today's sales for store 1: ";
      cin >> storeSales1;
      cout << "Enter today's sales for store 2: ";
      cin >> storeSales2;
      cout << "Enter today's sales for store 3: ";
      cin >> storeSales3;
      cout << "Enter today's sales for store 4: ";
      cin >> storeSales4;
      cout << "Enter today's sales for store 5: ";
      cin >> storeSales5;

      // If invalid display message for positive values
      if (storeSales1 < 0 || storeSales2 < 0 || storeSales3 < 0 || storeSales4 < 0 || storeSales5 < 0)
      {
         cout << endl;
         cout << "Please enter positive values for the day's sales" << endl;

      } // end if (storeSales1 < 0 || storeSales2 < 0 || storeSales3 < 0 || storeSales4 < 0 || storeSales5 < 0)

   } while (storeSales1 < 0 || storeSales2 < 0 || storeSales3 < 0 || storeSales4 < 0 || storeSales5 < 0);  // end do-while loop

   cout << endl;

   // Divide the sales by 100 to determine how many asterisks will be needed for each store
   int numberAsterisks1 = storeSales1 / 100,
       numberAsterisks2 = storeSales2 / 100,
       numberAsterisks3 = storeSales3 / 100,
       numberAsterisks4 = storeSales4 / 100,
       numberAsterisks5 = storeSales5 / 100;

   // Counter variables to help the loops terminate
   int countStore1, countStore2, countStore3,
       countStore4, countStore5;

   // Print header
   cout << "SALES BAR CHART" << endl;
   cout << "(Each * = $100)" << endl;

   // for loop for store 1, while the countstore variable controls the loop, up to the number of asterisks variable
   cout << "Store 1: ";
   for (countStore1 = 1; countStore1 <= numberAsterisks1; countStore1++)
   {
      cout << "*";
   }
   cout << endl;

   // for loop for store 2, while the countstore variable controls the loop, up to the number of asterisks variable
   cout << "Store 2: ";
   for (countStore2 = 1; countStore2 <= numberAsterisks2; countStore2++)
   {
      cout << "*";
   }
   cout << endl;

   // for loop for store 3, while the countstore variable controls the loop, up to the number of asterisks variable
   cout << "Store 3: ";
   for (countStore3 = 1; countStore3 <= numberAsterisks3; countStore3++)
   {
      cout << "*";
   }
   cout << endl;

   // for loop for store 4, while the countstore variable controls the loop, up to the number of asterisks variable
   cout << "Store 4: ";
   for (countStore4 = 1; countStore4 <= numberAsterisks4; countStore4++)
   {
      cout << "*";
   }
   cout << endl;

   // for loop for store 5, while the countstore variable controls the loop, up to the number of asterisks variable
   cout << "Store 5: ";
   for (countStore5 = 1; countStore5 <= numberAsterisks5; countStore5++)
   {
      cout << "*";
   }
   cout << endl;

   return 0;

} // end function main