/**********************************************************************************
                                                                                  *
Author:     Alfredo Mejia                                                         *
Course:     CS 1337.009                                                           *
Date:       2/3/19                                                                *
Assignment: HW Assignment 2                                                       *
Compiler:   Visual Studios C++ 2017                                               *
                                                                                  *
Description: This program will ask the user for a password and determine          *
             if the password is valid or not following certain criteria.          *
             If the password is valid the program will display a message          *
             displaying the outcome and ask again for another password            *
             from the user. If the password is invalid a message will be          *
             displayed about the error and it will ask the user for another       *
             password. The program will continue this process until the user      *
             quits the program by pressing "*" (asterik).                         *
                                                                                  *
**********************************************************************************/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function prototypes
string userPassword();
bool lengthCriteria(int length);
bool characterCriteria(string password);
void displayResults(string password, bool lengthValid, bool charactersValid);

// main function
int main()
{
   // Variable used to determine the iteration of the loop
   bool endProgram;
   do
   {
      // Always initialized to false b/c program doesn't know if user wants to end program
      endProgram = false;

      // Call userPassword and return a string that contains the password
      string password = userPassword();

      // If the string is not an asterik or longer than 1 it means a password was entered
      if (password != "*" || password.length() > 1)
      {
         // Call lengthCriteria to determine if the password's length is valid
         bool lengthValid = lengthCriteria(password.length());

         // Call charactersValid to determine if the password has the character criteria
         bool charactersValid = characterCriteria(password);

         // Call displayResults and pass the boolean values to determine the validity of the password
         displayResults(password, lengthValid, charactersValid);
         cout << endl;

      } // end if (password != "*" || password.length() > 1)

      // If the asterik is entered display message and end loop
      else
      {
         endProgram = true;
         cout << "The program has ended" << endl;
      } // end else

   } while (!endProgram); // end do-while

   return 0;
} // end main 

/*********************************************************************************
Fnction: userPassword
Descrpt: This fucntion will display a prompt to the user to enter a password
         or an asterik to end the program. The data will be stored in a 
         string and will be returned.
**********************************************************************************/
string userPassword()
{
   // Create variable, display message, store data
   string password;
   cout << "Please enter a password or enter \"*\" to end the program" << endl;
   cin >> password;

   // Return the data entered
   return password;

} // end userPassword

/**********************************************************************************
Fnction: lengthCriteria
Descrpt: The function will accept an int being the length of the string to
         determine if the password has the minimum amount of characters and
         doesn't surpass the maximum amount of characters. If the password
         does not meet the length criteria the function will return false;
         however, if it meets the length criteria it will return true.
***********************************************************************************/
bool lengthCriteria(int length) 
{
   bool valid;

   // Determine if it meets length criteria
   if (length >= 12 && length <= 50)
      valid = true;
   else
      valid = false;

   // Return the boolean value true = meets and false = doesn't meet
   return valid;

} // end lengthCriteria

/*************************************************************************************
Fnction: characterCriteria
Descrpt: This function will accept a string being the password entered by the 
         user. It will create variables all initalized and it will create an array
         holding special characters that must be included in the password (at least
         one). It will use a loop to check every character of the string and
         determine if it has an upper case letter, lower case, and a digit. If 
         the string does have one, the corresponding variable will be assigned to
         true. If the character is a punctuation it will use a nested loop to compare 
         the character of the string to the whole array of special characters. If
         at least one matches then it has meet the requirement for the special characters,
         however if an invalid character is inserted the password would be invalid. Thus
         the function will return true for all being valid and false for at least one
         being invalid (false).
**************************************************************************************/
bool characterCriteria(string password)
{
   // Variables and array initialized to determine the validity
   bool upperCase = false, lowerCase = false, digit = false, specialChar = false, validChar = true;
   const int NUM_SPECIAL = 15;
   const char specialCharacters[NUM_SPECIAL] = { '!', '@', '#', '$', '%', '^', '&', '(', ')', '[', ']', ',', '.', ':', ';' };

   // For loop used to compare a single character at a time
   for (int count = 0; count < password.length(); count++)
   {
      // If the character is upper case, set the variable to true
      if (isupper(password[count]))
         upperCase = true;

      // If the character is lower case, set the variable to true
      else if (islower(password[count]))
         lowerCase = true;

      // If the character is a digit, set the variable to true
      else if (isdigit(password[count]))
         digit = true;

      // If the character is other than a letter or a num
      else if (ispunct(password[count]))
      {
         bool invalidChar = true;

         // For loop to compare the single element to the special char array
         for (int count2 = 0; count2 < NUM_SPECIAL; count2++)
         {
            // If it finds a matching assign values to the boolean variables
            if (password[count] == specialCharacters[count2])
            {
               specialChar = true;
               invalidChar = false;

            } // end if (password[count] == specialCharacters[count2])

         } // end for (int count2 = 0; count2 < NUM_SPECIAL; count2++)

         // If no matching character then invalid character
         if (invalidChar)
            validChar = false;

      } // else if (ispunct(password[count]))

   } // end for (int count = 0; count < password.length(); count++)

   // If all the variables are true means it meets all criteria and return true otherwise return false
   if (upperCase && lowerCase && digit && specialChar && validChar)
      return true;
   else
      return false;
} // end character criteria

/********************************************************************************************************
Fnction: displayResults
Descrpt: The function will accept the string and two boolean variables. The boolean variables are 
         going to hold the value if the password meets the length's criteria and the character's
         criteria. If both booleans are true then display the password inserted and display
         a message saying the password is valid. If any of the booleans is false then it is invalid
         and display message about the error of the password.
*********************************************************************************************************/
void displayResults(string password, bool lengthValid, bool charactersValid)
{
   // If both true display password is valid
   if (lengthValid && charactersValid)
      cout << "\"" << password << "\" is a valid password." << endl;

   // If invalid display message
   if (!lengthValid)
      cout << "The password's length should be a minimum of 12 characters long and no more than 50 characters long" << endl;

   // If invalid display message
   if (!charactersValid)
      cout << "The password should contain at least one upper case letter, one lower case letter, one digit,"
           << " and one special character from the following !@#$%^&()[],.:;" << endl;
} // end displayResults

