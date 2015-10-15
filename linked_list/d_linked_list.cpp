#include <iostream>
#include <set>
#include "DLinkedList.h"

using namespace std;

DLinkedList::DLinkedList(int headData)
{
	head = new DNode();
	head->prev = nullptr;
	head->next = nullptr;
	head->data = headData;
	tail = head;
	size = 1;
}

void DLinkedList::push(DNode *node)
{
	node->prev = tail;
	node->next = nullptr;
	tail = node;
	size += 1;
}