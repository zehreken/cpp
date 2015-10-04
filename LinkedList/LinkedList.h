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
	int size;
public:
	LinkedList(int headData);
	void push(Node *node);
	Node* pop();
	void insert(Node *node, int index);
	void remove(int index);
	Node* reverse();
	static int compare(Node *headA, Node *headB);
	static Node* mergeSorted(Node *headA, Node *headB);
	static Node* removeDuplicates(Node *head);
	static int hasCycle(Node* head);
	static Node* findMergeNode(Node *headA, Node *headB);
	Node* getHead();
	Node* getTail();
	int getSize();
	void print();
	void printReverse();
};

#endif
