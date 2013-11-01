#ifndef _HUFFMAN_CODE_CPP_
#define _HUFFMAN_CODE_CPP_

#include "HuffmanCode.h"

// convert byte to character
#define byte2Char(val) ((unsigned char) ((val) % 256))

// convert character to ASCII
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

#define MAXCHAR 256


struct Node{
	char symbol;
	int weight;
	Node* left;
	Node* right;
	Node* next;

	// Constructor
	Node(){symbol = '\0'; weight = 0 ; left = right = next = NULL; }
	Node(char k){
		symbol = k;
		weight = 1;
		left = right= next = NULL;
	}
};

// Struct to store code
struct Map{
	char** map;

	Map(){
		map = new char*[MAXCHAR];
		for(int i = 0 ; i < MAXCHAR ; i++){
			map[i] = new char[32];
			memset(map[i],'\0',32);
		}
	}
};

// struct to store code
struct Code{
	char* code;

	Code(){
		code = new char[32];
		memset(code,'\0',32);
	}
};

Node* swap(Node *L1,Node *L2){
	L1->next = L2->next;
	L2->next = L1;
	return L2;
}

// Queue to creat huffman tree
struct Queue{
	Node* front;
	Node* rear;
	int count;

	// Menthod
	Queue(){
		front = rear = NULL;
		count = 0;
	}

	void EnQueue(Node* newnode){
		if (count == 0) {
			front = rear = newnode;
		} else {
			rear->next = newnode;
			rear = rear->next;
		}
		++count;
	}

	void EnQueue(char k){
		Node* tmp = new Node(k);
		EnQueue(tmp);
	}

	Node* DeQueue(){
		Node* tmp;
		tmp = front;
		front = front->next;
		tmp->next = NULL;
		if(count == 1){
			front = rear = NULL;
		}
		--count;
		return tmp;
	}

	void freq(char k){
		Node* tmp = front;
		while(tmp != NULL){
			if(tmp->symbol == k){
				tmp->weight++;
				return;
			}
			tmp = tmp->next;
		}
		EnQueue(k);
	}

	void sort(){
		Node *cur,*pre = front;
		bool change = 1;
		while(change){
			change = 0;
			for(cur = front,pre = front; cur->next != NULL;pre = cur, cur = cur->next){
				if (cur->next != NULL && cur->weight > cur->next->weight){
					cur = swap(cur,cur->next);
					if(cur->next == front){
						front = cur;
						change = 1;
						break;
					}
					change = 1;
					pre->next = cur;
				}

			}
		}
		cur = front;
		while (cur->next != NULL){
			cur = cur->next;
		}
		rear = cur;
	}


};

void display(Node* root){
	Node* tmp = root;
	while(tmp  != NULL){
		cout<< tmp->symbol << " : "<< tmp->weight<<endl;
		tmp = tmp->next;
	}
}
void displaytree(Node* root){
	if(root->left == NULL && root->right == NULL){
		cout<<root->symbol<<":"<<root->weight<<endl;
	}
	else{
		displaytree(root->left);
		displaytree(root->right);
	}
}
void huffman2map(Node* root, char** map, char* temp, int& bodysize){
	static int a = -1;
	if(root->left == NULL && root->right == NULL){
		strcpy(map[char2Int(root->symbol)],temp);
		bodysize += root->weight*strlen(temp);
	}
	else{
		++a;
		temp[a] = '0';
		huffman2map(root->left,map,temp,bodysize);
		temp[a] = '1';
		huffman2map(root->right,map,temp,bodysize);
		temp[a] = '\0';
		--a;
	}

}

void code2huffman(char* code,char k,Node* root){
	static int a = -1;
	if(code[a+1] == '\0'){
		root->symbol = k;
		return;
	}
	else{
		++a;
		if(code[a] == '0'){
			if(root->left == NULL){
			root->left = new Node;
			}
			code2huffman(code,k,root->left);
		}
		else{
			if(root->right == NULL){
			root->right = new Node;
			}
			code2huffman(code,k,root->right);
		}
		--a;
	}
}

void countTotalBits(Map map, int& totalbit){
	for(int i = 0 ; i < MAXCHAR ; i++){
		if(map.map[i][0] != '\0'){
			totalbit += strlen(map.map[i]);
		}
	}
}



int HuffmanCode::zip(char* inputFile, char* outputFile) {

	Reader *reader = new Reader(inputFile);
	Writer *writer = new Writer(outputFile);
	HCZHeader header;

	Queue queue;
	Node* huffmantree = NULL;
	Map map;
	Code code;
	int totalbit = 0;
	int bodysize = 0;
	int totalchar = 0;


	while(reader->isHasNext()){
		queue.freq(reader->readChar());
	}

	totalchar = queue.count;
	queue.sort();


	while(queue.count > 1){
		Node *tmp1 = queue.DeQueue();
		Node *tmp2 = queue.DeQueue();
		Node *newnode = new Node;
		newnode->right = tmp1;
		newnode->left = tmp2;
		newnode->weight = tmp1->weight + tmp2->weight;
		queue.EnQueue(newnode);
		queue.sort();
	}
	huffmantree = queue.DeQueue();

	code.code[0]= '0';
	huffman2map(huffmantree,map.map,code.code,bodysize);

	countTotalBits(map,totalbit);

	header.setBodySize(bodysize);

	header.setTotal(totalchar,totalbit);
	for(int i = 0 ; i < MAXCHAR ; i++){
		if(map.map[i][0] != '\0'){
			header.set(char(i),strlen(map.map[i]),map.map[i]);
		}
	}


	header.write(writer);
	delete reader;
	reader = new Reader(inputFile);

	while(reader->isHasNext()){
		int k = reader->readByte();
		for(int i = 0 ; i < strlen(map.map[k]);i++){
			writer->writeBit(map.map[k][i] - '0');
		}
	}

	delete reader;
	delete writer;

    cout << "zipping...";
    return UN_IMPLEMENT;
}


void dich(Reader* reader,Writer *writer,Node* root, int& size){
	if(root->left == NULL && root->right == NULL){
		writer->writeByte(char2Int(root->symbol));
	}
	else{
		--size;
		if(reader->readBit()){
			dich(reader,writer,root->right,size);
		}
		else{
			dich(reader,writer,root->left,size);
		}
	}
}
int HuffmanCode::unzip(char* inputFile, char* outputFile) {

	Reader *reader = new Reader(inputFile);
	HCZHeader *header = new HCZHeader;
	Writer *writer = new Writer(outputFile);

	header->read(reader);

	Node* huffmantree = new Node;
	int bodysize = header->getBodySize();
	int totalchar;
	int totalbit;
	header->getTotal(totalchar,totalbit);
	Code code;
	char k;
	for(int i = 0, nbit ; i < MAXCHAR; i++  ){
		if(header->get(char(i),nbit,code.code) == 0){
			code2huffman(code.code,char(i),huffmantree);
		}
	}
	while(bodysize>0){
		dich(reader,writer,huffmantree,bodysize);
	}
	delete reader;
	delete header;
	delete writer;

    cout << "unzipping...";
    return UN_IMPLEMENT;
}


#endif
