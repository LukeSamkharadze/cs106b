/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <cmath>

#include "simpio.h"
#include "console.h"

using namespace std;

string IntegerToString(int n)
{
	// for negative values
	if(n < 0)
		return string() + "-" + IntegerToString(-n);

	// base case
	if(n < 10)
		return string() + char(n + '0');

	// main case
	return IntegerToString(n/10) + IntegerToString(n%10);
}

int StringToInteger(string str)
{
	// for negative values
	if(str[0] == '-')
		return -StringToInteger(str.substr(1,str.length()));

    // base case
	if(str.length() == 1)
		return str[0] - '0';

	// main case
	return StringToInteger(str.substr(0,str.length()-1)) * 10 + // except last digit
		StringToInteger(str.substr(str.length()-1,str.length())); // last digit
}

int HexadecimalToInteger(string str)
{
	int integer = 0;
	bool isNegative = false;

	if(str[0] == '-')
	{
		str = str.substr(1,str.length());
		isNegative = true;
	}

	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] >= '0' && str[i] <= '9')
			integer += (str[i]-'0') * pow(16,(double)str.length()-i-1);
		else
			integer += (str[i]-'7') * pow(16,(double)str.length()-i-1);
	}
	
	return -1 * (isNegative*2-1) * integer;
}

string IntegerToHexadecimal(int n)
{
	if(n < 0)
		return string() + "-" + IntegerToHexadecimal(-n);
	
	if(n/16 == 0)
	{
		if(n%16 < 10)
			return IntegerToString(n%16);
		else
			return string() + char('A' + n%16 - 10);
	}
	else
	{
		char hexCharacter;

		if(n%16 < 10)
			hexCharacter = n%16 + '0';
		else
			hexCharacter = 'A' + n%16 - 10;

		return IntegerToHexadecimal(n/16) + hexCharacter;
	}
}

int main() 
{
	cout << "Integer to String Conversion" << endl;
	int inputInteger = getInteger("Input: ");
	cout << "Converted: " << IntegerToString(inputInteger)<< endl;

	cout << endl;

	cout << "String to Integer Conversion" << endl;
	string inputString = getLine("Input: ");
	cout << "Converted: " << StringToInteger(inputString) << endl;

	cout << endl;

	cout << "Hexadecimal to Integer Conversion" << endl;
	inputString = getLine("Input: ");
	cout << "Converted: " << HexadecimalToInteger(inputString) << endl;

	cout << endl;

	cout << "Integer to Hexadecimal Conversion" << endl;
	inputInteger = getInteger("Input: ");
	cout << "Converted: " << IntegerToHexadecimal(inputInteger) << endl;


    return 0;
}