#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Graph.h"
using namespace std;

/*10 9
2 1
3 1
4 3
5 2
6 1
7 2
8 6
9 8
10 8*/

int main()
{
	Graph graph(10);
	graph.addEdge(1, 2);
	graph.printAdjacencyMatrix();
	graph.addEdge(1, 3);
	graph.printAdjacencyMatrix();
	graph.addEdge(3, 4);
	graph.printAdjacencyMatrix();
	graph.addEdge(2, 5);
	graph.printAdjacencyMatrix();
	graph.addEdge(1, 6);
	graph.printAdjacencyMatrix();
	graph.addEdge(2, 7);
	graph.printAdjacencyMatrix();
	graph.addEdge(6, 8);
	graph.printAdjacencyMatrix();
	graph.addEdge(8, 9);
	graph.printAdjacencyMatrix();
	graph.addEdge(8, 10);
	graph.printAdjacencyMatrix();

	graph.printEdges();

	cout << "node count: " << graph.getNodeCount() << endl;
	cout << "edge count: " << graph.getEdgeCount() << endl;

	int a;
	cin >> a;

	return 0;
}
