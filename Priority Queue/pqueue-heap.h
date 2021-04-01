#ifndef PQueue_Heap_Included
#define PQueue_Heap_Included

#include <string>

using namespace std;

class HeapPriorityQueue
{
public:
	HeapPriorityQueue();
	~HeapPriorityQueue();
	
	int size();
	bool isEmpty();

	void enqueue(string value);
	string peek();
	string dequeueMin();

//private:
	void Grow();
	void BubbleDown();
	void BubbleUp(int index);
	void Swap(int index1, int index2);
	

	string* elements;

	int capacity;
	int length;
};

#endif