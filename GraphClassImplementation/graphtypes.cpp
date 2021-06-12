#include "graphtypes.h"
#include <iostream>
#include <queue>

void SimpGraph::AddNode(std::pair<long long int, long long int> pos)
{
	long long int id = (pos.first<<32) | pos.second;
	Node* newnode = new Node(id);
	nodeMap[id] = newnode;
	nodes.insert(newnode);
}

void SimpGraph::AddNode(long long int id)
{
	Node* newnode = new Node(id);
	nodeMap[id] = newnode;
	nodes.insert(newnode);
}

void SimpGraph::AddArc(Node* start, Node* finish, int cost)
{
	Arc* newarc = new Arc(start, finish, cost);
	start->arcs.insert(newarc);
	arcs.insert(newarc);
}

void SimpGraph::AddOneWayConnection(std::pair<long long int, long long int> n1, std::pair<long long int, long long int> n2, int c)
{
	long long int id1 = n1.first << 32 | n1.second;
	long long int id2 = n2.first << 32 | n2.second;
	if (nodeMap.find(id1) == nodeMap.end())
	{
		AddNode(id1);
	}
	if (nodeMap.find(id2) == nodeMap.end())
	{
		AddNode(id2);
	}
	AddArc(nodeMap[id1], nodeMap[id2], c);
}
void SimpGraph::AddTwoWayConnection(std::pair<long long int, long long int> n1, std::pair<long long int, long long int> n2, int c)
{
	long long int id1 = n1.first << 32 | n1.second;
	long long int id2 = n2.first << 32 | n2.second;
	if (nodeMap.find(id1) == nodeMap.end())
	{
		AddNode(id1);
	}
	if (nodeMap.find(id2) == nodeMap.end())
	{
		AddNode(id2);
	}
	AddArc(nodeMap[id1], nodeMap[id2], c);
	AddArc(nodeMap[id2], nodeMap[id1], c);
}

void SimpGraph::PrintAdjacencyList()
{
	for (Node* n : nodes)
	{
		std::cout << n->id << " (" << n->arcs.size() << ") -> ";
		for (Arc* a : n->arcs)
		{
			std::cout << a->finish->id << "(" << a->cost << "),";
		}
		std::cout << std::endl;
	}
}

void SimpGraph::DFS(std::pair<long long int, long long int> startcell)
{
	long long int id = startcell.first << 32 | startcell.second;
	if (nodeMap.find(id) != nodeMap.end())
	{
		DFS(nodeMap[id]);
	}
}

void SimpGraph::DFS(Node* startnode)
{
	visited.clear();
	visitUsingDFS(startnode);
}

void SimpGraph::BFS(std::pair<long long int, long long int> startcell)
{
	long long int id = startcell.first << 32 | startcell.second;
	if (nodeMap.find(id) != nodeMap.end())
	{
		BFS(nodeMap[id]);
	}
}

void SimpGraph::BFS(Node* startnode)
{
	visited.clear();
	while (!tovisit.empty()) tovisit.pop();
	tovisit.push(startnode);
	visited.insert(startnode);
	visitUsingBFS();
}

void SimpGraph::VisitFunction1(Node* node)
{
	std::cout << node->name << " visited.\n";
}

std::vector<SimpGraph::Arc*> SimpGraph::findShortestPath(Node* start, Node* finish)
{
	std::vector<Arc*> path;
	std::priority_queue< std::vector<Arc*>, std::vector<std::vector<Arc*>>, GreaterPathLength> queue;
	std::map<long long int, int> fixed;
	while (start != finish)
	{
		if (fixed.find(start->id) == fixed.end())
		{
			fixed[start->id] = getPathCost(path);
			for (Arc* arc : start->arcs)
			{
				if (fixed.find(arc->finish->id) == fixed.end())
				{
					path.push_back(arc);
					queue.push(path);
					path.pop_back();
				}
			}
		}
		if (queue.size() == 0)
		{
			path.clear();
			return path;
		}
		path = queue.top(); queue.pop();
		start = path[path.size() - 1]->finish;
	}
	return path;
}

int SimpGraph::getPathCost(const std::vector<Arc*>& path)
{
	int cost = 0;
	for (Arc* arc : path)
	{
		cost += arc->cost;
	}
	return cost;
}

void SimpGraph::visitUsingDFS(Node* node)
{
	if (visited.find(node) == visited.end())
	{
		VisitFunction1(node);
		visited.insert(node);
		for (Arc* a : node->arcs)
		{
			visitUsingDFS(a->finish);
		}
	}
	else
	{
		return;
	}
}

void SimpGraph::visitUsingBFS()
{
	while (!tovisit.empty())
	{
		Node* nextnode = tovisit.front();
		tovisit.pop();
		VisitFunction1(nextnode);

		for (Arc* a : nextnode->arcs)
		{
			if (visited.find(a->finish) == visited.end())
				tovisit.push(a->finish);
			visited.insert(a->finish);
		}
	}
	return;
}

void SimpGraph::PlaceObstacle(std::pair<long long int, long long int> n) {
	long long int id = (n.first << 32) | n.second;
	for (auto e : nodeMap[id]->arcs) {
		e->cost = 100;
	}
}