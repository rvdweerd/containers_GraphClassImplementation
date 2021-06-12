#include "graphtypes.h"
#include <iostream>

void Initialize(SimpGraph& graph)
{
	int width = 7;
	int height = 7;
	for (int x = 0; x < width;x++) {
		for (int y = 0; y < height; y++) {
			graph.AddNode({ x,y });
		}
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height-1; y++) {
			graph.AddTwoWayConnection({ x,y }, { x, y + 1 },1);
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width- 1; x++) {
			graph.AddTwoWayConnection({ x,y }, { x+1, y }, 1);
		}
	}

	std::vector<std::pair<long long int, long long int>> obstacles = {
		{1,1},{2,1},{3,1},{4,1},{5,1},
		{1,2},
		{1,3},{4,3},{5,2},{6,3},
		{1,4},
		{3,5},
		{3,6}
	};
	for (auto o : obstacles) {
		graph.PlaceObstacle(o);
	}
}

int main()
{
	SimpGraph graph;
	Initialize(graph);
	
	std::cout << "Running some tests:\n";

	std::cout << "\nPrinting the adjacency list\n";
	graph.PrintAdjacencyList();
	
	std::cout << "\nFinding shortest path from (0,0) to (6,6)\n";
	int n = 0;
	for (auto a : graph.findShortestPath({0,0}, {6,6}))
	{
		std::cout << a->start->name << " -> " << a->finish->name << " (" << a->cost << ")\n";
		n += a->cost;
	}
	std::cout << "total distance: " << n;
	std::cin.get();
}