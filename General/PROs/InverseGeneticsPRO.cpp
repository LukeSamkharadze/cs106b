/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>

#include "simpio.h"
#include "set.h"
#include "map.h"

using namespace std;

void PrintStartingInfo()
{
	cout << "INVERSE GENETICS PRO" << endl;
	cout << "Enter RNA strand and we will calculate mutation chance of getting another protein" << endl << endl;
	
	getLine("Press ENTER to continue\n");
}

Map<char, Set<string>> loadCodonMap(string inputFile) 
{
    Map<char, Set<string>> result;

    string codon;
    char protein;

	ifstream input(inputFile.c_str());

    while (input >> codon >> protein)
        result[protein] += codon;

    return result;
}

bool IsCodonSequenceValid(string codonSequence)
{
	if(codonSequence.length() == 0)
		return false;

	if(codonSequence.length() % 3 != 0)
		return false;

	for(int charID = 0; charID < codonSequence.length(); charID++)
		if(codonSequence[charID]!= 'A' && codonSequence[charID]!= 'C' &&
			codonSequence[charID]!= 'G' && codonSequence[charID]!= 'U')
			return false;

	return true;
}

string GetCodonSequence()
{
	string codonSequence;

	while(true)
	{
		codonSequence = getLine("Input codon sequence: ");

		if(IsCodonSequenceValid(codonSequence)) break;

		cout << "Codon sequence must only include letters 'A','C','G','U' and length must be 3n (n>0)" << endl;
	}

	cout << endl;
	return codonSequence;
}

Vector<Vector<string>> GetNLengthCodonSequences(Set<string> codons, int nToPick)
{
	Vector<Vector<string>> result;

	if(nToPick == 0)
	{
		result.add(Vector<string>());
		return result;
	}

	foreach(string codon in codons)
		foreach(Vector<string> codonSequence in GetNLengthCodonSequences(codons - codon, nToPick - 1))
		{
			codonSequence.add(codon);
			result.add(codonSequence);
		}

	return result;
}

void VisitCodonSequences(Set<string> remaining, Vector<string> soFar, string& codonSequence, int nToPick, int& counter)
{
	if(soFar.size() == nToPick)
	{	
		string stringCodonSequence;

		foreach(string codon in soFar)
			stringCodonSequence += codon;

		if(codonSequence == stringCodonSequence);
			counter++;

		cout << soFar << endl;
		return;
	}

	foreach(string codon in remaining)
	{
		Vector<string> soFar_ = soFar;
		soFar_.add(codon);
		VisitCodonSequences(remaining - codon, soFar_, codonSequence, nToPick, counter);
	}
}

Set<string> GetNLengthCodonSequences(Map<char, Set<string>>& proteinTocodons, string stringCodonSequence)
{
	Set<string> codons;

	foreach(char protein in proteinTocodons)
		foreach(string codon in proteinTocodons[protein])
			codons.add(codon);


	//int counter = 0;
	//int a = stringCodonSequence.size() / 3;
	//VisitCodonSequences(codons,Vector<string>(), stringCodonSequence, a, counter);

	//cout << counter << endl;

	Set<string> stringCodonSequences;

	foreach(Vector<string> codonSequence in GetNLengthCodonSequences(codons, stringCodonSequence.size() / 3))
	{
		string stringCodonSequence_;

		foreach(string codon in codonSequence)
			stringCodonSequence_ += codon;

		stringCodonSequences.add(stringCodonSequence_);
	}

	return stringCodonSequences;
}

double CalculateChance(Map<char, Set<string>>& proteinTocodons, string codonSequence)
{
	cout << "Generating valid codon sequences (0-5 mins)..." << endl;
	Set<string> proteinSequences = GetNLengthCodonSequences(proteinTocodons, codonSequence);
	cout << "Successfully Generated valid codon sequences" << endl << endl;

	Map<int,char> itrogenousBases;

	itrogenousBases.put(0,'A');
	itrogenousBases.put(1,'C');
	itrogenousBases.put(2,'G');
	itrogenousBases.put(3,'U');

	int counter = 0;

	for(int charID = 0; charID < codonSequence.length(); charID++)
		for(int itrogenousBaseID = 0; itrogenousBaseID < itrogenousBases.size(); itrogenousBaseID++)
			if(proteinSequences.contains(codonSequence.substr(0,charID) +
				itrogenousBases[itrogenousBaseID] +
				codonSequence.substr(charID + 1)))
				counter++;

	return 100 * (double)counter/proteinSequences.size();
}

int main() 
{
	PrintStartingInfo();

	string inputFile = "codons.txt";
	string codonSequence = GetCodonSequence();

    Map<char, Set<string>> proteinTocodons = loadCodonMap(inputFile);
	
	double chance = CalculateChance(proteinTocodons, codonSequence);
	cout << "Chance of getting another protein from mutation is: " << chance << endl << endl;

	getLine("Press ENTER to continue");

    return 0;
}