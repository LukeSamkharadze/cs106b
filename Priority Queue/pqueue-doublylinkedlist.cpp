#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() 
{
	head = new Node(NULL, NULL, "head");
	tail = new Node(head, NULL, "tail");

	head->next = tail;

	length = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() 
{
	for(Node* currentNode = head->next; currentNode != NULL; currentNode = currentNode->next)
		delete currentNode->prev;

	delete tail;
}

int DoublyLinkedListPriorityQueue::size() 
{
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() 
{
	return size() == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) 
{
	Node* newNode = new Node(head, head->next, value);
	
	head->next->prev = newNode;
	head->next = newNode;

	++length;
}

string DoublyLinkedListPriorityQueue::peek() 
{
	return GetMinNode()->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() 
{
	Node* minNode = GetMinNode();
	string minNodeValue = minNode->value;

	minNode->prev->next = minNode->next;
	minNode->next->prev = minNode->prev;

	--length;

	delete minNode;
	return minNodeValue;
}

DoublyLinkedListPriorityQueue::Node* DoublyLinkedListPriorityQueue::GetMinNode()
{
	if(isEmpty())
		error("Priority Queue is empty");

	Node* minNode = head->next;

	for(Node* currentNode = minNode->next; currentNode != tail; currentNode = currentNode->next)
		if(minNode->value > currentNode->value)
			minNode = currentNode;

	return minNode;
}