/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>

#include "simpio.h"
#include "hashmap.h"
#include "vector.h"
#include "random.h"
#include "string.h"

#include "console.h"

using namespace std;

//===========================================================================================//

enum CoinSide { TAILS = 0 , HEADS = 1};

HashMap<CoinSide,string> GetCoinSidesToString();

HashMap<CoinSide,string> coinSidesToString = GetCoinSidesToString();

HashMap<CoinSide,string> GetCoinSidesToString()
{
	HashMap<CoinSide,string> coinSidesToString;

	coinSidesToString.put(CoinSide(0),"TAILS");
	coinSidesToString.put(CoinSide(1),"HEADS");

	return coinSidesToString;
}

//===========================================================================================//

bool CheckForSpecificCoinSides(Vector<CoinSide> coinSides, Vector<CoinSide> specificCoinSides)
{
	bool flag = false;

	for(int coinSideID = 0; coinSideID < coinSides.size() - specificCoinSides.size() + 1; coinSideID++)
	{
		flag = true;

		for(int specificCoinSideID = 0; specificCoinSideID < specificCoinSides.size(); specificCoinSideID++)
			if(coinSides[coinSideID+specificCoinSideID] != specificCoinSides[specificCoinSideID])
				flag = false;

		if(flag)
			return flag;
	}
	
	return flag;
}

//===========================================================================================//

CoinSide FlipCoin(double headsChance)
{
	return CoinSide(randomChance(headsChance));
}

void FlipConsecutiveCoinSides(Vector<CoinSide> specificCoinSides, double headsChance, bool isDebugModeEnabled)
{
	Vector<CoinSide> flippedCoinSides;

	long flipCounter = 0;
	while(CheckForSpecificCoinSides(flippedCoinSides, specificCoinSides) == false)
	{
		flippedCoinSides.add(FlipCoin(headsChance));

		if(isDebugModeEnabled)
			cout << "Coin flipped: " <<
			coinSidesToString.get(flippedCoinSides[flippedCoinSides.size()-1]) <<
			" " << flipCounter << endl;

		flipCounter++;
	}

	cout << "It took " << flipCounter << " flips" << endl;
}

Vector<CoinSide> GetCorrespondedCoinSidesVector(string text)
{
	Vector<CoinSide> correspondedCoinSides;

	for(int characterID = 0; characterID < text.length(); characterID++)
		if(text[characterID] == 'T')
			correspondedCoinSides.add(CoinSide::TAILS);
		else if(text[characterID] == 'H')
			correspondedCoinSides.add(CoinSide::HEADS);
	
	return correspondedCoinSides;
}

int main() 
{
	cout << "Enter your specific Tails-Heads sequence, for ex: \'HTTHT\'" << endl;
	string inputLine = getLine("Input: ");

	cout << "Enter chance for heads to get flipped, for ex: \'0.4\'" << endl;
	double inputDouble = getReal("Input: ");

	cout << "Do you want to enable debug mode? (Enter \'1\' or \'0\')" << endl;
	bool isDebugModeEnabled;
	cout << "Input: ";
	cin >> isDebugModeEnabled;

	FlipConsecutiveCoinSides(
		GetCorrespondedCoinSidesVector(inputLine),
		inputDouble,
		isDebugModeEnabled);

    return 0;
}