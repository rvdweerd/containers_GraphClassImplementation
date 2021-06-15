#include "SimpleGraph.h"
#include <iostream>
#include <queue>

void SimpGraph::AddNode(std::pair<LL, LL> pos)
{
	LL id = (pos.first<<32) | pos.second;
	Node* newnode = new Node(id);
	nodeMap[id] = newnode;
	nodes.insert(newnode);
}

void SimpGraph::AddNode(LL id)
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

void SimpGraph::AddOneWayConnection(std::pair<LL, LL> n1, std::pair<LL, LL> n2, int c)
{
	LL id1 = n1.first << 32 | n1.second;
	LL id2 = n2.first << 32 | n2.second;
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

void SimpGraph::AddTwoWayConnection(std::pair<LL, LL> n1, std::pair<LL, LL> n2, int c)
{
	LL id1 = n1.first << 32 | n1.second;
	LL id2 = n2.first << 32 | n2.second;
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
	std::cout << "Adjacency List:\n";
	for (Node* n : nodes)
	{
		std::cout << n->name << " degree=(" << n->arcs.size() << ") -> ";
		for (Arc* a : n->arcs)
		{
			std::cout << a->finish->name << "(" << a->cost << "),";
		}
		std::cout << std::endl;
	}
}

void SimpGraph::PlotPath(std::vector<std::pair<LL, LL>> path)
{
	// Find maximum cost of an edge
	float maxCost = 0;

	// Fill matrix with cost levels of each node
	std::vector<std::vector<float>> fieldCellCost(fieldHeight_, std::vector<float>(fieldWidth_, 0.f));
	for (auto e : arcs) {
		int y = (int)e->finish->coord.second;
		int x = (int)e->finish->coord.first;
		fieldCellCost[y][x] += e->cost;
		if (fieldCellCost[y][x] > maxCost) maxCost = fieldCellCost[y][x];
	}
	// Create field matrix and fill with shadings according to cost level
	std::vector<std::vector<char>> field(fieldHeight_, std::vector<char>(fieldWidth_, '.'));
	for (int y = 0; y < field.size(); y++) {
		for (int x = 0; x < field[0].size(); x++) {
			float fraction = fieldCellCost[y][x] / maxCost;
			if (fraction > 0.75) field[y][x] = 178;
			else if (fraction > 0.5) field[y][x] = 177;
			else if (fraction > 0.25) field[y][x] = 176;
		}
	}
	// Plot path
	for (auto coord : path) {
		field[(int)coord.second][(int)coord.first] = 'x';
	}
	// Plot Obstacles
	for (auto coord : obstacleCenters) {
		field[coord.second][coord.first] = 'R';
	}
	// Print to console
	for (auto row : field) {
		for (char c : row) {
			std::cout << c;
		}
		std::cout << '\n';
	}
}

void SimpGraph::DFS(std::pair<LL, LL> startcell)
{
	LL id = startcell.first << 32 | startcell.second;
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

void SimpGraph::BFS(std::pair<LL, LL> startcell)
{
	LL id = startcell.first << 32 | startcell.second;
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

void SimpGraph::InitializeAsGrid(std::pair<int, int> WxH)
{
	int width = WxH.first;
	int height = WxH.second;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			AddNode({ x,y });
		}
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height - 1; y++) {
			AddTwoWayConnection({ x,y }, { x, y + 1 }, 1);
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width - 1; x++) {
			AddTwoWayConnection({ x,y }, { x + 1, y }, 1);
		}
	}
}

std::vector<SimpGraph::Arc*> SimpGraph::findShortestPath(Node* start, Node* finish)
{
	std::vector<Arc*> arcPath;
	std::priority_queue< std::vector<Arc*>, std::vector<std::vector<Arc*>>, GreaterPathLength> queue;
	std::map<LL, int> fixed;
	while (start != finish)
	{
		if (fixed.find(start->id) == fixed.end())
		{
			fixed[start->id] = getPathCost(arcPath);
			for (Arc* arc : start->arcs)
			{
				if (fixed.find(arc->finish->id) == fixed.end())
				{
					arcPath.push_back(arc);
					queue.push(arcPath);
					arcPath.pop_back();
				}
			}
		}
		if (queue.size() == 0)
		{
			arcPath.clear();
			return arcPath;
		}
		arcPath = queue.top(); queue.pop();
		start = arcPath[arcPath.size() - 1]->finish;
	}
	return arcPath;
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
		VisitedPrintFunction(node);
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
		VisitedPrintFunction(nextnode);

		for (Arc* a : nextnode->arcs)
		{
			if (visited.find(a->finish) == visited.end())
				tovisit.push(a->finish);
			visited.insert(a->finish);
		}
	}
	return;
}

void SimpGraph::VisitedPrintFunction(Node* node)
{
	std::cout << node->name << " visited.\n";
}

void SimpGraph::ResetGridAndPlaceObstacleHills(std::vector<std::pair<int, int>> obstacleGridLocations, float peakCost, int spread)
{
	ResetGrid();
	obstacleCenters = obstacleGridLocations;
	for (auto obstacleLocation : obstacleGridLocations) {
		PlaceObstacleHillUsingBFS(obstacleLocation, peakCost, spread);
	}
}

void SimpGraph::PlaceObstacleCellOnly(std::pair<LL, LL> node, float cost) {
	LL id = (node.first << 32) | node.second;
	for (auto e : nodeMap[id]->arcs) {
		e->cost += cost;
	}
}

void SimpGraph::PlaceObstacleHillUsingBFS(std::pair<LL, LL> startcell, float initial_cost, int hill_size)
{
	LL id = startcell.first << 32 | startcell.second;
	if (nodeMap.find(id) != nodeMap.end())
	{
		PlaceObstacleHillUsingBFS(nodeMap[id],initial_cost, hill_size);
	}

}

void SimpGraph::PlaceObstacleHillUsingBFS(Node* startnode, float initial_cost, int hill_size)
{
	float cost_step = (initial_cost) / (float)hill_size;
	visited.clear();
	while (!tovisit.empty()) tovisit.pop();
	startnode->height = initial_cost;
	startnode->distanceToTop = 0;
	tovisit.push(startnode);
	visited.insert(startnode);
	priceEdgesUsingBFS(hill_size, cost_step);
}

void SimpGraph::priceEdgesUsingBFS(int hill_size, float cost_step)
{
	while (!tovisit.empty())
	{
		Node* current_node = tovisit.front();
		tovisit.pop();
		//VisitedPrintFunction(nextnode);

		float currentCost = current_node->height - cost_step;
		for (Arc* a : current_node->arcs)
		{
			if (current_node->distanceToTop <= hill_size)
			{
				a->cost += current_node->height;
				if (visited.find(a->finish) == visited.end())
				{
					a->finish->height = currentCost;
					a->finish->distanceToTop = current_node->distanceToTop + 1;
					tovisit.push(a->finish);
				}
				visited.insert(a->finish);
			}
		}
	}
	return;
}

void SimpGraph::ResetGrid() {
	for (auto e : arcs) {
		e->cost = 1;
	}
	obstacleCenters.clear();
}