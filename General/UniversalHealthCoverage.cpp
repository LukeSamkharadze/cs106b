/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>

#include "set.h"
#include "vector.h"
#include "console.h"

using namespace std;

bool canOfferUniversalCoverage(
							   Set<string>& cities,Vector<Set<string>>& locations,
							   int numHospitals,
							   Vector<Set<string>>& result)
{
	if(cities.size() == 0)
		return true;
	if(numHospitals == 0)
		return false;

	for(int hospitalID = 0; hospitalID < locations.size(); hospitalID++)
	{
		Vector<Set<string>> newLocations = locations;
		newLocations.remove(hospitalID);

		if(canOfferUniversalCoverage(cities - locations[hospitalID], newLocations, numHospitals-1, result))
		{
			result.add(locations[hospitalID]);
			return true;
		}

		result.clear();
	}

	return false;
}

void SetupHospitalsAndCities(Set<string>& cities, Vector<Set<string>>& hospitals)
{
	cities.add("A");
	cities.add("B");
	cities.add("C");
	cities.add("D");
	cities.add("E");
	cities.add("F");

	Set<string> hospital1;
	hospital1.add("A");
	hospital1.add("B");
	hospital1.add("C");

	Set<string> hospital2;
	hospital2.add("A");
	hospital2.add("C");
	hospital2.add("D");

	Set<string> hospital3;
	hospital3.add("B");
	hospital3.add("F");

	Set<string> hospital4;
	hospital4.add("C");
	hospital4.add("E");
	hospital4.add("F");

	hospitals.add(hospital1);
	hospitals.add(hospital2);
	hospitals.add(hospital3);
	hospitals.add(hospital4);
}

int main() 
{
	Set<string> cities;
	Vector<Set<string>> hospitals;
	Vector<Set<string>> result;

	int maxHospitals = 3;

	SetupHospitalsAndCities(cities, hospitals);

	cout << canOfferUniversalCoverage(cities, hospitals, maxHospitals, result) << endl;

	for(int i = 0; i < result.size(); i++)
		cout << result[i] << endl;

    return 0;
}
