#include <iostream>
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList(int headData)
{
	head = new Node();
	tail = head;
	head->next = nullptr;
	head->data = headData;
	size = 1;
}

void LinkedList::add(Node *node)
{
	tail->next = node;
	tail = node;
	size += 1;
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
	if (toPop != nullptr)
	{
		toPop->next = nullptr;
		tail = toPop;
		size -= 1;
	}
}

void LinkedList::insert(Node *node, int index)
{
	if (index < 0 || index >= size)
	{
		cout << "EXCEPTION: illegal index value" << endl;
	}
	// else if (index == size)
	else if (index == 0)
	{
		node->next = head;
		head = node;
		size += 1;
	}
	else
	{
		Node *temp = head;
		Node *next = nullptr;
		int n = 0;
		while (temp != nullptr && n < index - 1)
		{
			temp = temp->next;
			n += 1;
		}
		next = temp->next;
		temp->next = node;
		node->next = next;
		size += 1;
	}
}

void LinkedList::remove(int index)
{
	if (index < 0 || index >= size)
	{
		cout << "EXCEPTION: illegal index value" << endl;
	}
	// else if (index == size)
	else if (index == 0)
	{
		head = head->next;
		size -= 1;
	}
	else
	{
		Node *temp = head;
		int n = 0;
		while (temp != nullptr && n < index - 1)
		{
			temp = temp->next;
			n += 1;
		}
		temp->next = temp->next->next;
		size -= 1;
	}
}

Node* LinkedList::reverse()
{
	Node *prev, *current, *next;
	prev = nullptr;
	current = head;
	tail = head;
	
	while (current != nullptr)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	
	head = prev;
	return head;
}

int LinkedList::compare(Node *headA, Node *headB)
{
	int isEqual = 1;
	
	return isEqual;
}

Node* LinkedList::getHead()
{
	return head;
}

Node* LinkedList::getTail()
{
	return tail;
}

int LinkedList::getSize()
{
	return size;
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
