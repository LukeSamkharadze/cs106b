/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <map>

#include "simpio.h"
#include "random.h"
#include "vector.h"
#include "tokenscanner.h"

using namespace std;

void PrintStartingInfo()
{
	cout << "RUN WITH CTRL+F5 FOR MAXIMUM PERFORMANCE" << endl << endl;
	
	getLine("Press ENTER to continue");

	cout << endl;
	cout << "EXTENSION N2 RANDOM WRITER" << endl;
	cout << "Enter file name, markov word model and we generate text using word" << endl << endl;
}

string GetFileName()
{
	while(true)
	{
		string fileName;

		cout << "Enter file name: ";
		cin >> fileName;

		if(ifstream(fileName.c_str()).good())
			return fileName;
	}
}

int GetMarkovModel()
{
	int markovModel;

	cout << "Enter markov model: ";
	cin >> markovModel;

	return markovModel;
}

int charSumOfVectors(const Vector<string>& vector)
{
	int sum = 0;

	foreach(string word in vector)
		for(int charID = 0; charID < word.length();charID++)
			sum+= word[charID];

	return sum;
}

struct CMPVectorByCharSum
{
	bool operator()(const Vector<string>& a, const Vector<string>& b) const
	{
		return charSumOfVectors(a) < charSumOfVectors(b);
	}
};

Vector<string> CutLastVectorElement(Vector<string> vector)
{
	vector.remove(vector.size()-1);
	return vector;
}

map<Vector<string>, Vector<string>,CMPVectorByCharSum> GetMarkovProbabilities(string &fileName, int &markovModel)
{
	cout << endl<<"Processing file..." << endl;

	map<Vector<string>, Vector<string>,CMPVectorByCharSum> markovProbabilities;

	Vector<string> currentMarkov;

	string word;

	ifstream stream(fileName.c_str());
	TokenScanner scanner(stream);
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("-',.!?;[]()`\"");

	while(scanner.hasMoreTokens())
	{
		word = scanner.nextToken();

		currentMarkov.add(word);
	
		if(currentMarkov.size() == markovModel +1)
		{
			markovProbabilities[CutLastVectorElement(currentMarkov)].add(word);
			currentMarkov.remove(0);
		}
	}

	cout << "Successfully Processed file." << endl << endl;

	return markovProbabilities;
}

Vector<string> GetMostRepeatedMarkov(map<Vector<string>, Vector<string>,CMPVectorByCharSum> &markovProbabilities)
{
	Vector<string> maxMarkovKey;

	foreach(Vector<string> key in markovProbabilities)
	{
		if(maxMarkovKey.size() == 0)
			maxMarkovKey = key;
		else if(markovProbabilities[key].size() > markovProbabilities[maxMarkovKey].size())
			maxMarkovKey = key;
	}

	return maxMarkovKey;
}

Vector<string> GenerateRandomText(
								  map<Vector<string>,Vector<string>,CMPVectorByCharSum> &markovProbabilities,
								  int textLength,
								  int markovModel)
{

	cout << "Generating text..." << endl;

	Vector<string> text = GetMostRepeatedMarkov(markovProbabilities);
	
	for(int i = 0; i < textLength; i++)
	{
		Vector<string> markov;

		for(int j = 0; j < markovModel; j++)
			markov.add(text[text.size()-(markovModel-j)]);

		if(markovProbabilities[markov].size() == 0)
			break;

		text.add(markovProbabilities[markov][randomInteger(0,markovProbabilities[markov].size()-1)]);
	}

	cout << "Successfully generated text." << endl << endl;

	return text;
}

void PrintText(Vector<string>& text, int wordsInLine)
{
	int counter = 0;
	foreach(string word in text)
	{
		cout << word << " ";
		if(++counter%wordsInLine == 0)
			cout << endl;
	}

	cout << endl;
}

int main() 
{
	PrintStartingInfo();

	int wordsInPrintedLine = 20;
	int wordsInGeneratedText = 200;

	string fileName = GetFileName();
	int markovModel = GetMarkovModel();

	map<Vector<string>, Vector<string>,CMPVectorByCharSum> markovProbabilities = GetMarkovProbabilities(fileName,markovModel);
	
	Vector<string> generatedText = GenerateRandomText(markovProbabilities,wordsInGeneratedText,markovModel);

	PrintText(generatedText,wordsInPrintedLine);

    return 0;
}