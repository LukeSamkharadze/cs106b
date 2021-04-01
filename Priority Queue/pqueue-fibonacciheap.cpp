#include "pqueue-fibonacciheap.h"
#include "error.h"

#include <math.h>

FibonacciHeapPriorityQueue::FibonacciHeapPriorityQueue() 
{
	capacity = 1;
	length = 0;

	nodes = new Node*[capacity];

	minNodeID = -1;
}

FibonacciHeapPriorityQueue::~FibonacciHeapPriorityQueue() 
{
	for(int i = 0; i < length; i++)
		Destructor(nodes[i]);
}

int FibonacciHeapPriorityQueue::size() 
{
	int counter = 0;

	for(int i = 0; i < length; i++)
		if(nodes[i] != NULL)
			counter += pow(2.,nodes[i]->degree);

	return counter;
}

bool FibonacciHeapPriorityQueue::isEmpty() 
{
	return size() == 0;
}

void FibonacciHeapPriorityQueue::enqueue(string value) 
{
	Node* newNode = new Node(value);
	
	if(isEmpty())
		minNodeID = length;
	else if(value < nodes[minNodeID]->value)
		minNodeID = length;

	if(length == capacity)
		Grow();
	nodes[length++] = newNode;
}

string FibonacciHeapPriorityQueue::peek() 
{
	if(minNodeID == -1)
		error("Priority Queue is Empty");

	return nodes[minNodeID]->value;
}

string FibonacciHeapPriorityQueue::dequeueMin() 
{
	if(minNodeID == -1)
		error("Priority Queue is Empty");

	string minValue = nodes[minNodeID]->value;

	Node* children = nodes[minNodeID]->child;

	delete nodes[minNodeID];
	nodes[minNodeID] = NULL;

	while(children != NULL)
	{
		Node* sibling = children->sibling;
		children->sibling = NULL;

		Enqueue(children);

		children = sibling;
	}

	Refactor();

	return minValue;
}

void FibonacciHeapPriorityQueue::Destructor(Node* node)
{
	while(node != NULL)
	{
		Destructor(node->child);
		node = node->sibling;
	}
}

void FibonacciHeapPriorityQueue::Enqueue(Node* node)
{
	for(int i = node->degree; i < length; i++)
	{
		if(i > node->degree)
		{
			nodes[i-1] = node;
			return;
		}
		else if(nodes[i] == NULL && i == node->degree)
		{
			nodes[i] = node;
			return;
		}
		else if(node->degree == nodes[i]->degree)
		{
			node = Merge(nodes[i], node);
			nodes[i] = NULL;
		}
	}

	if(length == capacity)
		Grow();
	nodes[length++] = node;
}

void FibonacciHeapPriorityQueue::Refactor()
{
	if(size() == 0)
	{
		minNodeID = -1;
		return;
	}

	int i = 1;
	for(; i < length; i++)
	{
		if(nodes[i] != NULL)
			if(nodes[i]->degree != i)
				break;
	}

	for(; i < length; i++)
	{
		Node* node = nodes[i];
		nodes[i] = NULL;
		if(node != NULL)
			Enqueue(node);
	}
	
	UpdateMinNodeID();
}

void FibonacciHeapPriorityQueue::Grow()
{
	capacity *= 2;

	Node** newNodes = new Node*[capacity];

	for (int nodeID = 0; nodeID < length; nodeID++)
		newNodes[nodeID] = nodes[nodeID];

	nodes = newNodes;
}

void FibonacciHeapPriorityQueue::UpdateMinNodeID()
{
	minNodeID = -1;
	for(int i = 0; i < length; i++)
		if(nodes[i] != NULL)
		{
			if(minNodeID == -1)
				minNodeID = i;
			else if(nodes[minNodeID]->value > nodes[i]->value)
				minNodeID = i;
		}

	if(minNodeID == -1)
		error("Priority Queue is Empty");
}

FibonacciHeapPriorityQueue::Node* FibonacciHeapPriorityQueue::Merge(Node* firstNode, Node* secondNode)
{
	if(firstNode->value < secondNode->value)
	{
		secondNode->parent = firstNode;
		secondNode->sibling = firstNode->child;
		firstNode->child = secondNode;
		firstNode->degree++;

		return firstNode;
	}
	else
	{
		firstNode->parent = secondNode;
		firstNode->sibling = secondNode->child;
		secondNode->child = firstNode;
		secondNode->degree++;

		return secondNode;
	}
}