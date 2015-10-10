#pragma once

struct DNode
{
	DNode *prev = nullptr;
	DNode *next = nullptr;
	int data = 0;
};

class DLinkedList
{
private:
	DNode *head;
	DNode *tail;
	int size;
public:
	DLinkedList(int headData);
	void push(DNode *node);
	DNode* pop();
	void insert(DNode *node, int index);
	void remove(int index);
	DNode* reverse();
	static int compare(DNode *headA, DNode *headB);
	static DNode* mergeSorted(DNode* headA, DNode* headB);
	static DNode* removeDuplicates(DNode* head);
	static int hasCycle(DNode* head);
	static DNode* findMergeNode(DNode *headA, DNode *headB);
	DNode* getHead();
	DNode* getTail();
	int getSize();
	void print();
	void printReverse();
};