#include <iostream>
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList(int headData)
{
	head = new Node();
	tail = head;
	head->next = nullptr;
	head->data = headData;
}

void LinkedList::add(Node *node)
{
	tail->next = node;
	tail = node;
}

void LinkedList::pop()
{
	Node *temp = head;
	Node *toPop = nullptr;
	while (temp->next != nullptr)
	{
		toPop = temp;
		temp = temp->next;
	}
	if (toPop != nullptr) toPop->next = nullptr;
}

void LinkedList::insert(Node *node, int index)
{
	Node *temp = head;
}

void LinkedList::remove(Node *node, int index)
{
	
}

int LinkedList::compare(Node *headA, Node *headB)
{
	
}

Node* LinkedList::getHead()
{
	return head;
}

Node* LinkedList::getTail()
{
	return tail;
}

void LinkedList::print()
{
	Node *temp = head;
	while (temp != nullptr)
	{
		cout << temp->data;
		temp = temp->next;
		if (temp != nullptr) cout << ", ";
	}
	cout << endl;
}

void LinkedList::printReverse()
{
	
}
