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

#include "simpio.h"
#include "map.h"
#include "random.h"

using namespace std;

void PrintStartingInfo()
{
	cout << "RUN WITH CTRL+F5 FOR MAXIMUM PERFORMANCE" << endl << endl;
	
	getLine("Press ENTER to continue");

	cout << endl;
	cout << "HOMEWORK RANDOM WRITER" << endl;
	cout << "Enter file name, markov model and we generate text" << endl << endl;
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

Map<string, Vector<char>> GetMarkovProbabilities(string fileName, int markovModel)
{
    Map<string,Vector<char>> markovProbabilities;
    
	ifstream stream(fileName.c_str());

	Vector<char> text;
	
    char characters;
	while(stream.get(characters))
		text.add(characters);

	string currentMarkov = "";
	for(int i = 0; i < markovModel; i++)
        currentMarkov += " ";

    for(int i = markovModel + 1; i < text.size() - markovModel; i++)
	{
        for(int j = 0; j < markovModel; j++)
            currentMarkov[j] = text[i-markovModel+j];

        markovProbabilities[currentMarkov].add(text[i]);
    }

    return markovProbabilities;
}

string GetMostRepeatedMarkov(Map<string, Vector<char>>& markovProbabilities)
{
	string maxMarkovKey = "";

	foreach(string key in markovProbabilities)
	{
		if(maxMarkovKey == "")
			maxMarkovKey = key;
		else if(markovProbabilities[key].size() > markovProbabilities[maxMarkovKey].size())
			maxMarkovKey = key;
	}

	return maxMarkovKey;
}

string GenerateRandomText(Map<string, Vector<char>>& markovProbabilities, int textLength, int markovModel)
{
	string text = GetMostRepeatedMarkov(markovProbabilities);
	
	if(text.size() < markovModel)
		return text;

	for(int i = 0; i < textLength; i++)
	{
		string markov = text.substr(text.length()-markovModel,markovModel);

		if(markovProbabilities[markov].size() == 0)
			break;

		text += markovProbabilities[markov][randomInteger(0,markovProbabilities[markov].size()-1)];
	}

	return text;
}

int main() 
{
	PrintStartingInfo();

	string fileName = GetFileName();
	int markovModel = GetMarkovModel();
	int textLength = 2000;

	cout << endl << "Processing..." << endl;
	Map<string, Vector<char>>& markovProbabilities = GetMarkovProbabilities(fileName,markovModel);

	cout << endl << GenerateRandomText(markovProbabilities,textLength,markovModel) << endl << endl;

    return 0;
}