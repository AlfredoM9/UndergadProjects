// Author:     Alfredo Mejia
// Course:     CS 1336.003
// Date:       11/18/18
// Assignment: HW 8 Excersie 2
// Compiler:   Visual C++ 2017

/******************************************************************************* 
Description: This program will calculate the average of a group of test scores *
             where the lowest test score is dropped from the calculation.      *
********************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
void getScore(int & testScore);
void calcAverage(int testScore1, int testScore2, int testScore3, int testScore4, int testScore5);
int findLowest(int testScore1, int testScore2, int testScore3, int testScore4, int testScore5);

// main function
int main()
{
   // Variables for each test score
   int testScore1, testScore2, testScore3, testScore4, testScore5;

   // Call getScore function five times to get a test score 5 times
   // Pass by reference these variables will be changed
   getScore(testScore1);
   getScore(testScore2);
   getScore(testScore3);
   getScore(testScore4);
   getScore(testScore5);

   // Call calcAverage with arguments to calculate the average and display it
   calcAverage(testScore1, testScore2, testScore3, testScore4, testScore5);

   return 0;

} // end main function

// getScore: This function will display a prompt asking the user to enter a test score. It will then validate
// the data and because it is passed by reference it will change the variable's value in the main function
void getScore(int & testScore)
{
   // Display prompt and validate input
   do
   {
      cout << "Please enter a test score" << endl;
      cin >> testScore;
      if (testScore < 0 || testScore > 100)
         cout << "The test score should be between 0 and 100" << endl;
   } while (testScore < 0 || testScore > 100); // end do while loop
} // end getScore function

// calcAverage: This function will call the findLowest function passing arguments by value to determine the 
// lowest test score. It will then return the lowest and it allow for this function to calculate the average
// excluding the lowest and displaying the average in a fixed format.
void calcAverage(int testScore1, int testScore2, int testScore3, int testScore4, int testScore5)
{
   // Variables
   int lowestTestScore;
   double averageTestScore;

   // Call findLowest set to the variable lowestTestScore
   lowestTestScore = findLowest(testScore1, testScore2, testScore3, testScore4, testScore5);

   // Calculate average test score dropping the lowest
   averageTestScore = (testScore1 + testScore2 + testScore3 + testScore4 + testScore5 - lowestTestScore) / 4.0;

   // Display the average test score
   cout << "The following is the average test score from 5 test scores gathered with the lowest test score being dropped" << endl;
   cout << "Average test score: " << fixed << setprecision(2) << averageTestScore << endl;
} // end calcAverage function

// findLowest: This function will find the lowest test score and return the value of the lowest test score
int findLowest(int testScore1, int testScore2, int testScore3, int testScore4, int testScore5)
{
   // Set a variable
   int lowestTestScore = 1000;

   // Determine the lowest value
   if (testScore1 < lowestTestScore)
      lowestTestScore = testScore1;
   if (testScore2 < lowestTestScore)
      lowestTestScore = testScore2;
   if (testScore3 < lowestTestScore)
      lowestTestScore = testScore3;
   if (testScore4 < lowestTestScore)
      lowestTestScore = testScore4;
   if (testScore5 < lowestTestScore)
      lowestTestScore = testScore5;

   // Return lowest value
   return lowestTestScore;

} // end findLowest function
