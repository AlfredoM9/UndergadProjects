#pragma once

#include <iostream>
#include <string>
using namespace std;

// Bank Class
class Bank
{
// Private members
private:
	int accountNum;
	string name;
	double balance;
	char accountType;

// Public functions
public:

	// Mutators
	void setAccountNum (int acctNum)
	{	accountNum = acctNum;	}

	void setName(string userName)
	{	name = userName;	}

	void setBalance(double total)
	{	balance = total;	}

	void setAcctType(char type)
	{	accountType = type;	}

	// Constructors
	Bank(int, string, double);
	Bank();

	// Other functions
	string withdraw(double);
	double deposit(double);

	// Accessors
	int getAccountNum()
	{	return accountNum;	}

	string getName()
	{	return name;	}

	double getBalance()
	{	return balance;	}

	char getAcctType()
	{	return accountType;	}
}; // end of Bank declaration

// Derived class Savings from parent Bank
class Savings : public Bank
{
// Private variables
private:
	double interestRate;
	int compoundPeriod;

// Public functions
public:
	// Constructors
	Savings(int, string, double, double, int, char s = 's');
	Savings();

	double addInterestRate(int);

	// Mutators
	void setInterestRate(double annualRate)
	{	interestRate = annualRate;	}

	void setCompoundPeriod(int days)
	{	compoundPeriod = days;	}

	// Accessors
	double getInterestRate()
	{	return interestRate;	}

	int getCompoundedPeriod()
	{	return compoundPeriod;	}
}; // end Savings declaration

// Derived class Checking from parent Bank
class Checking : public Bank
{
private:
	double minBalance, monthlyFee;

public:
	// Constructors
	Checking(int, string, double, const double, const double, char = 'c');
	Checking();

	// Mutators
	void setMinBalance(double min)
	{	minBalance = min;	}

	void setMonthlyFee(double fee)
	{	monthlyFee = fee;	}

	// Accessors
	double getMinBalance()
	{	return minBalance;	}

	double getMonthlyFee()
	{	return monthlyFee;	}
}; // end Checking declaration