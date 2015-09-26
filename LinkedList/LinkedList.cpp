#include <iostream>
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList(int headData)
{
	head = new Node();
	head->next = nullptr;
	head->data = headData;
	tail = head;
	size = 1;
}

void LinkedList::push(Node *node)
{
	tail->next = node;
	tail = node;
	size += 1;
}

Node* LinkedList::pop()
{
	Node *itr = head;
	Node *temp = nullptr;
	while (itr->next != nullptr)
	{
		temp = itr;
		itr = itr->next;
	}
	tail = temp;
	size -= 1;
	
	return temp->next;
}

void LinkedList::insert(Node *node, int index)
{
	if (index < 0 || index >= size)
	{
		cout << "EXCEPTION: illegal index value" << endl;
	}
	else if (index == 0)
	{
		node->next = head;
		head = node;
		size += 1;
	}
	else
	{
		Node *itr = head;
		Node *next = nullptr;
		int n = 0;
		while (itr != nullptr && n < index - 1)
		{
			itr = itr->next;
			n += 1;
		}
		next = itr->next;
		itr->next = node;
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
	else if (index == 0)
	{
		delete head;
		head = head->next;
		size -= 1;
	}
	else
	{
		Node *itr = head;
		int n = 0;
		while (itr != nullptr && n < index - 1)
		{
			itr = itr->next;
			n += 1;
		}
		itr->next = itr->next->next;
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
	Node *itrA, *itrB;
	itrA = headA;
	itrB = headB;
	while (itrA != nullptr)
	{
		if (itrB == nullptr || itrA->data != itrB->data)
		{
			isEqual = 0;
			break;
		}
		itrA = itrA->next;
		itrB = itrB->next;
	}
	if (itrB != nullptr) isEqual = 0;
	
	return isEqual;
}

Node* LinkedList::mergeSorted(Node *headA, Node *headB)
{
	Node *sortedHead = nullptr;
	
	return sortedHead;
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
	Node *itr = head;
	for (int i = 0; i < size; ++i)
	{
		cout << itr->data;
		itr = itr->next;
		if (i < size - 1) cout << ", ";
	}
	cout << endl;
}

void LinkedList::printReverse()
{
	
}
