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
	edge._from = _from;
	edge._to = _to;
	nodes[_from - 1].children.push_back(nodes[_to - 1]);

	edges.push_back(edge);

	adjacencyMatrix[_from - 1][_to - 1] = adjacencyMatrix[_to - 1][_from - 1] = 1;
}

void Graph::removeEdge(int _from, int _to)
{
	adjacencyMatrix[_from - 1][_to - 1] = adjacencyMatrix[_to - 1][_from - 1] = 0;
}

int Graph::getNodeCount()
{
	return nodes.size();
}

int Graph::getEdgeCount()
{
	return edges.size();
}

Node Graph::getNode(int id)
{
	return nodes[id];
}

int Graph::getSubTreeSize(Node node)
{
	int subTreeSize = 0;
	for (int i = 0; i < node.children.size(); ++i)
	{
		subTreeSize += getSubTreeSize(node.children[i]);
		std::cout << subTreeSize << std::endl;
	}

	return subTreeSize;
}

int Graph::getFirstLevelChildrenCount(Node node)
{
	return node.children.size();
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
		std::cout << edges[i]._from << " -> " << edges[i]._to << std::endl;
	}
	std::cout << std::endl;
}
