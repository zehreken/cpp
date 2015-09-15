#include <iostream>

using namespace std;

struct Node
{
	Node *next;
	int data;
};

void printLinkedList(Node *head)
{
	Node *temp = head;
	while (temp != NULL)
	{
		cout << temp->data << ", ";
		temp = temp->next;
	}
	cout << endl;
}

int main()
{
	Node *head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	Node *temp = head;
	for (int i = 1; i < 10; ++i)
	{
		Node *newNode = (Node*)malloc(sizeof(Node));
		temp->next = newNode;
		newNode->data = i;
		temp = newNode;
	}
	
	printLinkedList(head);
	
	return 0;
}
