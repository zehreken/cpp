#include <iostream>
#include "LinkedList.h"

Node *newHead = NULL;
Node* recursiveReverse(Node *head)
{
	if (head->next != NULL)
	{
		Node *temp = recursiveReverse(head->next);
		temp->next = head;
		head->next = NULL;
		return temp->next;
	}
	else
	{
		newHead = head;
	}
	
	return newHead;
}

Node* reverse(Node *head)
{
	Node *prev, *current, *next;
	prev = NULL;
	current = head;
	
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	
	return prev;
}

int main()
{
	Node *head = new Node();
	head->data = 0;
	Node *temp = head;
	for (int i = 1; i < 10; ++i)
	{
		Node *newNode = new Node();
		temp->next = newNode;
		newNode->data = i;
		temp = newNode;
	}
	
	LinkedList ll(0);
	ll.print();
	for (int i = 1; i < 30; ++i)
	{
		Node *newNode = new Node();
		newNode->data = i;
		ll.add(newNode);
	}
	ll.print();
	ll.pop();
	ll.print();
	for (int i = 0; i < 10; ++i) ll.pop();
	ll.print();
	
	return 0;
}
