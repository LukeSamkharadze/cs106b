#include "pqueue-binomialheap.h"
#include "error.h"

#include <math.h>

BinomialHeapPriorityQueue::BinomialHeapPriorityQueue() 
{
	capacity = 1;
	length = 0;
	nodes = new Node*[capacity];
}

BinomialHeapPriorityQueue::~BinomialHeapPriorityQueue() 
{
	for(int i = 0; i < length; i++)
		Destructor(nodes[i]);
}

int BinomialHeapPriorityQueue::size() 
{
	int counter = 0;

	for(int i = 0; i < length; i++)
		if(nodes[i] != NULL)
			counter += pow(2.,i);

	return counter;
}

bool BinomialHeapPriorityQueue::isEmpty() 
{
	return size() == 0;
}

void BinomialHeapPriorityQueue::enqueue(string value) 
{
	if(length == capacity)
		Grow();

	Enqueue(new Node(value));
}

string BinomialHeapPriorityQueue::peek() 
{
	return nodes[FindMinID()]->value;
}

string BinomialHeapPriorityQueue::dequeueMin() 
{
	int minID = FindMinID();
	Node* minNode = nodes[minID];
	string minValue = minNode->value;

	Node* children = minNode->child; 

	delete nodes[minID];
	nodes[minID] = NULL;

	while(children != NULL)
	{
		Node* sibling = children->sibling;
		children->sibling = NULL;

		Enqueue(children);

		children = sibling;
	}

	return minValue;
}

void BinomialHeapPriorityQueue::Destructor(Node* node)
{
	while(node != NULL)
	{
		Destructor(node->child);
		node = node->sibling;
	}
}

void BinomialHeapPriorityQueue::Enqueue(Node* node)
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

	nodes[length++] = node;
}

void BinomialHeapPriorityQueue::Grow()
{
	capacity *= 2;

	Node** newNodes = new Node*[capacity];

	for (int nodeID = 0; nodeID < length; nodeID++)
		newNodes[nodeID] = nodes[nodeID];

	nodes = newNodes;
}

int BinomialHeapPriorityQueue::FindMinID()
{
	int minID = -1;
	for(int i = 0; i < length; i++)
		if(nodes[i] != NULL)
		{
			if(minID == -1)
				minID = i;
			else if(nodes[minID]->value > nodes[i]->value)
				minID = i;
		}

	if(minID == -1)
		error("Priority Queue is Empty");

	return minID;
}

BinomialHeapPriorityQueue::Node* BinomialHeapPriorityQueue::Merge(Node* firstNode, Node* secondNode)
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