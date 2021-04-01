#ifndef PQueue_FibonacciHeap_Included
#define PQueue_FibonacciHeap_Included

#include <string>

#include "Vector.h"

using namespace std;

class FibonacciHeapPriorityQueue 
{
public:
	FibonacciHeapPriorityQueue();
	~FibonacciHeapPriorityQueue();
	
	int size();
	bool isEmpty();
	
	void enqueue(string value);
	string peek();
	string dequeueMin();
private:
	struct Node
	{
		int degree;
		string value;

		Node* parent;
		Node* sibling;
		Node* child;

		Node()
		{
			degree = 0;

			parent = NULL;
			sibling = NULL;
			child = NULL;
		}

		Node(string value)
		{
			degree = 0;
			this->value = value;

			parent = NULL;
			sibling = NULL;
			child = NULL;
		}
	};

	Node** nodes;

	int length;
	int capacity;

	int minNodeID;

	void Destructor(Node* node);
	void Enqueue(Node* node);
	void Refactor();
	void Grow();
	void UpdateMinNodeID();
	Node* Merge(Node* firstNode, Node* secondNode);
};

#endif