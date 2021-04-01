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
	cout << "HOMEWORK WORD LADDER" << endl;
	cout << "Enter word to start with, to end with and we generate ladder" << endl << endl;
}

bool IsInputValid(Lexicon& lexicon, string& startingWord, string& endingWord)
{
	if(startingWord.length() != endingWord.length())
		return false;
	if(lexicon.contains(startingWord)==false)
		return false;
	if(lexicon.contains(endingWord)==false)
		return false;

	return true;
}

Vector<string> GetWordLadder(Lexicon& lexicon, string& startingWord, string& endingWord)
{
	IsInputValid(lexicon,startingWord,endingWord);

    Queue<Vector<string>> wordLadders;
	wordLadders.enqueue(Vector<string>());
	wordLadders.back().add(startingWord);
    
    Lexicon alreadyUsedWords;

	while (wordLadders.isEmpty() == false)
	{
		Vector<string>& currentWordLadder = wordLadders.dequeue();

		string currentWord = currentWordLadder[currentWordLadder.size()-1];
	        
		if (currentWord == endingWord) 
			return currentWordLadder;

		for (int characterIDToReplace = 0; characterIDToReplace < currentWord.size(); characterIDToReplace++) 
			for (char character = 'a'; character <= 'z'; character++) 
			{
				string newWord = currentWord.substr(0, characterIDToReplace) + character + currentWord.substr(characterIDToReplace + 1);
			    
				if (alreadyUsedWords.contains(newWord) || lexicon.contains(newWord) == false)
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

int main()
{
	PrintStartingInfo();

	Lexicon& lexicon = Lexicon("EnglishWords.dat");

	while(true)
	{
		string startingWord = getLine("Enter the starting word: ");
		if(startingWord == "") return 0;
		string endingWord = getLine("Enter the ending word: ");

		cout << "Searching..." << endl;

		PrintWordLadder(GetWordLadder(lexicon, startingWord, endingWord));
	}

	cout << "Goodbye!" << endl;
	return 0;
}