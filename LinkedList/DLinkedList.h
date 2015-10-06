#pragma once
#include "LinkedList.h"

struct DNode : Node
{
	Node *prev = nullptr;
}

class DLinkedList : LinkedList
{
private:
	DNode *head;
	DNode *tail;
	int size;
public:
	DLinkedList(int headData);
	void push
}