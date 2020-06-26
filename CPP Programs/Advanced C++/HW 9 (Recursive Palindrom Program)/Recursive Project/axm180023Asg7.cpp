/***************************************************************************
Author:      Alfredo Mejia                                                 *
Course:      CS 1337.009                                                   *
Date:        4/18/19                                                       *
Assignment:  HW Assignment 7 (Recursive Palindrome)                        *
Compiler:    Visual Studios C++ 2017                                       *
Description: This program will accept a string from the user.              *
			 The program will ignore any white spaces, punctuation,        *
			 or any other character that is not digits or letters.         *
			 From the digits and letters present it will determine         *
			 if it is palindrome or not. It will display what the user     *
			 entered and show if it is palindrome. It will repeat until    *
			 the user enters a single asterisk.                            *
****************************************************************************/
#include <iostream>
#include <string>
#include <cctype>

using namespace std; 

// Function Prototypes
string onlyCharacters(string);
bool isPalindrome(string);

// main function
int main()
{
	// create a string for input
	string input;

	do
	{
		// Display Header
		cout << "Please enter a word/phrase and it will determine if it is a palindrome (enter \"*\" to exit program)" << endl;

		// Create a temporary string for input
		string tempString;

		// Get the whole line of input
		getline(cin, tempString);

		// Call the onlyCharacters function: this will return only valid characters, all lowercase
		input = onlyCharacters(tempString);

		// Determine if the filtered string is palindrome
		bool palindrome = isPalindrome(input);

		// If the user didn't insert "*"
		if (!(input == "*"))
		{
			// If it is palindrome display message, display other message otherwise
			if (palindrome)
				cout << "\"" << tempString << "\" is a palindrome" << endl;
			else
				cout << "\"" << tempString << "\" is not a palindrome" << endl;
		} // end if
		cout << endl;
	} while (!(input == "*")); // while the user doesn't enter "*"

	cout << "The program has ended" << endl;

	system("pause");

	return 0;
} // end main

/*******************************************************************************************************************
FUNCT: onlyCharacters
DESCR: It will accept a string. If the length is 0 or 1 it will automatically return the string because it is
	   automatically a palindrome and it doesn't need filtering. However if it is longer then it will determine
	   the characters that are valid and send them to the front of the string in the order they come. It will then
	   truncate the string where the invalid characters start from the back. It will then return the string. If no
	   valid characters are present an empty string is return thus making it a palindrome.
*********************************************************************************************************************/
string onlyCharacters(string tempString)
{
	// If the length is zero or one then it is automatically palindrome so no need to filter it
	if (tempString.length() == 0 || tempString.length() == 1)
		return tempString;

	// Otherwise
	else
	{
		// Create variables for the index of the new string and a variable to hold the new string size
		int newSize = 0, newCount = 0;

		// Go through every character in the string
		for (int count = 0; count < tempString.length(); count++)
		{
			// If it is a letter or digit
			if (isalnum(tempString[count]))
			{
				// Send it to the front of the string
				tempString[newCount] = tolower(tempString[count]);

				// Increment variables
				newCount++, newSize++;
			} // end if
		} // end for

		// Resize the string to only include valid characters
		tempString.resize(newSize);

		// return the string
		return tempString;
	} // end else
} // end onlyCharacters

/*************************************************************************************************************************
FUNCT: isPlaindrome
DESCR: The function will accept a string which has been already filtered. If the length is 0 or 1 then it
	   is automatically a palindrome. If it is longer it will check the starting point and end point of the
	   string to see if they match. If they do, then the function is called again but this time with the end
	   points being taken off (because we already analyzed that portion) and only the middle section being passed.
	   The same process repeats. It goes on to make the string smaller and smaller. If at some point the end points
	   don't match then it becomes false. Otherwise it will continue to become true. Then the boolean value is returned.
***************************************************************************************************************************/
bool isPalindrome(string input)
{
	// Create boolean variable
	bool palindrome;

	// If the length is 1 or 0 then automatic palindrome
	if (input.length() == 0 || input.length() == 1)
		palindrome = true;

	// Otherwise if the ending and starting character are equal then call isPalindrome function again to analyze the characters in between
	else if (input[0] == input[input.length() - 1])
		palindrome = isPalindrome(input.substr(1, input.length() - 2));

	// If they don't equal then it isn't palindrome
	else
		palindrome = false;

	// return boolean variable
	return palindrome;
} // end isPalindrome
