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
	LinkedList ll(0);
	ll.print();
	for (int i = 1; i < 20; ++i)
	{
		Node *newNode = new Node();
		newNode->data = i;
		ll.add(newNode);
	}
	ll.print();
	std::cout << "size: " << ll.getSize() << std::endl;
	ll.pop();
	ll.print();
	std::cout << "size: " << ll.getSize() << std::endl;
	for (int i = 0; i < 10; ++i) ll.pop();
	ll.print();
	
	Node *t = new Node();
	t->data = 9999;
	ll.insert(t, ll.getSize() - 1);
	ll.print();
	std::cout << "size: " << ll.getSize() << std::endl;
	ll.remove(5);
	ll.print();
	std::cout << "size: " << ll.getSize() << std::endl;
	std::cout << "head data: " << ll.getHead()->data << std::endl;
	
	Node *reverse = ll.reverse();
	ll.print();
	std::cout << "tail data: " << ll.getTail()->data << std::endl;
	
	
	return 0;
}
