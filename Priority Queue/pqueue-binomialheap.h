#ifndef PQueue_BinomialHeap_Included
#define PQueue_BinomialHeap_Included

#include <string>
#include "Vector.h"

using namespace std;

class BinomialHeapPriorityQueue 
{
public:
	BinomialHeapPriorityQueue();
	~BinomialHeapPriorityQueue();
	
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

	int capacity;
	int length;

	void Destructor(Node* node);
	void Enqueue(Node* node);
	void Grow();
	int FindMinID();
	Node* Merge(Node* firstNode, Node* secondNode);
};

#endif