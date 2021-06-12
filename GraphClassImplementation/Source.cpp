#include "SimpleGraph.h"
#include <iostream>
#include <crtdbg.h>  
#define _CRTDBG_MAP_ALLOC  

void InitializeAsGrid(SimpGraph& graph, int width=3, int height=3)
{
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

void Test1() {
	SimpGraph graph;
	InitializeAsGrid(graph,7,7);

	std::cout << "\nPrinting the adjacency list\n";
	graph.PrintAdjacencyList();

	std::cout << "\nFinding shortest path from (0,0) to (6,6)\n";
	int n = 0;
	for (auto a : graph.findShortestPath({ 0,0 }, { 6,6 }))
	{
		std::cout << a->start->name << " -> " << a->finish->name << " (" << a->cost << ")\n";
		n += a->cost;
	}
	std::cout << "total distance: " << n;
	
	std::cout << "\n\nRemoving all obstacles...";
	graph.RemoveAllObstacles();
	std::cout << "\nPrinting the adjacency list\n";
	graph.PrintAdjacencyList();
}

int main()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	
	std::cout << "Running some tests:\n";
	Test1();
	
	
	_CrtDumpMemoryLeaks();
	std::cin.get();
}