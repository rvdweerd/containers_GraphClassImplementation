#pragma once
#include <string>
#include <set>
#include <map>
#include <queue>

class SimpGraph
{
private:
	typedef long long int LL;
	struct Arc;
	struct Node
	{
		Node(LL n)
			:
			id(n),
			coord({ n>>32, (n<<32)>>32 })
		{
			name = "(" + std::to_string(coord.first) + "," + std::to_string(coord.second) + ")";
		}
		std::string name;
		LL id;
		std::pair<LL, LL> coord;
		std::set<Arc*> arcs;
		float height = 0;
		int distanceToTop = 0;
	};
	struct Arc
	{
		Arc(Node* s, Node* f, float c)
			:
			start(s),
			finish(f),
			cost(c)
		{
		}
		Node* start;
		Node* finish;
		float cost;
	};
public:
	SimpGraph(int width, int height) : fieldWidth_(width), fieldHeight_(height) {
		InitializeAsGrid({ width,height });
	}
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
	void PrintAdjacencyList();
	void PlotPath(std::vector<std::pair<LL, LL>> path);
	void ResetGridAndPlaceObstacleHills(std::vector<std::pair<int, int>> obstacleGridLocations, float peakCost, int spread);
	float findShortestPath(std::pair<LL, LL> startcell, std::pair<LL, LL> endcell, std::vector<std::pair<LL, LL>>& pathCoords, std::vector<std::string>& pathNames) {
		LL id1 = startcell.first << 32 | startcell.second;
		LL id2 = endcell.first << 32 | endcell.second;
		std::vector<Arc*> arcPath = findShortestPath(nodeMap[id1], nodeMap[id2]);
		float cost = 0;
		for (auto a : arcPath) {
			pathCoords.push_back(a->start->coord);
			pathNames.push_back(a->start->name);
			cost += a->cost;
		}
		pathCoords.push_back(arcPath.back()->finish->coord);
		pathNames.push_back(arcPath.back()->finish->name);
		return cost;
	}

private:
	void InitializeAsGrid(std::pair<int, int> WxH);
	void AddNode(std::pair<LL, LL> pos);
	void AddNode(LL id);
	void AddArc(Node* start, Node* finish, int cost);
	void AddOneWayConnection(std::pair<LL, LL> n1, std::pair<LL, LL> n2, int c);
	void AddTwoWayConnection(std::pair<LL, LL> n1, std::pair<LL, LL> n2, int c);
	void PlaceObstacleCellOnly(std::pair<LL, LL> node, float cost);
	void PlaceObstacleHillUsingBFS(std::pair<LL, LL> startcell, float initial_cost, int hill_size);
	void PlaceObstacleHillUsingBFS(Node* startnode, float initial_cost, int hill_size);
	void priceEdgesUsingBFS(int hill_size, float cost_step);
	void VisitedPrintFunction(Node* node);
	void ResetGrid();
	void DFS(std::pair<LL, LL> startcell);
	void DFS(Node* startnode);
	void BFS(std::pair<LL, LL> startcell);
	void BFS(Node* startnode);
	void visitUsingDFS(Node* node);
	void visitUsingBFS();
	struct GreaterPathLength
	{
		bool operator()(const std::vector<Arc*>& lhs, const std::vector<Arc*>& rhs) const
		{
			return getPathCost(lhs) > getPathCost(rhs);
		}
	};
	std::vector<Arc*> findShortestPath(Node* start, Node* finish);
	static int getPathCost(const std::vector<Arc*>& path);

private:
	int fieldWidth_;
	int fieldHeight_;
	std::vector<std::pair<int,int>> obstacleCenters;
	std::map<LL, Node*> nodeMap;
	std::set<Node*> nodes;
	std::set<Arc*> arcs;
	std::set<Node*> visited;
	std::queue<Node*> tovisit;
};