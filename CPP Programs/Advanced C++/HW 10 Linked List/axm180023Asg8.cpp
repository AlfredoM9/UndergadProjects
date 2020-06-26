#include <iostream>
#include <string>
#include <fstream>
#include "LinkedList.h"

using namespace std;

// Functions
string displayMenu(ifstream&);
void getData(ifstream&);

// main function
int main()
{
	// Hold file name
	string fileName;
	do
	{
		// Create an input stream object
		ifstream inputFile;

		// Call displayMenu function and returns input
		fileName = displayMenu(inputFile);

		// If user doesn't want to exit
		if (fileName != "*")

			// Get the data
			getData(inputFile);

	} while (fileName != "*"); // Exit when user enters an asterisk

	cout << "The program has ended" << endl;

	system("pause");

	return 0;
} // end main

/************************************************************************************************************************
FUNCT: displayMenu
DESCR: This function accepts a reference object of ifstream. It will ask for a file name and it will validate that it 
	   either entered a valid file name or an asterisk to exit the program. Once the input has been validated it will 
	   return the input.
*************************************************************************************************************************/
string displayMenu(ifstream & inputFile)
{
	// Variables for input and a flag for the loop
	string tempFile;
	bool invalid = true;
	do
	{
		// Display prompt
		cout << "Please enter a file name or enter \"*\" to exit the program." << endl;
		cin >> tempFile;

		// If user wants to exit
		if (tempFile == "*")
			invalid = false;

		// Otherwise check if it's a valid file name
		else
		{
			inputFile.open(tempFile);

			if (inputFile)
				invalid = false;
			else
				cout << "An error has occurred." << endl;
		} // end else
	} while (invalid); // while input is not valid

	// return user input
	return tempFile;
} // end displayMenu

/******************************************************************************************************
FUNCT: getData
DESCR: The function will accept the ifstream object. It will then pass every number to the list.
	   While at the same time sorting it using insertion sort. It will then display the numbers
	   and delete the list.
********************************************************************************************************/
void getData(ifstream & inputFile)
{
	// Create object
	LinkedList list;

	// Temporary variable to hold the data
	double num;

	// While there is data in the file
	while (inputFile >> num)
		list.insertNode(num);

	// Display and delete
	list.displayList();
	list.destroyList();

} // end getData