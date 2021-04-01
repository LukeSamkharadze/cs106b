/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <exception>
#include <iostream>
#include <string>

#include "simpio.h"
#include "set.h"
#include "vector.h"

using namespace std;

void PrintStartingInfo()
{
	cout << "SUBSEQUENCE PRO" << endl;
	cout << "Enter words and find the shortest subsequence" << endl << endl;

	getLine("Press ENTER to continue\n");
}

bool IsSubsequence(string text, string subsequence)
{
	if(subsequence == "")
		return true;

	if(subsequence.length() > text.length())
		return false;

	if(subsequence[0] == text[0])
		return IsSubsequence(text.substr(1), subsequence.substr(1));

	return IsSubsequence(text.substr(1), subsequence);
}

bool AreSubsequences(Vector<string> strings, string subsequence)
{
	for(int wordID = 0; wordID < strings.size(); wordID++)
		if(IsSubsequence(strings[wordID], subsequence) == false)
			return false;

	return true;
}

Vector<string> GetSubsequences(Vector<string> strings)
{
	Vector<string> subsequences;
	
	for(int wordID = 0; wordID < strings.size(); wordID++)
		if(AreSubsequences(strings, strings[wordID]))
			subsequences.add(strings[wordID]);

	return subsequences;
}

string GetShortestSubsequence(Vector<string> strings)
{
	Vector<string> subsequences = GetSubsequences(strings);
	Set<string> subsequencesSet;

	foreach(string word in subsequences)
		subsequencesSet.add(word);

	foreach(string word in subsequencesSet)
		return word;

	throw exception();
}

Vector<string> GetWords(string sentinelWord = "")
{
	Vector<string> words;

	string word;

	cout << endl << "Enter '" << sentinelWord << "' to stop entering words" << endl;

	while(true)
	{
		word = getLine("Input: ");

		if(word == sentinelWord) break;

		words.add(word);
	}

	return words;
}

int main() 
{
	PrintStartingInfo();

	string sentinelWord = "";

	Vector<string> words = GetWords(sentinelWord);

	if(words.size() == 0) { getLine("\nWrong Input\n\nPress ENTER to continue"); return 1;}

	try
	{
		string shortestSubsequence = GetShortestSubsequence(words);
		cout << "Shortest subsequence: ";
		cout << shortestSubsequence << endl << endl;
	}
	catch (exception ex)
	{
		cout << endl << "No subsequence found" << endl << endl;
	}

	getLine("Press ENTER to continue");
    return 0;
}