#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() { }

VectorPriorityQueue::~VectorPriorityQueue() { }

int VectorPriorityQueue::size() 
{
	return elements.size();
}

bool VectorPriorityQueue::isEmpty() 
{
	return size() == 0;
}

void VectorPriorityQueue::enqueue(string value)
{
	elements.add(value);
}

string VectorPriorityQueue::peek()
{
	return elements[GetMinIndex()];
}

string VectorPriorityQueue::dequeueMin()
{
	int minIndex = GetMinIndex();
	
	string tmp = elements[minIndex];

	elements.remove(minIndex);

	return tmp;
}

int VectorPriorityQueue::GetMinIndex()
{
	if(isEmpty())
		error("Queue is empty");

	int minIndex = 0;

	for(int elementID = 1; elementID < size(); elementID++)
		if(elements[elementID] < elements[minIndex])
			minIndex = elementID;

	return minIndex;
}