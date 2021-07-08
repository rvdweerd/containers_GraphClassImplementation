#include "SimpleGraph.h"
#include <iostream>
#include <crtdbg.h>
#include <random>
#define _CRTDBG_MAP_ALLOC  

struct MemoryAllocationMetrics {
	size_t totalAllocated = 0;
	size_t totalFreed = 0;
	size_t currentMemoryUsage() {
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
	for (size_t i = 1; i < 10; i++) {
		PrintMemoryUsage();
		float density = 0.002f*i;
		int numObstacles = int(w * h * density);
		float obstacleHeight = 1000; // height of the cost hill
		int obstacleRadius = 8; // radius of the cost hill on the field
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrX(0, w - 1);
		std::uniform_int_distribution<> distrY(0, h - 1);

		// Instantiate the graph of the field
		SimpGraph graph({ w, h });
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
		float totalCost = graph.findShortestPath({ 0,0 }, { w - 1,h - 1 }, pathCoords, pathNames);

		std::cout << "\nExample object avoidance path:" << totalCost << "\n\n";
		graph.PlotPath(pathCoords);
		std::cout << "\nTotal cost of avoidance path:" << totalCost << "\n\n";
		std::cin.get();
	}
}

void Test2() {
	// set 1: density 0.005, obsHeight 10, obsRadius 8, decay 0.75
	//                                              50
	int w = 31;
	int h = 19;

	float density = 0.005f;
	int numObstacles = int(w * h * density);
	float obstacleHeight = 10; // height of the cost hill
	int obstacleRadius = 1; // radius of the cost hill on the field
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrX(0, w - 1);
	std::uniform_int_distribution<> distrY(0, h - 1);

	// Instantiate the graph of the field
	SimpGraph graph({ w, h });
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
	float totalCost = graph.findShortestPath({ w/2,0 }, { w/2,h - 1 }, pathCoords, pathNames);

	std::cout << "\nExample object avoidance path:" << totalCost << "\n\n";
	graph.PlotPath(pathCoords);
	std::cout << "\nTotal cost of avoidance path:" << totalCost << "\n\n";
}

void Test3() {
	// set 1: density 0.005, obsHeight 10, obsRadius 8, decay 0.75
	//                                              50
	int w = 15;
	int h = 9;

	float obstacleHeight = 10; // height of the cost hill
	int obstacleRadius = 0; // radius of the cost hill on the field

							// Instantiate the graph of the field
	SimpGraph graph({ w, h });
	// Place random obstacles on the field
	std::vector<std::pair<int, int>> obstacleCoordinates = { {9,4},{10,2},{10,6},{12,5} };
	
	graph.ResetGridAndPlaceObstacleHills(obstacleCoordinates, obstacleHeight, obstacleRadius);

	// Run lowest cost path and display results
	std::cout << "Field size: (w=" << w << ",h=" << h << "), " << w * h << " nodes. ";
	PrintMemoryUsage();
	//graph.PrintAdjacencyList();

	std::vector<std::pair<long long int, long long int>> pathCoords;
	std::vector<std::string> pathNames;
	float totalCost = graph.findShortestPath({ w / 2,h/2 }, { w -1,h /2 }, pathCoords, pathNames);

	std::cout << "\nExample object avoidance path:" << totalCost << "\n\n";
	graph.PlotPath(pathCoords);
	std::cout << "\nTotal cost of avoidance path:" << totalCost << "\n\n";
}

void Test4(std::vector<std::vector<std::pair<int, int>>> obstacleCoordinatesSet) {
	// set 1: density 0.005, obsHeight 10, obsRadius 8, decay 0.75
	//                                              50
	PrintMemoryUsage();
	int w = 23;
	int h = 15;
	// Instantiate the graph of the field
	SimpGraph graph({ w, h });
	graph.AddGoalNodes();
	float obstacleHeight = 10; // height of the cost hill
	for (std::vector<std::pair<int, int>> obstacleCoordinates : obstacleCoordinatesSet) {
		for (int obstacleRadius = 1; obstacleRadius < 2; obstacleRadius++) { // radius of the cost hill on the field
			// Place obstacles on the field
			/*for (int x = 0; x < w; x++) {
				for (int y : {1, h-1}) {
					obstacleCoordinates.push_back({ x,y });
				}
			}*/
			
			graph.ResetGridAndPlaceObstacleHills(obstacleCoordinates, obstacleHeight, obstacleRadius);
			
			// Run lowest cost path and display results
			std::cout << "Field size: (w=" << w << ",h=" << h << "), " << w * h << " nodes. ";
			std::cout << "\nObstacle radius: " << obstacleRadius;
			PrintMemoryUsage();
			//graph.PrintAdjacencyList();

			std::vector<std::pair<long long int, long long int>> pathCoords;
			std::vector<std::string> pathNames;
			float totalCost = graph.findShortestPath({ w / 2,h / 2 }, { w ,h / 2 }, pathCoords, pathNames);

			std::cout << "\nExample object avoidance path:" << totalCost << "\n\n";
			graph.PlotPath(pathCoords);
			std::cout << "\nTotal cost of avoidance path:" << totalCost << "\n\n";
			std::cin.get();
		}
	}
}


int main()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	
	/*Test1();
	for (int i = 0; i < 50; i++) {
		Test2();
		std::cin.get();
	}*/
	{
		std::vector<std::vector<std::pair<int, int>>> obstacleCoordinatesSet = {
		{ {15,7},{18,9},{18,4},{20,8} }, // Example 1a
		{ {15,7},{18,9},{18,5},{20,8} }, // Example 1b
		{ {20,5},{20,9},{17,8},{14,7} }, // Example 2
		{ {14,9},{14,5},{17,8},{20,7} }, // Example 5
		//{ {14,9},{14,5},{17,8},{20,7} },
		};
		//Test1();
		Test4(obstacleCoordinatesSet);
	}
	std::cin.get();
	_CrtDumpMemoryLeaks();
}