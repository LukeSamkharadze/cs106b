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
#include <cmath>

#include "simpio.h"
#include "map.h"
#include "random.h"
#include "set.h"

using namespace std;

struct Author
{
	string authorName;
	string fileName;

	Author() {}

	Author(string authorName_, string fileName_)
	{
		authorName = authorName_;
		fileName = fileName_;
	}
};

void PrintStartingInfo()
{
	cout << "RUN WITH CTRL+F5 FOR MAXIMUM PERFORMANCE" << endl << endl;
	
	getLine("Press ENTER to continue");

	cout << endl;
	cout << "EXTENSION N1 RANDOM WRITER" << endl;
	cout << "Enter file name, markov model and we compare it to other authors" << endl << endl;
}

Vector<Author> GetAuthors()
{
	Vector<Author> authors;

	authors.add(Author("William Shakespeare","Hamlet.txt"));
	authors.add(Author("George Eliot","Middlemarch.txt"));
	authors.add(Author("Mark Twain","TomSawyer.txt"));
	authors.add(Author("Martin Luther King","MLK-Dream.txt"));
	authors.add(Author("John F. Kennedy","JFK-Berlin.txt"));
	authors.add(Author("Charlotte Bronte","JaneEyre.txt"));

	return authors;
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

Map<string, Vector<char>> GetMarkovProbabilities(string& fileName, int& markovModel)
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

int Count(Vector<char> &vector, char &character)
{
	int counter = 0;

	foreach(char ch in vector)
		if(ch == character)
			++counter;

	return counter;
}

int Count(Map<char,int>& charactersAndItsCount)
{
	int counter = 0;

	foreach(char character in charactersAndItsCount)
		counter+=charactersAndItsCount[character];

	return counter;
}

float Average(Vector<float>& vector)
{
	float sum = 0;

	foreach(float realNumber in vector)
		sum+= realNumber;

	return sum / vector.size();
}

Map<string, Map<char,float>> MarkovVectorToMap(Map<string,Vector<char>>& markovProbabilities)
{
	Map<string, Map<char,float>> newMarkovProbabilities;

	foreach(string key in markovProbabilities)
	{
		newMarkovProbabilities.put(key,Map<char,float>());

		Set<char> characterSet;

		foreach(char character in markovProbabilities[key])
			characterSet.add(character);

		foreach(char character in characterSet)
			newMarkovProbabilities[key].put(
			character,
			(float)Count(markovProbabilities[key],character)/(float)markovProbabilities[key].size());
	}

	return newMarkovProbabilities;
}

void CompareMarkovProbabilities(
								Vector<Author>& authors,
								Vector<Map<string, Map<char,float>>>& authorsAndMarkovs,
								Map<string, Map<char,float>>& markovProbabilities)
{
	cout << "Starting to compare other authors..." << endl;

	for(int authorID = 0; authorID < authors.size(); authorID++)
	{
		Vector<float> differences;

		foreach(string markov in markovProbabilities)
			if(authorsAndMarkovs[authorID].containsKey(markov))
				foreach(char character in markovProbabilities[markov])
					if(authorsAndMarkovs[authorID][markov].containsKey(character))
						differences.add(abs(
							(float)(authorsAndMarkovs[authorID][markov][character]-markovProbabilities[markov][character])/
							(float)markovProbabilities[markov][character]));

		cout << "Compared to " << authors[authorID].authorName << " and we got " << Average(differences) * 100 << "% difference" << endl;
	}

	cout << "Successfully  compared other authors." << endl;
}

Vector<Map<string, Map<char,float>>> LoadAuthorsMarkovs(Vector<Author>& authors, int& markovModel)
{
	cout << endl << "Loading authors and their texts..." << endl;

	Vector<Map<string, Map<char,float>>> authorsAndMarkovs;

	for(int authorID = 0; authorID < authors.size(); authorID++)
	{
		cout << "Current author loading: " << authors[authorID].authorName << "..."<<endl;
		
		authorsAndMarkovs.add(MarkovVectorToMap(GetMarkovProbabilities(authors[authorID].fileName,markovModel)));
	}

	cout << "Successfully loaded authors and their texts." << endl;

	return authorsAndMarkovs;
}

int main() 
{
	PrintStartingInfo();

	string fileName = GetFileName();
	int markovModel = GetMarkovModel();

	Vector<Author> authors = GetAuthors();

	Vector<Map<string, Map<char,float>>>& authorsAndMarkovs = LoadAuthorsMarkovs(authors, markovModel);

	cout << endl << "Loading your file..." << endl;
	Map<string, Map<char,float>>& markovProbabilities = MarkovVectorToMap(GetMarkovProbabilities(fileName,markovModel));
	cout << "Successfully loaded your file." << endl << endl; 

	CompareMarkovProbabilities(authors,authorsAndMarkovs,markovProbabilities);

    return 0;
}