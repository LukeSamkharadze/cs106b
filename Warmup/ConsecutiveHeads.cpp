/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>


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

	coinSidesToString.put(CoinSide(0),"tails");
	coinSidesToString.put(CoinSide(1),"head");

	return coinSidesToString;
}

//===========================================================================================//

bool CheckForNConsecutiveCoinSides(Vector<CoinSide> coinSides, int startingID, int consecutiveCoinSides)
{
	for(int consecutiveCoinSideCounter = 1; consecutiveCoinSideCounter < consecutiveCoinSides; consecutiveCoinSideCounter++)
		if(coinSides[startingID] != coinSides[startingID + consecutiveCoinSideCounter])
			return false;

	return true;
}

bool CheckForNConsecutiveCoinSides(Vector<CoinSide> coinSides, int consecutiveCoinSides)
{
	for(int coinSideID = 0; coinSideID < coinSides.size() - consecutiveCoinSides + 1; coinSideID++)
		if(CheckForNConsecutiveCoinSides(coinSides,coinSideID,consecutiveCoinSides))
			return true;

	return false;
}



//===========================================================================================//

CoinSide FlipCoin(double tailsChance)
{
	return CoinSide((int)randomChance(tailsChance));
}


void Flip3ConsecutiveCoinSides(int consecutiveCoinSides, double tailsChance)
{
	Vector<CoinSide> flippedCoinSides;

	int flipCounter = 0;
	while(CheckForNConsecutiveCoinSides(flippedCoinSides,consecutiveCoinSides) == false)
	{
		flippedCoinSides.add(FlipCoin(tailsChance));

		cout << coinSidesToString.get(flippedCoinSides[flippedCoinSides.size()-1]) << endl;

		flipCounter++;
	}

	cout << "It took " << flipCounter <<
		" flips to get " << consecutiveCoinSides <<
		" consecutive " << coinSidesToString.get(flippedCoinSides[flippedCoinSides.size()-1]) << "." << endl;
}


int main() 
{
	int consecutiveCoinSides = 3;
	double tailsChance = .5;

	Flip3ConsecutiveCoinSides(consecutiveCoinSides,tailsChance);

    return 0;
}
