/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>

#include "simpio.h"
#include "strlib.h"
#include "filelib.h"
#include "tokenscanner.h"
#include "console.h"

using namespace std;

struct TextInfo
{
	long sentenceCount;
	long wordCount;
	long syllableCount;

	TextInfo()
	{
		sentenceCount = 0;
		wordCount = 0;
		syllableCount = 0;
	}
};

string GetValidFileName()
{
	string fileName;

	do
		fileName = getLine("Enter The Valid File Name : ");
	while(fileExists(fileName) == false);

	return fileName;
}

bool IsPunctuationMark(string word)
{
	if(word == "." || word == "!" || word == "?")
		return true;

	return false;
}

bool IsWord(string word)
{
	if(('A' <= word[0] && word[0] <= 'Z') || ('a' <= word[0] && word[0] <= 'z'))
		return true;
	
	return false;
}

bool IsSyllable(char character)
{
	character = toLowerCase(string() + character)[0];

	if(character == 'a' || character == 'e' || character == 'i' ||
		character == 'o' || character == 'u' || character == 'y')
		return true;

	return false;
}

int CountSyllables(string word)
{
	int syllableCount = 0;

	for(unsigned int characterID = 0; characterID < word.length(); characterID++)
		if(IsSyllable(word[characterID]))
		{
			if(characterID == word.length() - 1 && toLowerCase(string() + word[characterID])[0] == 'e')
				break;
			else if(characterID == word.length() - 2 && toLowerCase(string() + word[characterID+1])[0] == 'e')
				syllableCount++;
			else if(characterID < word.length() - 1 && IsSyllable(word[characterID + 1]))
				continue;
			else
				syllableCount++;
		}

	if(syllableCount == 0)
		return 1;

	return syllableCount;
}

TextInfo GetTextInfoFromFile(string fileName)
{
	ifstream inputStream(fileName.c_str());

	TokenScanner tokenScanner(inputStream);
	tokenScanner.ignoreWhitespace();
	tokenScanner.addWordCharacters("'");

	TextInfo textInfo;

	while (tokenScanner.hasMoreTokens()) 
	{
		string token = tokenScanner.nextToken();

		if(IsWord(token))
		{
			textInfo.wordCount++;
			textInfo.syllableCount+=CountSyllables(token);
		}
		else if(IsPunctuationMark(token))
			textInfo.sentenceCount++;
	}

	if(textInfo.sentenceCount == 0)
		textInfo.sentenceCount = 1;
	if(textInfo.wordCount == 0)
		textInfo.wordCount = 1;

	return textInfo;
}

double CalculateFleschKincaid(TextInfo textInfo)
{
	const double CONSTANT_0 = -15.59;
	const double CONSTANT_1 = 0.39;
	const double CONSTANT_2 = 11.8;

	return CONSTANT_0 + CONSTANT_1 * ((double)textInfo.wordCount / (double)textInfo.sentenceCount) +
		CONSTANT_2 * ((double)textInfo.syllableCount / (double)textInfo.wordCount);
}

int main() 
{
	string fileName = GetValidFileName();

    TextInfo textInfo = GetTextInfoFromFile(fileName);

	cout << "Sentence count: " << textInfo.sentenceCount << endl;
	cout << "Word count: " << textInfo.wordCount << endl;
	cout << "Syllable count: " << textInfo.syllableCount << endl;

	cout << "Flesch kincaid score: " << CalculateFleschKincaid(textInfo) << endl;

    return 0;
}
