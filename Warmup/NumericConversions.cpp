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

int main() 
{
	cout << "Integer to String Conversion" << endl;
	int inputInteger = getInteger("Input: ");
	cout << "Converted: " << IntegerToString(inputInteger)<< endl;

	cout << endl;

	cout << "String to Integer Conversion" << endl;
	string inputString = getLine("Input: ");
	cout << "Converted: " << StringToInteger(inputString) << endl;

    return 0;
}
