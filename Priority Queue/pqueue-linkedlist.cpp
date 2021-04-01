#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() 
{
	head = new Node(NULL, "\0");
	length = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() 
{ 
	while(isEmpty() == false)
		dequeueMin();

	delete head;
}

int LinkedListPriorityQueue::size() 
{
	return length;
}

bool LinkedListPriorityQueue::isEmpty() 
{
	return size() == 0;
}

void LinkedListPriorityQueue::enqueue(string value)
{
	Node* prevNode = SearchPrevNode(value);
	Node* newNode = new Node(prevNode->next, value);
	prevNode->next = newNode;

	++length;
}

string LinkedListPriorityQueue::peek()
{
	if(isEmpty())
		error("Priority queue is empty");

	return head->next->value;
}

string LinkedListPriorityQueue::dequeueMin()
{
	string value = peek();

	Node* oldNode = head->next;
	head->next = oldNode->next;	

	--length;

	delete oldNode;
	return value;
}

LinkedListPriorityQueue::Node* LinkedListPriorityQueue::SearchPrevNode(string value)
{
	Node* currentNode = head;

	while(currentNode->next != NULL && value > currentNode->next->value)
		currentNode = currentNode->next;

	return currentNode;
}