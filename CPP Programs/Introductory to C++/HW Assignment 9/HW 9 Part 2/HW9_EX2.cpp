// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       11/18/18
// Assignment: HW 9 Excersie 1
// Compiler:   Visual C++ 2017

/*
Description:

*/

#include <iostream>
#include <fstream>
using namespace std;

int main ()
{
   ifstream inputFile, inputFile2;

   inputFile.open("CorrectAnswers.txt");

   if (inputFile.fail())
      cout << "CorrectAnswers failed";

   inputFile2.open("StudentAnswers.txt");

   if (inputFile2.fail())
      cout << "StudentAnswers failed";

   const int ANSWERS = 20, STUDENTS = 15;
   char correctAnswers[ANSWERS];
   char studentAnswers[STUDENTS][ANSWERS];


   int i = 0, k = 0;
   while (i < ANSWERS && inputFile >> correctAnswers[i])
      i++;

   for (i = 0; i < STUDENTS; i++)
   {
      bool trueFalse = false;
      int j = 0;
      while (j < ANSWERS && inputFile2 >> studentAnswers[i][j])
      {
         j++;
         trueFalse = true;
      }

      if (trueFalse)
         k++;
   }
   
   int numberOfStudents = k;

   inputFile.close();
   inputFile2.close();

   int studentMax;
   int studentMin;
   int max = -1;
   int min = 110;
   int incorrectQuestion[ANSWERS];
   char incorrectAnswer[ANSWERS];

   for (i = 0; i < numberOfStudents; i++)
   {
      int percent;
      k = 0;
      int l = 0;
      cout << "Report for student " << (i + 1) << ":" << endl;
      cout << "---------------------" << endl;

      for (int j = 0; j < ANSWERS; j++)
      {
         if (correctAnswers[j] == studentAnswers[i][j])
            k++;
         else
         {
            incorrectQuestion[l] = j;
            incorrectAnswer[l] = studentAnswers[i][j];
            l++;
         }
      }
      percent = ((k * 100) / ANSWERS);
      cout << "Missed " << (ANSWERS - k) << " out of " << ANSWERS << " questions for " << percent << "% correct" << endl;
      cout << "Questions missed: " << endl;
      if (l == 0)
         cout << "NONE" << endl;
      else
      {
         for (int m = 0; m < l; m++)
         {
            cout << (incorrectQuestion[m] + 1) << "(" << incorrectAnswer[m] << "/" << correctAnswers[incorrectQuestion[m]] << ")";
            if (m < (l - 1))
               cout << ", ";
            cout << incorrectQuestion[m] << endl;
         }
         cout << endl;
      }
      cout << endl << endl;
      for (int n = 0; n < ANSWERS; n++)
      {
         cout << correctAnswers[n];

         cout << "          " << studentAnswers[i][n] << endl;
      }



      cout << endl;
      cout << endl;
      if (percent >= 70)
         cout << "This student passed the exam!" << endl;
      else
         cout << "This student failed the exam." << endl;

      
      if (percent > max)
      {
         max = percent;
         studentMax = i;
      }
      if (percent < min)
      {
         min = percent;
         studentMin = i;
      }
      cout << endl;
      cout << endl;
   }

   cout << "Student " << (studentMax + 1) << " had the best grade with " << max << "%." << endl;
   cout << "Student " << (studentMin + 1) << " had the worst grade with " << min << "%." << endl;
































































   /*
   char correctAnswers[ANSWERS];
   char studentAnswers[STUDENTS][ANSWERS];
   char fullAnswers[FULL_ANSWERS];

   bool trueFalse;
   int k = 0;
   for (int i = 0; i < STUDENTS; i++)
   {
      trueFalse = false;
      int j = 0;
      while (j < ANSWERS && inputFile2 >> studentAnswers[i][j])
      {
         j++;
         trueFalse = true;
      }

      if (trueFalse)
         k++;
   }

   int realStudents = k;

   for (int i = 0; i < realStudents; i++)
   {
      k = 0;
      cout << "Report for student " << (i + 1) << ":" << endl;
      cout << "---------------------" << endl;
      for (int j = 0; j < ANSWERS; j++)
      {
         cout << correctAnswers[j] << endl;
         cout << studentAnswers[i][j] << endl;
         if (correctAnswers[j] == studentAnswers[i][j])
         {
            k++;
         }
      }
      cout << "Student " << (i+1) << " missed " << k << " out of " << ANSWERS << endl;
   }

   int incorrectQuestion[ANSWERS];
   char incorrectAnswers[ANSWERS];
   for (int i = 0; i < realStudents; i++)
   {
      cout << "Report for student " << (i + 1) << ":" << endl;
      cout << "---------------------" << endl;
      for (int j = 0; j < ANSWERS; j++)
      {
         if (correctAnswers[j] != studentAnswers[i][j])
         {
            incorrectQuestion[k] = j;
            incorrectAnswers[j] = studentAnswers[i][j];
            k++;
         }
      }
      cout << "Missed " << k << " out of " << ANSWERS << " questions for " << (100 - ((k * 100) / ANSWERS)) << "% correct" << endl;
      cout << "Questions missed: ";
      for (int i = 0; i < k; i++)
      {
         cout << incorrectQuestion[i] << "(" << incorrectAnswers[i] << "/" << correctAnswers[i] << ")";
         if (i < (k - 1))
            cout << ", " << endl;
      }


   }

   */

   system("pause");

   return 0;
}