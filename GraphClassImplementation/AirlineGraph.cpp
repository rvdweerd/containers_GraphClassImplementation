#include "graphtypes.h"

void printAdjacencyList(SimpleGraph& g);
void initAirlineGraph(SimpleGraph& airline);
void addFlight(SimpleGraph& airline, std::string c1, std::string c2, int miles);
void addNode(SimpleGraph& g, std::string name);
void addArc(SimpleGraph& g, Node* n1, Node* n2, double cost);

int main()
{
	SimpleGraph airline;
	initAirlineGraph(airline);
	printAdjacencyList(airline);

	std::cin.get();
	return 0;
}

void printAdjacencyList(SimpleGraph& g)
{
	for (Node* n : g.nodes)
	{
		std::cout << n->name << " D("<<n->arcs.size()<<") -> ";
		for (Arc* a : n->arcs)
		{
			std::cout << a->finish->name<<",";
		}
		std::cout << std::endl;
	}
}

void initAirlineGraph(SimpleGraph& airline)
{
	addNode(airline, "Atlanta");
	addNode(airline, "Boston");
	addNode(airline, "Chicago");
	addNode(airline, "Dallas");
	addNode(airline, "Denver");
	addNode(airline, "Los Angeles");
	addNode(airline, "New York");
	addNode(airline, "Portland");
	addNode(airline, "San Francisco");
	addNode(airline, "Seattle");
	addFlight(airline, "Atlanta", "Chicago", 599);
	addFlight(airline, "Atlanta", "Dallas", 725);
	addFlight(airline, "Atlanta", "New York", 756);
	addFlight(airline, "Boston", "New York", 191);
	addFlight(airline, "Boston", "Seattle", 2489);
	addFlight(airline, "Chicago", "Denver", 907);
	addFlight(airline, "Dallas", "Denver", 650);
	addFlight(airline, "Dallas", "Los Angeles", 1240);
	addFlight(airline, "Dallas", "San Francisco", 1468);
	addFlight(airline, "Denver", "San Francisco", 954);
	addFlight(airline, "Portland", "San Francisco", 550);
	addFlight(airline, "Portland", "Seattle", 130);
}

void addFlight(SimpleGraph& airline, std::string c1, std::string c2, int miles)
{
	addArc(airline, airline.nodeMap[c1], airline.nodeMap[c2], miles);
	addArc(airline, airline.nodeMap[c2], airline.nodeMap[c1], miles);
}

void addNode(SimpleGraph& g, std::string name)
{
	Node* pNode = new Node;
	pNode->name = name;
	g.nodes.insert(pNode);
	g.nodeMap[name] = pNode;
}

void addArc(SimpleGraph& g, Node* n1, Node* n2, double cost)
{
	Arc* pArc = new Arc;
	pArc->start = n1;
	pArc->finish = n2;
	pArc->cost = cost;
	g.arcs.insert(pArc);
	n1->arcs.insert(pArc);
}
