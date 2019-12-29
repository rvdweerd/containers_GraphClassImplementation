#include "graphtypes.h"

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
	graph.PrintAdjacencyList();
}

int main()
{
	SimpGraph graph;
	Initialize(graph);
	graph.PrintAdjacencyList();
	graph.BFS("Boston");

}


