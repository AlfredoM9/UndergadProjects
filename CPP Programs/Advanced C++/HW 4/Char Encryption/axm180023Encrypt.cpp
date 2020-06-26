/**********************************************************************************
                                                                                  *
Author:     Alfredo Mejia                                                         *
Course:     CS 1337.009                                                           *
Date:       2/24/19                                                               *
Assignment: HW Assignment 2                                                       *
Compiler:   Visual Studios C++ 2017                                               *
                                                                                  *
Description:                                                                      *
                                                                                  *
**********************************************************************************/

#include <iostream>

using namespace std;

bool getString(char string[], const int MAX_CHARS);
void encrypt(char string[], int &size);
void decrypt(char string[], int size);
int main() 
{
   const int MAX_CHARS = 200;
   char string[MAX_CHARS] = { 0 };
   bool endProgram = getString(string, MAX_CHARS);
   
   if (endProgram)
      cout << "The program has ended" << endl;
  
   else
   {
      int numChars = 0;
      encrypt(string, numChars);
      cout << "The string entered encrypted:" << endl << string << endl;
      decrypt(string, numChars);
      cout << "The string entered decrypted:" << endl << string << endl;
   }

   system("pause");
   return 0;
}

bool getString(char string[], const int MAX_CHARS)
{
   cout << "Please enter a string of characters or enter '*' to stop the program" << endl;
   cin.get(string, MAX_CHARS);

   if (string[0] == '*')
      return true;
   else
      return false;
}

void encrypt(char string[], int &size)
{
   while (string[size] != 0)
      size++;
   
   int addNum;
   for (int count = 0; count < size; count++)
   {
      if (count % 10 == 0)
         addNum = 1;
      string[count] += addNum++;
   }

   return;
}

void decrypt(char string[], int size)
{
   int addNum;
   for (int count = 0; count < size; count++)
   {
      if (count % 10 == 0)
         addNum = 1;
      string[count] -= addNum++;
   }
}