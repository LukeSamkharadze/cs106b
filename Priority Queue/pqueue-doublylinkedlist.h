#ifndef PQueue_DoublyLinkedList_Included
#define PQueue_DoublyLinkedList_Included

#include <string>

using namespace std;

class DoublyLinkedListPriorityQueue 
{
public:
	DoublyLinkedListPriorityQueue();
	~DoublyLinkedListPriorityQueue();
	
	int size();
	bool isEmpty();
	
	void enqueue(string value);
	string peek();
	string dequeueMin();

private:
	struct Node
	{
		Node* prev;
		Node* next;
		string value;

		Node() { }

		Node(Node* prev, Node* next, string value)
		{
			this->prev = prev;
			this->next = next;
			this->value = value;
		}
	};

	Node* GetMinNode();

	Node* head;
	Node* tail;

	int length;
};

#endif