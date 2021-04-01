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

#include "simpio.h"
#include "vector.h"

using namespace std;

struct City
{
	string name;
	int population;

	City() { }

	City(string name_, int population_)
	{
		name = name_;
		population = population_;
	}
};

void PrintStartingInfo()
{
	cout << "UNIVERSAL HEALTH COVERAGE PRO" << endl;
	cout << "Create hospitals and we will choose best combination out of them" << endl << endl;
	
	getLine("Press ENTER to continue\n");
}

bool ContainsCity(Vector<City> cities, City city)
{
	foreach(City city_ in cities)
		if(city_.name == city.name)
			return true;

	return false;
}

int GetCoveredAmount(Vector<Vector<City>> hospitals)
{	
	Vector<City> coveredCities;

	for(int hospitalID = 0; hospitalID < hospitals.size(); hospitalID++)
	{
		cout << "Hospital ID " << hospitalID << ": ";

		foreach(City city in hospitals[hospitalID])
		{
			cout << city.name << "-" << city.population << " ";

			if(ContainsCity(coveredCities, city) == false)
				coveredCities.add(city);
		}

		cout << endl;
	}

	int coveredPopulation = 0;

	foreach(City coveredCity in coveredCities)
		coveredPopulation += coveredCity.population;	

	cout << "Total covered population: " << coveredPopulation << endl << endl;

	return coveredPopulation;
}

void CheckCombinationsOfHospitals(
								Vector<Vector<City>> remainingHospitals,
								Vector<Vector<City>> pickedHospitals,
								int nToPick,
								int& maxCoveredPopulation,
								Vector<Vector<City>>& result)
{
	if (nToPick == 0)
	{
		int coveredPopulation = GetCoveredAmount(pickedHospitals);
		
		if(coveredPopulation > maxCoveredPopulation)
		{
			maxCoveredPopulation = coveredPopulation;
			result = pickedHospitals;
		}

		return;
	}
	if (nToPick > remainingHospitals.size()) 
		return;

	Vector<City> hospital = remainingHospitals[0];
	remainingHospitals.remove(0);

	CheckCombinationsOfHospitals(remainingHospitals, pickedHospitals, nToPick, maxCoveredPopulation, result);

	pickedHospitals.add(hospital);

	CheckCombinationsOfHospitals(remainingHospitals, pickedHospitals, nToPick - 1, maxCoveredPopulation, result);
}

Vector<Vector<City>> GetHospitals()
{
	Vector<Vector<City>> hospitals;

	int hospitalCount = getInteger("How many hospitals do you want to create: ");

	cout << endl << "Do not repeat city names" << endl << endl;

	for(int hospitalID = 0; hospitalID < hospitalCount; hospitalID++)
	{
		Vector<City> hospital;

		cout << "Hospital ID " << hospitalID << ":" << endl;

		while(true)
		{
			// Dont repeat city names, I'm using vector
			string cityName = getLine("Enter city name (leave blank to stop): ");
			if(cityName == "") break;
			
			int cityPopulation = getInteger("Enter city population (n>0): ");

			hospital.add(City(cityName,cityPopulation));
		}

		cout << endl;

		hospitals.add(hospital);
	}

	return hospitals;
}

int main() 
{
	PrintStartingInfo();

	Vector<Vector<City>> hospitals = GetHospitals();
	Vector<Vector<City>> result;

	int maxCoveredPopulation = 0;
	int maxHospitals =3;

	CheckCombinationsOfHospitals(hospitals, Vector<Vector<City>>(), maxHospitals, maxCoveredPopulation, result);

	cout << endl << "Best Hospital Combination" << endl;
	GetCoveredAmount(result);

	getLine("\nPress ENTER to continue");

    return 0;
}