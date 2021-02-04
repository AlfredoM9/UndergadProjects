#include <iostream>
#include <string>
#include "Bank.h"
using namespace std;

// Bank Class Constructor
Bank::Bank(int acctNum, string userName, double currentBalance)
{
	// Initializes all member variables with parameters
	accountNum = acctNum;
	name = userName;
	balance = currentBalance;
} // end Bank constructor

// Bank Class Constructor
Bank::Bank()
{
	// Initializes it to default values
	accountNum = 9999;
	name = "";
	balance = 0;
} // end Bank Constructor

// Bank's withdrawal function
string Bank::withdraw(double withdrawing)
{
	// Create a temporary string
	string tempMessage;

	// If the amount you want to withdraw is larger than the balance
	if (withdrawing > balance)
		// Store "insufficient balance"
		tempMessage = "Insufficient Balance";

	// Otherwise withdraw and subtract from balance
	else
	{
		balance -= withdrawing;
		tempMessage = to_string(balance);
	} // end else

	// return string
	return tempMessage;
} // end Bank::withdraw

// Bank's deposit function
double Bank::deposit(double depositing)
{
	// Add deposit amount and return new balance
	balance += depositing;
	return balance;
} // end Bank::deposit

// Saving's constructor
Savings::Savings(int acctNum, string userName, double total, double rate, int days, char saving)
{
	// Initializes all member variables with the parameters  
	setAccountNum(acctNum);
	setName(userName);
	setBalance(total);
	setInterestRate(rate);
	setCompoundPeriod(days);
	setAcctType(saving);
} // end Saving's constructor

// Saving's constructor
Savings::Savings()
{
	// Initialize all member variables to default values
	setAccountNum(9999);
	setName("");
	setBalance(0);
	setInterestRate(0);
	setCompoundPeriod(0);
	setAcctType('x');
} // end Saving's constructor

// Saving's add interest rate function
double Savings::addInterestRate(int daysEntered)
{
	// Compute the number of periods that have past
	int numOfPeriods = daysEntered / compoundPeriod;

	// Get the balance
	double tempBalance = getBalance();

	// Add interest rate for every period
	for (int count = 0; count < numOfPeriods; count++)
		tempBalance = tempBalance + (tempBalance*interestRate);

	// Set the new balance
	setBalance(tempBalance);

	// return new balance
	return tempBalance;
} // end Savings::addInterestRate

// Checking's constructor
Checking::Checking(int acctNum, string userName, double total, const double minTotal, const double fee, char checking) 
{
	// Initializes all member variables with the parameters
	setAccountNum(acctNum);
	setName(userName);
	setBalance(total);
	setMinBalance(minTotal);
	setMonthlyFee(fee);
	setAcctType(checking);
} // end Checking's constructor

// Checking's constructor
Checking::Checking()
{
	// Initializes all member variables with default values
	setAccountNum(9999);
	setName("");
	setBalance(0);
	setMinBalance(0);
	setMonthlyFee(0);
	setAcctType('x');
} // end Checking's constructor