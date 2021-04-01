#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"

#include "random.h"

using namespace std;

Map<Loc, double> getNeighboursCosts(Loc& startingLocation, Loc& endingLocation, Grid<double>& world, Map<Loc, double>& pathLengths,
									Set<Loc>& alreadyFoundPaths, 
									double costFunction(Loc one, Loc two, Grid<double>& world),
									double heuristic(Loc start, Loc end, Grid<double>& world))
{
	Map<Loc, double> neighboursCosts;

	for(int drow = -1; drow <= 1; drow++)
		for(int dcol = -1; dcol <= 1; dcol++)
			if(dcol != 0 || drow != 0 )
				if(startingLocation.col + dcol >= 0 && startingLocation.col + dcol < world.nCols && 
					startingLocation.row + drow >= 0 && startingLocation.row + drow < world.nRows)
					{
						Loc neighbour = makeLoc(startingLocation.row + drow, startingLocation.col + dcol);
						
						if(costFunction(startingLocation, neighbour, world) == costFunction(startingLocation, neighbour, world) + 1)
							continue;

						neighboursCosts[neighbour] = pathLengths.get(startingLocation) + 
						costFunction(startingLocation, neighbour, world) +
						heuristic(neighbour, endingLocation, world);
					}

	return neighboursCosts;
}

Vector<Loc> getShortestPath(Loc& startLocation, Loc& endLocation, Map<Loc, Loc>& previousLocations)
{
	Vector<Loc> shortestPath;

	Loc currentLocation = endLocation;

	while(currentLocation != startLocation)
	{
		shortestPath.insert(0, currentLocation);
		currentLocation = previousLocations[currentLocation];
	}

	shortestPath.insert(0, startLocation);

	return shortestPath;
}

Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world, 
						 double costFunction(Loc one, Loc two, Grid<double>& world),
						 double heuristic(Loc start, Loc end, Grid<double>& world))
{
	TrailblazerPQueue<Loc> priorityQueue;
	priorityQueue.enqueue(start, 0);

	Map<Loc, double> pathLengths;
	pathLengths.put(start, heuristic(start, end, world));

	Set<Loc> alreadyFoundPathLengths;

	Map<Loc, Loc> previousLocations;

	while(priorityQueue.isEmpty() == false)
	{
		Loc currentLocation = priorityQueue.dequeueMin();
		alreadyFoundPathLengths.add(currentLocation);
		
		pathLengths[currentLocation] -= heuristic(currentLocation, end, world);

		colorCell(world, currentLocation, Color::GREEN);

		if(currentLocation == end)
			return getShortestPath(start, end, previousLocations);

		Map<Loc, double> neighboursCosts = getNeighboursCosts(currentLocation, end, world, pathLengths, alreadyFoundPathLengths, costFunction, heuristic);
		
		foreach(Loc neighbour in neighboursCosts)
		{
			bool isCalculatedAlready = pathLengths.containsKey(neighbour);

			if(alreadyFoundPathLengths.contains(neighbour))
				continue;
			else if(isCalculatedAlready && neighboursCosts[neighbour] < pathLengths[neighbour])
				priorityQueue.decreaseKey(neighbour, neighboursCosts[neighbour]);
			else if(isCalculatedAlready)
				continue;
			else
				priorityQueue.enqueue(neighbour, neighboursCosts[neighbour]);

			pathLengths[neighbour] = neighboursCosts[neighbour];
			previousLocations[neighbour] = currentLocation;

			colorCell(world, neighbour, Color::YELLOW);
		}
	}

	error("Could not find the shortest path");
}

Set<Loc> getNeighbours(Loc location, int numRows, int numCols)
{
	Set<Loc> neighbours;

	for(int drow = -1; drow <= 1; drow++)
		for(int dcol = -1; dcol <= 1; dcol++)
			if(dcol + drow == -1 || dcol + drow == 1)
				if(location.col + dcol >= 0 && location.col + dcol < numCols && location.row + drow >= 0 && location.row + drow < numRows)
					neighbours.add(makeLoc(location.row + drow, location.col + dcol));

	return neighbours;
}

TrailblazerPQueue<Edge> getEdgesPriorityQueue(int numRows, int numCols)
{
	TrailblazerPQueue<Edge> priorityQueue;

	for(int locID = 0; locID < numRows * numCols; locID+=2)
	{
		Loc currentLocation = makeLoc(locID / numCols, locID % numCols);

		foreach(Loc neighbour in getNeighbours(currentLocation, numRows, numCols))
			priorityQueue.enqueue(makeEdge(currentLocation, neighbour), randomReal(0,1));
	}

	return priorityQueue;
}

Map<Loc, Loc> getDefaultLocationParents(int numRows, int numCols)
{
	Map<Loc, Loc> locationParents;

	for(int rowID = 0; rowID < numRows; rowID++)
		for(int colID = 0; colID < numCols; colID++)
			locationParents[makeLoc(rowID, colID)] = makeLoc(rowID, colID);

	return locationParents;
}

Map<Loc, int> getDefaultlocationChildrenCount(int numRows, int numCols)
{
	Map<Loc, int> locationChildrenCount;

	for(int rowID = 0; rowID < numRows; rowID++)
		for(int colID = 0; colID < numCols; colID++)
			locationChildrenCount[makeLoc(rowID, colID)] = 1;

	return locationChildrenCount;
}

Loc getMainParentLocation(Map<Loc, Loc>& locationParents, Loc location)
{
	while(locationParents[location] != location)
		location = locationParents[location];

	return location;
}

void swap(Loc& firstLocation, Loc& secondLocation)
{
	Loc tmp = firstLocation;
	firstLocation = secondLocation;
	secondLocation = tmp;
}

Set<Edge> createMaze(int numRows, int numCols) 
{
	TrailblazerPQueue<Edge> priorityQueue = getEdgesPriorityQueue(numRows, numCols);
	Map<Loc, Loc> locationParents = getDefaultLocationParents(numRows, numCols);
	Map<Loc, int> locationChildrenCount = getDefaultlocationChildrenCount(numRows, numCols);

	Set<Edge> selectedEdges;
	
	while(priorityQueue.isEmpty() == false)
	{
		Edge currentEdge = priorityQueue.dequeueMin();
		
		Loc firstMainParentLocation = getMainParentLocation(locationParents, currentEdge.start);
		Loc secondMainParentLocation = getMainParentLocation(locationParents, currentEdge.end);

		if(firstMainParentLocation == secondMainParentLocation)
			continue;

		if(locationChildrenCount[firstMainParentLocation] < locationChildrenCount[secondMainParentLocation])
			swap(firstMainParentLocation, secondMainParentLocation);

		locationParents[secondMainParentLocation] = firstMainParentLocation;
		locationChildrenCount[firstMainParentLocation] += locationChildrenCount[secondMainParentLocation];

		selectedEdges.add(currentEdge);

		if(locationChildrenCount[firstMainParentLocation] == numRows * numCols)
			break;
	}

    return selectedEdges;
}