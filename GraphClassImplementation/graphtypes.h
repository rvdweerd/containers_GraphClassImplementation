#include <string>
#include <iostream>
#include <set>
#include <map>

struct Node;
struct Arc;

struct SimpleGraph
{
	std::set<Node*> nodes;
	std::set<Arc*> arcs;
	std::map<std::string, Node*> nodeMap;
};

struct Node
{
	std::string name;
	std::set<Arc*> arcs;
};

struct Arc
{
	Node* start;
	Node* finish;
	double cost;
};