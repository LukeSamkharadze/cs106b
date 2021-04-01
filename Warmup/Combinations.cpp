/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>

#include "simpio.h"
#include "console.h"

using namespace std;

int FindPascalC(int n,int k)
{
	// base cases
	if( k == 0 || n == k )
		return 1;
	
	// for non valid cases
	if( k < 0 || k > n)
		return -1;

	// main cases
	return FindPascalC(n-1,k-1) + FindPascalC(n-1,k);
}

int main() 
{
	int n = getInteger("Input n: ");
	int k = getInteger("Input k: ");

	cout << FindPascalC(n,k) << endl;

    return 0;
}
