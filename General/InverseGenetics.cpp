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

#include "set.h"
#include "map.h"
#include "console.h"

using namespace std;

Set<string> getAllRNAStrands(string protein, Map<char, Set<string>>& codons)
{
	Set<string> result;

	if(protein.length() == 0)
		return result+string();

	foreach(string codon in codons[protein[0]])
		foreach(string otherCodons in getAllRNAStrands(protein.substr(1), codons))
			result += codon + otherCodons;
	
	return result;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string>>& codons)
{
	foreach(string strand in getAllRNAStrands(protein,codons))
		cout << strand << endl;
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

int main() 
{
	string inputFile = "codons.txt";
	string proteinSequence = "KWS";

  Map<char, Set<string> > codons = loadCodonMap(inputFile);
	
	listAllRNAStrandsFor(proteinSequence, codons);

  return 0;
}