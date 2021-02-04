// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       12/1/18
// Assignment: HW 9 Excersie 1
// Compiler:   Visual C++ 2017

/*
Description:

*/

#include <iostream>
#include <fstream>
using namespace std;

int searchList(int stdList[], int numElems, int value, int index[]);

int main()
{
   const int LSS_SIZE = 100, LST_SIZE = 50;
   
   ifstream inputFile, inputFile2;

   inputFile.open("LSStandard.txt");

   if (inputFile.fail())
      cout << "LSS Fail";

   inputFile2.open("LSTest.txt");

   if (inputFile2.fail())
      cout << "LST Fail";

   int LSSarray[LSS_SIZE];
   int LSTarray[LST_SIZE];

   int i = 0, j = 0;
   int LSSnum, LSTnum;
   
   while (i < LSS_SIZE && inputFile >> LSSarray[i])
      i++;

   LSSnum = i;
   cout << LSSnum << endl;

   while (j < LST_SIZE && inputFile2 >> LSTarray[j])
      j++;

   LSTnum = j;
   cout << LSTnum << endl;
/*
   for (i = 0; i < LSSnum; i++)
      cout << LSSarray[i] << endl;

   cout << endl << endl << endl;

   for (j = 0; j < LSTnum; j++)
      cout << LSTarray[j] << endl;

   bool notMatch;
   for (j = 0; j < LSTnum; j++)
   {
      notMatch = true;
      cout << "Number " << (j+1) << "(" << LSTarray[j] << ")";
      for (i = 0; i < LSSnum; i++)
      {
         if (LSTarray[j] == LSSarray[i])
         {
            cout << " was located at index " << i << endl;
            notMatch = false;
            break;
         }
      }
      if (notMatch)
         cout << " was not in the file" << endl;
   }
*/
   int k;
   const int INDEX_SIZE = 25;
   int indexArray[INDEX_SIZE];
   int num;
   for (j = 0; j < LSTnum; j++)
   {
      cout << "Number " << (j + 1) << " (" << LSTarray[j] << ")";
      num = searchList(LSSarray, LSSnum, LSTarray[j], indexArray);

      if (num == -1)
         cout << " was not in the file" << endl;
      else
      {
         cout << " was located at index ";
         for (k = 0; k < num; k++)
            cout << indexArray[k] << " ";
         cout << endl;
      }

   }

   system("pause");
   return 0;

}

int searchList(int stdList[], int numElems, int value, int index [])
{
   int i, j = 0;
   for (i = 0; i < numElems; i++)
   {
      if (stdList[i] == value)
      {
            index[j] = i;
            j++;
      }
   }
   if (j > 0)
      return j;
   else
      return -1;
}