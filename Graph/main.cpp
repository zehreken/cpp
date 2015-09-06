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
	graph.addEdge(1, 3);
	graph.addEdge(3, 4);
	graph.addEdge(2, 5);
	graph.addEdge(1, 6);
	graph.addEdge(2, 7);
	graph.addEdge(6, 8);
	graph.addEdge(8, 9);
	graph.addEdge(8, 10);
	
	cout << "node count: " << graph.getNodeCount() << endl;
	cout << "edge count: " << graph.getEdgeCount() << endl;
	
	return 0;
}