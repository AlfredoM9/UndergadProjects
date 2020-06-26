#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isPalindrome(string);
string onlyCharacters(string);

int main()
{
	string input;
	do
	{
		string tempString;
		getline(cin, tempString);
		input = onlyCharacters(tempString);
		bool palindrome = isPalindrome(input);
		if (!(input == "*"))
		{
			if (palindrome)
				cout << "\"" << tempString << "\" is a palindrome" << endl;
			else
				cout << "\"" << tempString << "\" is not a palindrome" << endl;
		}
	} while (!(input == "*"));

	cout << "The program has ended" << endl;
	system("pause");
	return 0;
}

bool isPalindrome(string input)
{
	bool palindrome;
	if (input.length() == 0 || input.length() == 1)
		palindrome = true;

	else if (input[0] == input[input.length() - 1])
		palindrome = isPalindrome(input.substr(1, input.length() - 2));

	else
			palindrome = false;

	return palindrome;
}

string onlyCharacters(string tempString)
{
	if (tempString.length() == 0 || tempString.length() == 1)
		return tempString;
	else
	{
		int newSize = 0, count2 = 0;
		for (int count = 0; count < tempString.length(); count++)
		{
			if (isalnum(tempString[count]))
			{
				tempString[count2] = tolower(tempString[count]);
				count2++, newSize++;
			}
		}

		tempString.resize(newSize);
		return tempString;
	}
}