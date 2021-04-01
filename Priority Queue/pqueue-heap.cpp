#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() 
{
	elements = new string[1];
	capacity = 1;
	length = 0;
}

HeapPriorityQueue::~HeapPriorityQueue()
{
	delete[] elements;
}

int HeapPriorityQueue::size()
{
	return length;
}

bool HeapPriorityQueue::isEmpty()
{
	return size() == 0;
}

void HeapPriorityQueue::enqueue(string value)
{
	if (length == capacity) 
		Grow();

	elements[length] = value;

	++length;

	BubbleUp(length-1);
}

string HeapPriorityQueue::peek()
{
	if(isEmpty())
		error("Priority Queue is empty");

	return elements[0];
}

string HeapPriorityQueue::dequeueMin()
{
	string value = peek();
	elements[0] = elements[size()-1];
	
	--length;

	BubbleDown();

	return value;
}

void HeapPriorityQueue::Grow()
{
	capacity *= 2;

	string* newElements = new string[capacity];

	for (int elementID = 0; elementID < length; elementID++)
		newElements[elementID] = elements[elementID];

	delete[] elements;
	elements = newElements;
}

void HeapPriorityQueue::BubbleDown()
{
	int index = 1;

	while(true)
	{
		int minIndex;

		if(index*2 < length)
		{
			minIndex = (elements[index*2-1] < elements[index*2]) ? index*2-1 : index*2;

			if(elements[minIndex] > elements[index-1])
				return;
		}
		else if(index*2-1 < length)
		{
			minIndex = index*2-1;

			if(elements[minIndex] > elements[index-1])
				return;
		}
		else
			return;

		Swap(minIndex, index-1);
		index = minIndex+1;
	}
}

void HeapPriorityQueue::BubbleUp(int index)
{
	++index;
	while(index != 1 && elements[index/2-1] > elements[index-1])
	{
		Swap(index-1, index/2-1);
		index = index/2;
	}
}

void HeapPriorityQueue::Swap(int index1, int index2)
{
	string tmp = elements[index1];
	elements[index1] = elements[index2];
	elements[index2] = tmp;
}