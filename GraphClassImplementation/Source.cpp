#include "SimpleGraph.h"
#include <iostream>
#include <crtdbg.h>
#include <random>
#define _CRTDBG_MAP_ALLOC  

struct MemoryAllocationMetrics {
	uint32_t totalAllocated = 0;
	uint32_t totalFreed = 0;
	uint32_t currentMemoryUsage() {
		return totalAllocated - totalFreed;
	}
};

static MemoryAllocationMetrics s_memoryAllocationMetrics;

static void PrintMemoryUsage() {
	std::cout << "Memory usage: " << s_memoryAllocationMetrics.currentMemoryUsage() << " bytes.\n";
}

void* operator new(size_t size) {
	//std::cout << "Allocating " << size << " bytes\n";
	s_memoryAllocationMetrics.totalAllocated += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	s_memoryAllocationMetrics.totalFreed += size;
	free(memory);
}

void Test1() {
	int w = 150;
	int h = 45;
	float density = 0.02;
	int numObstacles = int(w * h * 0.02);
	int obstacleHeight = 100; // height of the cost hill
	int obstacleRadius = 5; // radius of the cost hill on the field
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrX(0, w-1);
	std::uniform_int_distribution<> distrY(0, h-1);

	// Instantiate the graph of the field
	SimpGraph graph({w, h});
	// Place random obstacles on the field
	std::vector<std::pair<int, int>> obstacleCoordinates;
	for (int i = 0; i < numObstacles; i++) {
		int x = distrX(gen);
		int y = distrY(gen);
		obstacleCoordinates.push_back({ x,y });
	}
	graph.ResetGridAndPlaceObstacleHills(obstacleCoordinates, obstacleHeight, obstacleRadius);
	
	// Run lowest cost path and display results
	std::cout << "Field size: (w=" << w << ",h=" << h << "), " << w * h << " nodes. ";
	PrintMemoryUsage();
	//graph.PrintAdjacencyList();

	std::vector<std::pair<long long int, long long int>> pathCoords;
	std::vector<std::string> pathNames;
	int totalCost = graph.findShortestPath({ 0,0 }, { w-1,h-1 }, pathCoords, pathNames);
	
	std::cout << "\nExample object avoidance path:" << totalCost << "\n\n";
	graph.PlotPath(pathCoords);
	std::cout << "\nTotal cost of avoidance path:" << totalCost << "\n\n";
}

int main()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	
	Test1();
	
	_CrtDumpMemoryLeaks();
	std::cin.get();
}