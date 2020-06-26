/**********************************************************************************
                                                                                  *
Author:     Alfredo Mejia                                                         *
Course:     CS 1337.009                                                           *
Date:       2/24/19                                                               *
Assignment: HW Assignment 2                                                       *
Compiler:   Visual Studios C++ 2017                                               *
                                                                                  *
Description: This program will take in a C-string and then encrypt it             *
             by adding one to the first element, two to the second element,       *
             three to the third, and so on until it reaches the 10th element.     *
             For the 11th it will once again start by adding one and continuing   *
             the process for each ASCII value of the character. It will then      *
             print the encrypted version. Then it will decrypt the string of      *
             characters to its original version and display it                    *
                                                                                  *
**********************************************************************************/
#include <iostream>
using namespace std;

bool getString(char string[], const int MAX_CHARS);
void encrypt(char string[]);
void decrypt(char string[]);

int main()
{
   // Declare char array & size
   const int MAX_CHARS = 201;
   char string[MAX_CHARS] = { 0 };

   // Call getString and returns true/false if there is an single asterisk
   bool endProgram = getString(string, MAX_CHARS);

   // If asterisk then end program
   if (endProgram)
      cout << "The program has ended" << endl;
   else
   {
      // Encrypt string and display it
      encrypt(string);
      cout << "The string entered encrypted:" << endl << string << endl;

      // Decrypt string and display it
      decrypt(string);
      cout << "The string entered decrypted:" << endl << string << endl;

   } // end else

   system("pause");
   return 0;
} // end main

/***********************************************************************************************
Funct: getString
Descr: Obtains the C-string from the user and returns if there is a single asterisk to the end
       the program or not.
************************************************************************************************/
bool getString(char string[], const int MAX_CHARS)
{
   // Display and obtain the string of characters
   cout << "Please enter a string of characters (maximum of 200 characters) or enter '*' to stop the program" << endl;
   cin.get(string, MAX_CHARS);

   // Determine the size of string
   int size = 0;
   while (string[size] != 0)
      size++;

   // If input is a single asterisk
   if (string[0] == '*' && size == 1)
      return true;
   else
      return false;
} // end getString

/*****************************************************************************************************
Func: encrypt
Desc: The function adds one to the first element, adds two the second element, until it reaches 10.
      Then for the 11th element it starts again by adding one and so on. Each 1st element starts by
      getting added one.
******************************************************************************************************/
void encrypt(char string[])
{
   // Determine the size of the string
   int size = 0;
   while (string[size] != 0)
      size++;

   // for loop to add the necessary number to the element
   int addNum;
   for (int count = 0; count < size; count++)
   {
      if (count % 10 == 0)
         addNum = 1;
      string[count] += addNum++;
   } // end for loop
} // end encrypt

/****************************************************************************************
Func: decrypt
Desc: The function will now restore the string to the orginal version by subtracting
      the amount it added to the element.
******************************************************************************************/
void decrypt(char string[])
{
   // Determine size of the string
   int size = 0;
   while (string[size] != 0)
      size++;

   // for loop to subtract the necessary amount to each element
   int addNum;
   for (int count = 0; count < size; count++)
   {
      if (count % 10 == 0)
         addNum = 1;
      string[count] -= addNum++;
   } // end for loop
} // end decrypt