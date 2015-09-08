#include <vector>

struct Node
{
	int id;
	std::vector<Node> children;
};

struct Edge
{
	int _from;
	int _to;
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
	void removeEdge(int, int);
	int getNodeCount();
	int getEdgeCount();
	Node getNode(int);
	int getSubTreeSize(Node);
	int getFirstLevelChildrenCount(Node);
	void printAdjacencyMatrix();
	void printEdges();
};
