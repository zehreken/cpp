#include "Graph.h"
#include <iostream>

Graph::Graph(int _v)
{
	nodeCount = _v;

	for (int i = 0; i < nodeCount; ++i)
	{
		Node node;
		node.id = i + 1;
		nodes.push_back(node);
	}

	adjacencyMatrix = std::vector<std::vector<int>>(nodeCount, std::vector<int>(nodeCount));
}

void Graph::addEdge(int _from, int _to)
{
	Edge edge;
	edge.from = _from;
	edge.to = _to;

	edges.push_back(edge);

	adjacencyMatrix[_from - 1][_to - 1] = adjacencyMatrix[_to - 1][_from - 1] = 1;
}

int Graph::getNodeCount()
{
	return nodes.size();
}

int Graph::getEdgeCount()
{
	return edges.size();
}

void Graph::printAdjacencyMatrix()
{
	for (int i = 0; i < nodeCount; ++i)
	{
		for (int j = 0; j < nodeCount; ++j)
		{
			std::cout << adjacencyMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Graph::printEdges()
{
	for (int i = 0; i < getEdgeCount(); ++i)
	{
		std::cout << edges[i].from << " -> " << edges[i].to << std::endl;
	}
}
