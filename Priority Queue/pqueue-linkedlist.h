#ifndef PQueue_LinkedList_Included
#define PQueue_LinkedList_Included

#include <string>

using namespace std;

class LinkedListPriorityQueue 
{
public:
	LinkedListPriorityQueue();
	~LinkedListPriorityQueue();
	
	int size();
	bool isEmpty();
	
	void enqueue(string value);
	string peek();
	string dequeueMin();
	
private:
	struct Node
	{
		Node* next;
		string value;

		Node() { }

		Node(Node* next, string value)
		{
			this->next = next;
			this->value = value;
		}
	};

	Node* SearchPrevNode(string value);

	Node* head;
	int length;
};

#endif
