// Alfredo Mejia
// Just trying to program something
// Visual Studios 2017
// Lab 11 from Fall 2018

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_SIZE = 21;

int readSquare(int square[MAX_SIZE][MAX_SIZE], string inputFileName);
bool validateSquare(const int square[MAX_SIZE][MAX_SIZE], int size);
void displaySquare();

int main()
{
   string fileName;
   cin >> fileName;

   int values[MAX_SIZE][MAX_SIZE];
   int dimensions;
   dimensions = readSquare(values, fileName);
   if (dimensions == 0)
      cout << "Could not open file" << endl;
   else

}

int readSquare(int square[MAX_SIZE][MAX_SIZE], string inputFileName)
{
   ifstream inputFile;
   inputFile.open(inputFileName);


}


