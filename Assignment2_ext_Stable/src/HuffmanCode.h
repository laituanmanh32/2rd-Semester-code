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
	long long int weight;
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
	//________________________________________________
	// Cac Node duoc add vao theo do uu tien
	// Node co trong so cao se nam gan rear hon
	//
	void enQueue(LNode *newnode);

	// Dequeue
	//_______________________________________________
	// Tra ve Node o dau danh sach
	// dong thoi xoa node do khoi danh sach
	LNode* deQueue();

	// Return the front node
	//_______________________________________________
	// Tra ve Node o dau danh sach
	LNode* frontQueue();

	// Incress frequence of a charater
	//_______________________________________________
	// Tang tan so ki tu k len 1
	void freq(char k);

	// Sort the Queue
	// _______________________________________________
	// Sap xep danh sach theo chieu tang dan weight
	//void sort();

	int getCount() const ;
	void display();
	// creat Hufman tree
	// _______________________________________________
	// Tao cay Huffman
	Node* creatHuffmanTree();
};


// Convert Huffman code tree to code map
// __________________________________________________________
// Chuyen bo ma trong cay huffman vao bang code codemap
// Tra ve bodysize bang tong so bit duoc sinh ra
// Tra ve sumofcharacter bang tong so ki tu duoc su dung
// Tra ve totalBit bang tong so bit duoc su dung de ma hoa
void convertHuffmanToMap(char**& codemap,Node* root, char*& code,int& bodysize,int& sumofcharacter, int& totalbit);

// Convert Code map to huffman code tree
//___________________________________________________________
//
void convertMaptoHuffman(Node*& root, char** codemap,char cha,int totalChar);

// Decode zip code
//____________________________________________________________
//
void deCode(Reader* reader, Writer* writer, Node* root,int& bodySize,int totalChar);


#endif
