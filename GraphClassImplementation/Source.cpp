#include "graphtypes.h"
#include <iostream>

void Initialize(SimpGraph& graph)
{
	graph.AddNode("Atlanta");
	graph.AddNode("Boston");
	graph.AddNode("Chicago");
	graph.AddNode("Dallas");
	graph.AddNode("Denver");
	graph.AddNode("Los Angeles");
	graph.AddNode("New York");
	graph.AddNode("Portland");
	graph.AddNode("San Francisco");
	graph.AddNode("Seattle");
	graph.AddTwoWayConnection("Atlanta", "Chicago", 599);
	graph.AddTwoWayConnection("Atlanta", "Dallas", 725);
	graph.AddTwoWayConnection("Atlanta", "New York", 756);
	graph.AddTwoWayConnection("Boston", "New York", 191);
	graph.AddTwoWayConnection("Boston", "Seattle", 2489);
	graph.AddTwoWayConnection("Chicago", "Denver", 907);
	graph.AddTwoWayConnection("Dallas", "Denver", 650);
	graph.AddTwoWayConnection("Dallas", "Los Angeles", 1240);
	graph.AddTwoWayConnection("Dallas", "San Francisco", 1468);
	graph.AddTwoWayConnection("Denver", "San Francisco", 954);
	graph.AddTwoWayConnection("Portland", "San Francisco", 550);
	graph.AddTwoWayConnection("Portland", "Seattle", 130);
}

int main()
{
	SimpGraph graph;
	Initialize(graph);
	
	std::cout << "Running some tests:\n";

	std::cout << "\nPrinting the adjacency list\n";
	graph.PrintAdjacencyList();

	std::cout << "\nTraversing BFS, starting at Boston\n";
	graph.BFS("Boston");

	std::cout << "\nTraversing DFS, starting at Boston\n";
	graph.DFS("Boston");

	std::cout << "\nFinding shortest path from Denver to Atlanta\n";
	int n = 0;
	for (auto a : graph.findShortestPath("Denver", "Atlanta"))
	{
		std::cout << a->start->name << " -> " << a->finish->name << " (" << a->cost << ")\n";
		n += a->cost;
	}
	std::cout << "total distance: " << n;

	std::cout << "\n\nFinding shortest path from San Francisco to Boston\n";
	n = 0;
	for (auto a : graph.findShortestPath("San Francisco", "Boston"))
	{
		std::cout << a->start->name << " -> " << a->finish->name << " (" << a->cost << ")\n";
		n += a->cost;
	}
	std::cout << "total distance: " << n;
	
	std::cin.get();
}