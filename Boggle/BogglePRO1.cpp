#include <iostream>
#include <math.h>

#include "gboggle.h"
#include "gwindow.h"
#include "hashmap.h"
#include "lexicon.h"
#include "strlib.h"
#include "random.h"
#include "simpio.h"
#include "grid.h"
#include "set.h"

using namespace std;

struct Point
{
	int x;
	int y;

	Point() { }

	Point(int x_, int y_)
	{
		x = x_;
		y = y_;
	}
};

void PrintProgramInfo()
{
	cout << "BOGGLE PRO N1" << endl;
	cout << "Decide whether you want to play big boggle or not" << endl << endl;

	getLine("Press ENTER to continue\n");
}

void PrintWelcomeText() 
{
	cout << "Welcome!  You're about to play an intense game ";
	cout << "of mind-numbing Boggle.  The good news is that ";
	cout << "you might improve your vocabulary a bit.  The ";
	cout << "bad news is that you're probably going to lose ";
	cout << "miserably to this little dictionary-toting hunk ";
	cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

void PrintInstructions()
{
	cout << endl;
	cout << "The boggle board is a grid onto which I ";
	cout << "I will randomly distribute cubes. These ";
	cout << "6-sided cubes have letters rather than ";
	cout << "numbers on the faces, creating a grid of ";
	cout << "letters on which you try to form words. ";
	cout << "You go first, entering all the words you can ";
	cout << "find that are formed by tracing adjoining ";
	cout << "letters. Two letters adjoin if they are next ";
	cout << "to each other horizontally, vertically, or ";
	cout << "diagonally. A letter can only be used once ";
	cout << "in each word. Words must be at least four ";
	cout << "letters long and can be counted only once. ";
	cout << "You score points based on word length: a ";
	cout << "4-letter word is worth 1 point, 5-letters ";
	cout << "earn 2 points, and so on. After your puny ";
	cout << "brain is exhausted, I, the supercomputer, ";
	cout << "will find all the remaining words and double ";
	cout << "or triple your paltry score." << endl << endl;
	cout << "Hit return when you're ready...";
	getLine();
	cout << endl;
}

void PrintGameInstructions(string sentinel)
{
	cout << "Ok, take all the time you want and find all the words you can!";
	cout << "Signal that you're finished by entering \"" << sentinel << "\"" << endl << endl;
}

void PrintMinimumLengthError()
{
	cout << "I'm sorry, but we have our standards." << endl;
	cout << "That word doesn't meet the minimum word length." << endl;
}

void PrintAlreadyGuessedWordError()
{
	cout << "You've already guessed that!" << endl;
}

void PrintInvalidWordError()
{
	cout << "You can't make that word!" << endl;
}

bool GetYesOrNo(string promt)
{
	while(true)
	{
		char inputFirstChar = tolower(getLine(promt)[0]);

		if(inputFirstChar == 'y') {cout << endl; return true; }
		if(inputFirstChar == 'n') {cout << endl; return false; }
		cout << "Please answer yes or no." << endl;
	}
}

string GetHumanInput()
{
	return getLine("Enter a word: ");
}

bool IsAskingForInstructions()
{
	return GetYesOrNo("Do you need instructions? ");
}

bool IsAskingForBigBoggle()
{
	cout << "You can choose standard Boggle (4x4 grid)" << endl;
	cout << "or Big Boggle (5x5)." << endl;

	return GetYesOrNo("Would you like Big Boggle? ");
}

bool IsAskingForOverride()
{
	cout << "I'll give you a chance to set up the board to your specification,";
	cout << "which makes it easier to confirm your boggle program is working." << endl;

	return GetYesOrNo("Do you want to force the board configuration? ");
}

bool IsAskingForRematch()
{
	return GetYesOrNo("Would you like to play again? ");
}

Vector<string> GetOverridenRows(bool isAskingForBigBoggle)
{
	int inputSize = 16 + 9 * isAskingForBigBoggle;
	int rowSize = 4 + isAskingForBigBoggle;

	cout << "Enter a " << inputSize << "-character string to identify which letters you want on the cubes." << endl;
	cout << "The first " << rowSize << " letters are the cubes on the top row from left to right, the next 5 letters are the second row, and so on." << endl;

	string input = getLine("Enter the string: ");

	while(input.size() != inputSize)
		input = getLine(string() + "String must include " + integerToString(inputSize) + " characters! Try again: ");

	Vector<string> rows;

	for(int rowID = 0; rowID < rowSize; rowID++)
	{
		string row = "";
		for(int charID = 0; charID < rowSize; charID++)
			row += input[rowID * rowSize + charID];
		rows.add(row);
	}

	return rows;
}

Vector<string> GetDefaultBoardCubes(bool isAskingForBigBoggle)
{
	string BIG_BOGGLE_CUBES[25]  = 
	{
		"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
		"AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
		"CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
		"DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
		"FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
	};

	string STANDARD_CUBES[16]  = 
	{
		"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
		"AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
		"DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
		"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
	};

	Vector<string> boardCubes;

	if(isAskingForBigBoggle)
		for(int cubeID = 0; cubeID < 25; cubeID++)
			boardCubes.add(BIG_BOGGLE_CUBES[cubeID]);
	else
		for(int cubeID = 0; cubeID < 16; cubeID++)
			boardCubes.add(STANDARD_CUBES[cubeID]);

	return boardCubes;
}


Grid<char> GetOverridenBoard(Vector<string> overridenRows)
{
	Grid<char> board(overridenRows.size(), overridenRows[0].size());

	for(int rowID = 0; rowID < overridenRows.size(); rowID++)
		for(int collumnID = 0; collumnID < overridenRows[rowID].size(); collumnID++)
			board[rowID][collumnID] = overridenRows[rowID][collumnID];

	return board;
}

Grid<char> GetBoard(Vector<string> boardCubes)
{
	Grid<char> board(sqrt((double)boardCubes.size()), sqrt((double)boardCubes.size()));

	for(int rowID = 0; rowID < board.numRows(); rowID++)
		for(int collumnID = 0; collumnID < board.numCols(); collumnID++)
		{
			int randomIndex = randomInteger(0, boardCubes.size() - 1);
			board[rowID][collumnID] = boardCubes[randomIndex][randomInteger(0, boardCubes[randomIndex].length() - 1)];
			boardCubes.remove(randomIndex);
		}

	return board;
}

HashMap<string,Vector<Point>> GetNeighbourWords(Grid<char>& board, string word, Vector<Point> pointsUsed)
{
	HashMap<string,Vector<Point>> neighbourWords;

	for(int dx = -1; dx <= 1; dx++)
		for(int dy = -1; dy <= 1; dy++)
		{
			int newX = pointsUsed[pointsUsed.size() - 1].x + dx;
			int newY = pointsUsed[pointsUsed.size() - 1].y + dy;

			if(newX < 0 || newX >= board.numCols() || newY < 0 || newY >= board.numRows())
				continue;

			bool isNewPointUsed = false;
			foreach(Point point in pointsUsed)
				if(newX == point.x && newY == point.y)
					isNewPointUsed = true;
			if(isNewPointUsed)
				continue;

			string newWord = word + board[newX][newY];
			Vector<Point> newPointsUsed = pointsUsed + Vector<Point>(1, Point(newX,newY));

			neighbourWords.put(newWord, newPointsUsed);
		}

	return neighbourWords;
}

void GetAllPossibleWordsREC(Grid<char>& board, int& minWordLength, Lexicon& lexicon,
								HashMap<string,Vector<Point>>& result,
								string currentWord, Vector<Point> pointsUsed)
{
	if(currentWord.length() > 1)
		if(lexicon.containsPrefix(currentWord) == false)
			return;

	if(currentWord.length() >= minWordLength)
		if(lexicon.contains(currentWord))
			result.put(currentWord, pointsUsed);

	HashMap<string,Vector<Point>> neighbourWords = GetNeighbourWords(board, currentWord, pointsUsed);

	foreach(string neighbourWord in neighbourWords)
		GetAllPossibleWordsREC(board, minWordLength, lexicon, result, neighbourWord, neighbourWords[neighbourWord]);
}

HashMap<string,Vector<Point>> GetAllPossibleWords(Grid<char>& board, int& minWordLength, Lexicon& lexicon)
{
	HashMap<string,Vector<Point>> allPossibleWords;

	for(int rowID = 0; rowID < board.numRows(); rowID++)
		for(int collumnID = 0; collumnID < board.numCols(); collumnID++)
		{
			HashMap<string,Vector<Point>> allPossibleWordsFrom1Point;

			GetAllPossibleWordsREC(board, minWordLength, lexicon,
				allPossibleWordsFrom1Point,
				string() + board[rowID][collumnID],
				Vector<Point>(1, Point(rowID, collumnID)));
			
			foreach(string word in allPossibleWordsFrom1Point)
				allPossibleWords.put(word, allPossibleWordsFrom1Point[word]);
		}

	return allPossibleWords;
}

void DrawBoard(Grid<char> board)
{
	drawBoard(board.numRows(), board.numCols());

	for(int rowID = 0; rowID < board.numRows(); rowID++)
		for(int collumnID = 0; collumnID < board.numCols(); collumnID++)
			labelCube(rowID, collumnID, board[rowID][collumnID]);
}


Set<string> GetHumanWords(int minWordLength, string sentinel, HashMap<string,Vector<Point>> allPossibleWords)
{
	Set<string> guessedWords;

	string input = GetHumanInput();

	while(input != sentinel)
	{
		if(input.length() < minWordLength)
			PrintMinimumLengthError();
		else if(guessedWords.contains(input))
			PrintAlreadyGuessedWordError();
		else if(allPossibleWords.containsKey(input))
		{
			recordWordForPlayer(input, Player::HUMAN);
			guessedWords.add(input);
		}
		else
			PrintInvalidWordError();

		input = GetHumanInput();
	}

	return guessedWords;
}

void PlayComputersTurn(HashMap<string,Vector<Point>> allPossibleWords, Set<string> humanGuessedWords)
{
	foreach(string humanGuessedWord in humanGuessedWords)
		allPossibleWords.remove(humanGuessedWord);

	foreach(string word in allPossibleWords)
		recordWordForPlayer(word, Player::COMPUTER);
}

void PlayTurns(Grid<char> board, int minWordLength, string sentinel, HashMap<string,Vector<Point>> allPossibleWords)
{
	PrintGameInstructions(sentinel);

	Set<string> humanGuessedWords = GetHumanWords(minWordLength, sentinel, allPossibleWords);
	
	PlayComputersTurn(allPossibleWords, humanGuessedWords);
}

void PlayBoogle(bool isAskingForBigBoggle, int minWordLength, string sentinel, Lexicon lexicon)
{
	Grid<char> board;

	if(IsAskingForOverride())
		board = GetOverridenBoard(GetOverridenRows(isAskingForBigBoggle));
	else 
		board = GetBoard(GetDefaultBoardCubes(isAskingForBigBoggle));

	DrawBoard(board);
	PlayTurns(board, minWordLength, sentinel, GetAllPossibleWords(board, minWordLength, lexicon));
}

int main() 
{
	int windowWidth = 650;
	int windowHeight = 350;

	string lexiconPath = "EnglishWords.dat";
	int minWordLength = 4;
	string sentinel = "";

	GWindow gw(windowWidth, windowHeight);
	initGBoggle(gw);

	PrintProgramInfo();

	PrintWelcomeText();
	if(IsAskingForInstructions()) 
		PrintInstructions();

	do
		PlayBoogle(IsAskingForBigBoggle(), minWordLength, sentinel, Lexicon(lexiconPath));
	while(IsAskingForRematch());

	return 0;
}