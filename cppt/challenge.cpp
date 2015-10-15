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
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
	public:
	int id, parent;
	vector<Node*> firstLevelChildren;
	
	int getChildCount()
	{
		int childCount = firstLevelChildren.size();
		for (int i = 0; i < firstLevelChildren.size(); ++i)
		{
			childCount += firstLevelChildren[i]->getChildCount();
			// cout << id << " child count: " << firstLevelChildren[i]->firstLevelChildren.size() << endl;
		}
		
		return childCount;
	}
};

int main()
{
	int vCount, eCount;
	scanf("%d %d", &vCount, &eCount);
	
	const int nodeCount = 10;
	Node nodes[nodeCount];
	for (int i = 0; i < nodeCount; ++i)
	{
		nodes[i].id = i + 1;
	}
	
	for (int i = 0; i < eCount; ++i)
	{
		int ui, vi;
		scanf("%d %d", &ui, &vi);
		
		nodes[ui - 1].parent = vi;
		nodes[vi - 1].firstLevelChildren.push_back(&nodes[ui - 1]);
	}
	
	printf("\n");
	
	for (int i = 0; i < vCount; ++i)
	{
		printf("id: %d parent: %d flc: %lu c: %d\n", nodes[i].id, nodes[i].parent, nodes[i].firstLevelChildren.size(), nodes[i].getChildCount());
	}
	
	return 0;
}