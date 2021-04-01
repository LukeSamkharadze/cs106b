/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"

using namespace std;

bool isSubsequence(string text, string subsequence)
{
	if(subsequence == "")
		return true;

	if(subsequence.length() > text.length())
		return false;

	if(subsequence[0] == text[0])
		return isSubsequence(text.substr(1), subsequence.substr(1));

	return isSubsequence(text.substr(1), subsequence);
}

int main() 
{
	cout << isSubsequence("zdarova","rv") << endl;

    return 0;
}