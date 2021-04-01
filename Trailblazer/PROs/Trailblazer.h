#ifndef Trailblazer_Included
#define Trailblazer_Included

#include "TrailblazerTypes.h"
#include "set.h"
#include "grid.h"

Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world,
						 double costFunction(Loc one, Loc two, Grid<double>& world),
						 double heuristic(Loc start, Loc end, Grid<double>& world));

Set<Edge> createMaze(int numRows, int numCols);

#endif