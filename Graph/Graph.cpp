#include "Graph.h"

Graph::Graph(int _v)
{
	nodeCount = _v;
	
	for (int i = 0; i < nodeCount; i++)
	{
		Node node;
		node.id = i + 1;
		nodes.push_back(node);
	}
}

void Graph::addEdge(int _from, int _to)
{
	Edge edge;
	edge.from = _from;
	edge.to = _to;
	
	edges.push_back(edge);
}

int Graph::getNodeCount()
{
	return nodes.size();
}

int Graph::getEdgeCount()
{
	return edges.size();
}