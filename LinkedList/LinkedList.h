#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node
{
	Node *next = 0;
	int data = 0;
};

class LinkedList
{
private:
	Node *head;
	Node *tail;
public:
	LinkedList(int headData);
	void add(Node *node);
	void pop();
	void insert(Node *node, int index);
	void remove(Node *node, int index);
	int compare(Node *headA, Node *headB);
	Node* getHead();
	Node* getTail();
	void print();
	void printReverse();
};

#endif
