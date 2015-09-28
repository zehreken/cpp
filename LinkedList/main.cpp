#include <iostream>
#include "LinkedList.h"

/*
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
//*/

int main()
{
	using namespace std;
	
	LinkedList ll(0);
	for (int i = 1; i < 10; ++i)
	{
		Node *n = new Node();
		n->data = i;
		ll.push(n);
	}
	
	LinkedList cc(0);
	for (int i = 2; i < 20; i += 2)
	{
		Node *n = new Node();
		n->data = i;
		cc.push(n);
	}
	
	ll.print();
	cc.print();
	
	Node *mergedHead = LinkedList::mergeSorted(ll.getHead(), cc.getHead());
	Node *itr = mergedHead;
	while (itr != nullptr)
	{
		cout << itr->data << ", ";
		itr = itr->next;
	}
	cout << endl;
	
	Node *temp = LinkedList::removeDuplicates(mergedHead);
	itr = temp;
	while (itr != nullptr)
	{
		cout << itr->data << ", ";
		itr = itr->next;
	}
	cout << endl;
	
	return 0;
}
