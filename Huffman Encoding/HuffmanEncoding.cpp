#include "HuffmanEncoding.h"
#include "pqueue.h"

void getMapOfEncodings(Node*& encodingTree, string encoding, Map<ext_char, string>& encodings)
{
	if(encodingTree == NULL)
		return;
	if(encodingTree->character != NOT_A_CHAR)
		encodings[encodingTree->character] = encoding;
	else
	{
		getMapOfEncodings(encodingTree->zero, encoding + "0", encodings);
		getMapOfEncodings(encodingTree->one, encoding + "1", encodings);
	}
}

Map<string, ext_char> getReversedMapOfEncodings(Map<ext_char, string>& encodings)
{
	Map<string, ext_char> reversedEncodings;

	foreach(ext_char character in encodings)
		reversedEncodings[encodings[character]] = character;

	return reversedEncodings;
}

//===============================================================================================//

void freeTree(Node* root) 
{
	if(root->zero != NULL)
		freeTree(root->zero);
	if(root->one != NULL)
		freeTree(root->one);

	delete root;
}

Map<ext_char, int> getFrequencyTable(istream& file) 
{
	Map<ext_char, int> frequencyTable;

	char character;
	while (file.get(character))
		frequencyTable[character]++;

	frequencyTable[PSEUDO_EOF] = 1;

	return frequencyTable;
}

Node* buildEncodingTree(Map<ext_char, int>& frequencies) 
{
	PriorityQueue<Node*> nodes;
	foreach(ext_char character in frequencies)
		nodes.enqueue(new Node(character, frequencies[character], NULL, NULL), frequencies[character]);

	while (nodes.size() != 1) 
	{
		Node* zero = nodes.dequeue();
        Node* one = NULL;

        if (nodes.isEmpty() == false)
            one = nodes.dequeue();
        
        nodes.enqueue(new Node(NOT_A_CHAR, zero->weight + one->weight, zero, one), zero->weight + one->weight);
    }

	return nodes.dequeue();
}

void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) 
{
	Map<ext_char, string> encodings;
	getMapOfEncodings(encodingTree, "", encodings);

	char character;
	while(infile.get(character))
		for (int i = 0; i < encodings[character].length(); i++)
			outfile.writeBit(encodings[character][i] - '0');

	for (int i = 0; i < encodings[PSEUDO_EOF].length(); i++)
			outfile.writeBit(encodings[PSEUDO_EOF][i] -'0');
}

void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) 
{
	Map<ext_char, string> encodings;
	getMapOfEncodings(encodingTree, "", encodings);
	Map<string, ext_char> reversedEncodings = getReversedMapOfEncodings(encodings);

	char bit;
	string currentBits;
	while(true)
	{
		bit = '0' + infile.readBit();
		currentBits += bit;

		if(reversedEncodings.containsKey(currentBits))
		{
			if(reversedEncodings[currentBits] == PSEUDO_EOF)
				return;

			file << (char)reversedEncodings[currentBits];
			currentBits = "";
		}
	}

}

void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) 
{
	if (!frequencies.containsKey(PSEUDO_EOF)) 
		error("No PSEUDO_EOF defined.");
	
	outfile << frequencies.size() - 1 << ' ';
	
	foreach (ext_char ch in frequencies) 
	{
		if (ch == PSEUDO_EOF) 
			continue;
		
		outfile << char(ch) << frequencies[ch] << ' ';
	}
}

Map<ext_char, int> readFileHeader(ibstream& infile) 
{
	Map<ext_char, int> result;
	
	int numValues;
	infile >> numValues;
	
	infile.get();
	
	for (int i = 0; i < numValues; i++) 
	{
		ext_char ch = infile.get();
		
		int frequency;
		infile >> frequency;
		
		infile.get();
		
		result[ch] = frequency;
	}
	
	result[PSEUDO_EOF] = 1;
	return result;
}

void compress(ibstream& infile, obstream& outfile) 
{
	Map<ext_char, int> frequencyTable = getFrequencyTable(infile);

    writeFileHeader(outfile, frequencyTable);
    Node* encodingTree = buildEncodingTree(frequencyTable);

	infile.rewind();
    encodeFile(infile, encodingTree, outfile);

    freeTree(encodingTree);
}

void decompress(ibstream& infile, ostream& outfile) 
{
    Node* encodingTree = buildEncodingTree(readFileHeader(infile));

    decodeFile(infile, encodingTree, outfile);

    freeTree(encodingTree);
}