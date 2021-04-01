#include <iostream>
#include <string>

#include "simpio.h"
#include "vector.h"
#include "queue.h"
#include "lexicon.h"
#include "foreach.h"

using namespace std;

void PrintStartingInfo()
{
	cout << "RUN WITH CTRL+F5 FOR MAXIMUM PERFORMANCE" << endl << endl;
	
	getLine("Press ENTER to continue");

	cout << endl;
	cout << "EXTENSION N1 WORD LADDER" << endl;
	cout << "Enter word to start with, to end with and we generate ladder faster" << endl << endl;
}

bool IsInputValid(Map<string,Vector<string>>& wordsAndNeighbours, string& startingWord, string& endingWord)
{
	if(startingWord.length() != endingWord.length())
		return false;
	if(wordsAndNeighbours.containsKey(startingWord)==false)
		return false;
	if(wordsAndNeighbours.containsKey(endingWord)==false)
		return false;

	return true;
}

Vector<string> GetWordLadder(Map<string,Vector<string>>& wordsAndNeighbours, string& startingWord, string& endingWord)
{
	cout <<endl<< "Searching word ladder..." << endl;

	IsInputValid(wordsAndNeighbours, startingWord, endingWord);

    Queue<Vector<string>> wordLadders;
	wordLadders.enqueue(Vector<string>());
	wordLadders.back().add(startingWord);
    
    Lexicon alreadyUsedWords = Lexicon();

	while (wordLadders.isEmpty() == false)
	{
		Vector<string>& currentWordLadder = wordLadders.dequeue();

		string currentWord = currentWordLadder[currentWordLadder.size()-1];
	        
		if (currentWord == endingWord)
		{
			cout << "Successfully searched word ladder." << endl;
			return currentWordLadder;
		}

		foreach(string newWord in wordsAndNeighbours[currentWord])
		{
			if (alreadyUsedWords.contains(newWord))
				continue;

			wordLadders.enqueue(currentWordLadder);
			wordLadders.back().add(newWord);
			alreadyUsedWords.add(newWord);
		}
	}

	return Vector<string>();
}

void PrintWordLadder(Vector<string> wordLadder)
{
	if(wordLadder.size() == 0)
	{
		cout << "No word ladder could be found." << endl << endl;
		return;
	}

	cout << "Ladder found: ";

	for(int wordID = 0; wordID < wordLadder.size()-1; wordID++)
		cout << wordLadder[wordID] << " -> ";
	cout << wordLadder[wordLadder.size()-1] << endl << endl;
}

Lexicon LoadLexicon(string fileName)
{
	cout << "Loading the lexicon..." << endl;

	Lexicon lexicon("EnglishWords.dat");

	cout << "Successfully loaded the lexicon." << endl << endl;

	return lexicon;
}

Map<string,Vector<string>> GetWordsAndNeighbours(Lexicon &lexicon)
{
	cout <<"Optimizing the lexicon..." << endl;

	Map<string,Vector<string>> wordsAndNeighbours;

	foreach(string word in lexicon)
		for (int characterIDToReplace = 0; characterIDToReplace < word.size(); characterIDToReplace++) 
			for (char character = 'a'; character <= 'z'; character++) 
			{
				string newWord = word.substr(0, characterIDToReplace) + character + word.substr(characterIDToReplace + 1);
			    
				if(newWord == word)
					continue;

				if (lexicon.contains(newWord) == false)
					continue;

				wordsAndNeighbours[word].add(newWord);
			}

	cout <<"Successfully optimized the lexicon." << endl << endl;

	return wordsAndNeighbours;
}

int main()
{
	PrintStartingInfo();

	Lexicon& lexicon = LoadLexicon("EnglishWords.dat");

	Map<string,Vector<string>> wordsAndNeighbours = GetWordsAndNeighbours(lexicon);

	while(true)
	{
		string startingWord = getLine("Enter the starting word: ");
		if(startingWord == "") break;
		string endingWord = getLine("Enter the ending word: ");

		PrintWordLadder(GetWordLadder(wordsAndNeighbours, startingWord, endingWord));
	}

	return 0;
}