#include "graphtypes.h"
#include <iostream>

void Initialize(SimpGraph& graph)
{
	int width = 3;
	int height = 3;
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
}

int main()
{
	SimpGraph graph;
	Initialize(graph);
	
	std::cout << "Running some tests:\n";

	std::cout << "\nPrinting the adjacency list\n";
	graph.PrintAdjacencyList();
	
	std::cout << "\nTraversing BFS, starting at (0,0)\n";
	graph.BFS({ 0,0 });

	std::cout << "\nTraversing DFS, starting at (0,0)\n";
	graph.DFS({ 0,0 });

	std::cout << "\nFinding shortest path from (0,1) to (2,1)\n";
	int n = 0;
	for (auto a : graph.findShortestPath({0,1}, {2,1}))
	{
		std::cout << a->start->name << " -> " << a->finish->name << " (" << a->cost << ")\n";
		n += a->cost;
	}
	std::cout << "total distance: " << n;

	// Place obstacle on (1,1)
	graph.PlaceObstacle({ 1,1 });
	std::cout << "\nFinding shortest path from (0,1) to (2,1)\n";
	n = 0;
	for (auto a : graph.findShortestPath({ 0,1 }, { 2,1 }))
	{
		std::cout << a->start->name << " -> " << a->finish->name << " (" << a->cost << ")\n";
		n += a->cost;
	}
	std::cout << "total distance: " << n;
		
	std::cin.get();
}