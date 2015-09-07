#include <vector>

struct Node
{
	int id;
};

struct Edge
{
	int from;
	int to;
};

class Graph
{
private:
	int nodeCount;
	std::vector<Node> nodes;
	std::vector<Edge> edges;
	std::vector<std::vector<int>> adjacencyMatrix;
public:
	Graph();
	Graph(int);
	void addEdge(int, int);
	int getNodeCount();
	int getEdgeCount();
	void printAdjacencyMatrix();
	void printEdges();
};
