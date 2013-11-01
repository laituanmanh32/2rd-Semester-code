#ifndef _HUFFMAN_CODE_H_
#define _HUFFMAN_CODE_H_

#include <iostream>
#include <fstream>
#include <cstring>

#include "Reader.h"
#include "Writer.h"
#include "HCZHeader.h"

using namespace std;

#define ERR -1

#define SUCCESS 0
#define UN_IMPLEMENT -2
#define MAXBUFSIZE 10000

// convert byte to character
#define byte2Char(val) ((unsigned char) ((val) % 256))

// convert character to ASCII
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

class HuffmanCode {
public:
    int zip(char* inputFile, char* outputFile);
    int unzip(char* inputFile, char* outputFile);
    HuffmanCode() {
    }

private:

};

// Standard node
class Node
{
public:
	int weight;
	Node *left;
	Node *right;

	Node();
};

// Charater node
class ChaNode : public Node
{
public:
	char symbol;
	ChaNode(char k);
	ChaNode();
};

// A liked list node
class LNode
{
public:
	Node *node;
	LNode *next;

	LNode();
	LNode(Node* newnode);
};


//  Priority queue
// Minimum value of weight will have higher priority (near front)
class Queue
{
private:
	LNode *rear;
	LNode *front;
	int count;     		// count of element in queue
public:
	Queue();


	// Check if queue is Null
	bool isEmpty();

	// Enqueue
	void enQueue(LNode *newnode);

	// Dequeue
	LNode* deQueue();

	// Return the front node
	LNode* frontQueue();

	// Incress frequence of a charater
	void freq(char k);

	// Sort the Queue
	void sort();
	int getCount() const ;
	void display();
	// creat Hufman tree
	Node* creatHuffmanTree();
};


// Convert Huffman code tree to code map
void convertHuffmanToMap(char**& codemap,Node* root, char*& code,int& bodysize,int& sumofcharacter, int& totalbit);

// Convert Code map to huffman code tree
void convertMaptoHuffman(Node*& root, char** codemap,char cha,int totalChar);

// Decode zip code
void deCode(Reader* reader, Writer* writer, Node* root,int& bodySize);


#endif
