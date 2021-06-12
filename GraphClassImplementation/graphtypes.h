#pragma once
#include <string>
#include <set>
#include <map>
#include <queue>

class SimpGraph
{
public:
	struct Arc;
	struct Node
	{
		Node(long long int n)
			:
			id(n)
		{
			coord.first = n >> 32;
			coord.second = (n << 32) >> 32;
			name = "(" + std::to_string(coord.first) + "," + std::to_string(coord.second) + ")";
		}
		std::string name;
		long long int id;
		std::pair<long long int, long long int> coord;
		std::set<Arc*> arcs;
	};
	struct Arc
	{
		Arc(Node* s, Node* f, int c)
			:
			start(s),
			finish(f),
			cost(c)
		{
		}
		Node* start;
		Node* finish;
		int cost;
	};
public:
	SimpGraph() = default;
	~SimpGraph() {
		for (auto n : nodes) {
			delete n;
			n = nullptr;
		}
		for (auto a : arcs) {
			delete a;
			a = nullptr;
		}

	};
	void AddNode(std::pair<long long int, long long int> pos);
	void AddNode(long long int id);
	void AddArc(Node* start, Node* finish, int cost);
	void AddOneWayConnection(std::pair<long long int, long long int> n1, std::pair<long long int, long long int> n2, int c);
	void AddTwoWayConnection(std::pair<long long int, long long int> n1, std::pair<long long int, long long int> n2, int c);
	void PrintAdjacencyList();
	void DFS(std::pair<long long int, long long int> startcell);
	void DFS(Node* startnode);
	void BFS(std::pair<long long int, long long int> startcell);
	void BFS(Node* startnode);
	void VisitFunction1(Node* node);
	void PlaceObstacle(std::pair<long long int, long long int> n);

	struct GreaterPathLength
	{
		bool operator()(const std::vector<Arc*>& lhs, const std::vector<Arc*>& rhs) const
		{
			return getPathCost(lhs) > getPathCost(rhs);
		}
	};
	std::vector<Arc*> findShortestPath(std::pair<long long int, long long int> startcell, std::pair<long long int, long long int> endcell)
	{
		long long int id1 = startcell.first << 32 | startcell.second;
		long long int id2 = endcell.first << 32 | endcell.second;
		return findShortestPath(nodeMap[id1], nodeMap[id2]);
	}
	std::vector<Arc*> findShortestPath(Node* start, Node* finish);
	static int getPathCost(const std::vector<Arc*>& path);


private:
	void visitUsingDFS(Node* node);
	void visitUsingBFS();

public:
	std::map<long long int, Node*> nodeMap;
	std::set<Node*> nodes;
	std::set<Arc*> arcs;
	std::set<Node*> visited;
	std::queue<Node*> tovisit;
};