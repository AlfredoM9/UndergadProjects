// Author:     Alfredo Mejia
// Course:     CS 1136.103
// Date:       11/16/18
// Assignment: Lab 9 Part 1
// Compiler:   Visual C++ 2017

/************************************************************************************************
Description: This program is for a company that sells spools of copper for $100 each.           *
             This program is going to read data from the user, reading the number of spools     *
             ordered, the number of spools currently in stock, and if there is any special      *
             shipping and handling costs. Then the program will calculate and display data. It  *
             will display the amount of spools ready to be shipped, the spools on the back order*
             it will display the subtotal of the spools, it will display the costs of the       *
             shipping and handling costs, and it will display the total charge which includes   *
             subtotal and the costs of shipping.                                                *
*************************************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

// Function protoypes
void readUserData(int & numSpoolsOrdered, int & numSpoolsInStock, double & shippingAndHandling);
void displayData(int numOfSpools, int numOfSpoolsOnBackOrder, double shippingAndHandling);

// main function
int main()
{
   // Varibles used to store data gathered from the readUserData function
   int spoolsOrdered, spoolsInStock;
   double costsOfShipping;

   // Use pass by reference
   readUserData(spoolsOrdered, spoolsInStock, costsOfShipping);

   // Execute the function
   displayData(spoolsOrdered, spoolsInStock, costsOfShipping);

   return 0;

} // end main function


// readUserData: This function will read in data from the user. It will read in the number of spools
// to be ordered, the number of spools in stock, and if there is any special shipping and handling costs.
void readUserData(int & numSpoolsOrdered, int & numSpoolsInStock, double & shippingAndHandling)
{
   // Variable to store the decision of the user of any special shipping costs
   char yesOrNo;

   // Display prompt and store spools ordered and validate input
   do
   {
      cout << "Spools to be ordered" << endl;
      cin >> numSpoolsOrdered;
      if (numSpoolsOrdered < 1)
         cout << "Spools order must be 1 or more" << endl;
   } while (numSpoolsOrdered < 1); // end do while (numSpoolsOrdered < 1)

   // Display prompt and store spools in stock and validate input
   do
   {
      cout << "Spools in stock" << endl;
      cin >> numSpoolsInStock;
      if (numSpoolsInStock < 0)
         cout << "Spools in stock must be 0 or more" << endl;
   } while (numSpoolsInStock < 0); // end do while (numSpoolsInStock < 0)

   // Display prompt if there is any special costs
   cout << "Special shipping and handling (y or n)" << endl;
   cin >> yesOrNo;

   // If yes, display prompt, store in special costs, and validate input
   if (yesOrNo == 'y')
   {
      cout << "Shipping and handling amount" << endl;
      cin >> shippingAndHandling;
      while (shippingAndHandling < 0)
      {
         cout << "The spool shipping and handling charge must be 0.0 or more" << endl;
         cout << "Shipping and handling amount" << endl;
         cin >> shippingAndHandling;
      } // end while (shippingAndHandling < 0)
   } // end if (yesOrNo == 'y')

   // Otherwise default shipping is 11.88 per spool
   else
      shippingAndHandling = 11.88;

} // end readUserData function


// displayData: This function will calculate the shipping and handling costs. It will calculate 
// the subtotal charges of the spools only. It will calculate the total charges which is the
// subtotal and the shipping costs. It will calculate the number of spools on the back order.
// And it will display all the data gathered: the spools ready to be shipped, spools on the back
// order, the subtotal, the shipping costs, and the total charges.
void displayData(int numOfSpools, int numOfSpoolsInStock, double shippingAndHandling)
{
   // Varibles for calculations
   double subtotalCharges, totalCharges;
   int numOfSpoolsOnBackOrder;

   // Calculate shipping and handling costs
   shippingAndHandling *= numOfSpoolsInStock;
   // Calculate subtotal
   subtotalCharges = numOfSpoolsInStock * 100.0;
   // Calculate total
   totalCharges = subtotalCharges + shippingAndHandling;
   // Calculate the number of spools on the back order
   numOfSpoolsOnBackOrder = numOfSpools - numOfSpoolsInStock;

   // Display data to a fixed amount of width spaces and a fixed format of two places after the decimal
   cout << "Spools ready to ship: " << numOfSpoolsInStock << endl;
   cout << "Spools on back-order: " << numOfSpoolsOnBackOrder << endl;
   cout << "Subtotal ready to ship: $" << setw(10) << fixed << setprecision(2) << subtotalCharges << endl;
   cout << "Shipping and handling:  $" << setw(10) << shippingAndHandling << endl;
   cout << "Total shipping charges: $" << setw(10) << totalCharges << endl;

} // end displayData function