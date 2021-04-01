#ifndef HuffmanTypes_Included
#define HuffmanTypes_Included

#include <stddef.h>

typedef int ext_char;

const ext_char PSEUDO_EOF = 256;
const ext_char NOT_A_CHAR = 257;

struct Node 
{
	ext_char character;

	Node *zero;
	Node *one;
	
	int weight;

	Node() 
	{ 
		zero = NULL;
		one = NULL;
	}

	Node(ext_char character, int weight, Node* zero, Node* one)
	{
		this->character = character;
		this->weight = weight;
		this->zero = zero;
		this->one = one;
	}

	void* operator new (size_t bytesNeeded);
	void  operator delete(void* toDelete);
};

#endif