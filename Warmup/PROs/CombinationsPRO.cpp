/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>

#include "vector.h"
#include "strlib.h"
#include "simpio.h"
#include "console.h"

using namespace std;

Vector<Vector<long long>> GetPascaleNumbers(long long n)
{
	Vector<Vector<long long>> pascalNumbers;

	for(long long i = 0; i < n; i++)
	{
		pascalNumbers.add(Vector<long long>());

		for(int j = 0; j <= i; j++)
		{
			pascalNumbers[pascalNumbers.size()-1].add(0);

			if(j == 0 || i == j)
				pascalNumbers[i][j] = 1;
			else
				pascalNumbers[i][j] = pascalNumbers[i-1][j-1] + pascalNumbers[i-1][j];
		}
	}

	return pascalNumbers;
}

Vector<string> GetPascalNumberRowsInStrings(Vector<Vector<long long>> pascalNumbers,bool isTriangleModeEnabled)
{
	Vector<string> pascalNumberRowsInStrings;

	for(long long i = 0; i < pascalNumbers.size(); i++)
	{
		string text = "";

		for(long long j = 0; j <= i; j++)
		{
			if(isTriangleModeEnabled)
				text += integerToString(pascalNumbers[i][j]) + " ";
			else if(pascalNumbers[i][j]%3 == 0)
				text += "   ";
			else if(pascalNumbers[i][j]%3 == 1)
				text += string() + char(1 + '0') + "  ";
			else if(pascalNumbers[i][j]%3 == 2)
				text += string() + char(2 + '0') + "  ";
		}

		pascalNumberRowsInStrings.add(text);
	}

	return pascalNumberRowsInStrings;
}

void DrawPascalTriangle(long long rows, bool isTriangleModeEnabled)
{
	Vector<Vector<long long>> pascalNumbers = GetPascaleNumbers(rows);
	Vector<string> pascalNumberRowsInStrings = GetPascalNumberRowsInStrings(pascalNumbers, isTriangleModeEnabled);

	for(long long i = 0; i < pascalNumbers.size(); i++)
	{
		for(
			long long j = 0; 
			j < ((long long)pascalNumberRowsInStrings[rows-1].length() - (long long)pascalNumberRowsInStrings[i].length()) /2;
			j++)
			cout << " ";

		cout << pascalNumberRowsInStrings[i] << endl;
	}

}

int main() 
{
	cout << "1) Improved Pascal Calculation Algorithm" << endl;
	cout << "2) Added a Way to Visualize Pascal Numbers" << endl;
	
	cout << endl;

	bool isTriangleModeEnabled;
	cout << "Enter '1' to enable triangle mode, otherwise enter '0'" << endl;
	cout << "Input: ";
	cin >> isTriangleModeEnabled;

	long long rows;
	cout << "Enter number of rows you want to see on pascal triangle" << endl;
	cout << "Input: ";
	cin >> rows;

	DrawPascalTriangle(rows, isTriangleModeEnabled);

    return 0;
}
