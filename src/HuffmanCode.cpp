#ifndef _HUFFMAN_CODE_CPP_
#define _HUFFMAN_CODE_CPP_

#include "HuffmanCode.h"

#include "hr_time.h"

// convert byte to character
#define byte2Char(val) ((unsigned char) ((val) % 256))

// convert character to ASCII
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

Node::Node()
{
	left = NULL;
	right = NULL;
	weight = 0;
}

ChaNode::ChaNode(char k)
{
	left = NULL;
	right = NULL;
	symbol = k;
	weight = 1;
}

ChaNode::ChaNode(){
	left = NULL;
	right = NULL;
	symbol = '\0';
	weight = 0;
}

LNode::LNode()
{
	node = NULL;
	next = NULL;
}

LNode::LNode(Node *newnode)
{
	this->node = newnode;
	next = NULL;
}



Queue::Queue()
{
	front = NULL;
	rear = NULL;
	count = 0;
}

bool Queue::isEmpty()
{
	if(count == 0)
	{
		return 1;
	}
	else
		return 0;
}

void Queue::enQueue(LNode *newnode)
{
	if(isEmpty())
	{
		front = rear = newnode;
	}
	else {
		LNode *cur = front,*pre = front;
		while(cur != NULL){
			if(newnode->node->weight <= cur->node->weight){
				if (cur == front) {
					front = newnode;
					newnode->next = cur;
					++count;
					return;
				}
				pre->next = newnode;
				newnode->next = cur;
				++count;
				return;
			}
			pre = cur;
			cur = cur->next;
		}
		pre->next = newnode;
		rear = newnode;
	}

	++count;

}

LNode* Queue::deQueue()
{
	if( !isEmpty() && count != 1)
	{
		LNode* tmp = front;
		front = front->next;
		tmp->next = NULL;
		--count;
		return tmp;
	}
	else if (count == 1)
	{
		LNode* tmp = front;
		front = rear = NULL;
		--count;
		tmp->next = NULL;
		return tmp;
	}
	else

		return NULL;
}

LNode* Queue::frontQueue()
{
	return front;
}

void Queue::freq(char k)
{
	LNode* tmp = front;
	while(tmp!=NULL)
	{
		if (((ChaNode*)tmp->node)->symbol == k)
		{
			tmp->node->weight++;
			return;
		}
		tmp = tmp->next;
	}
	tmp = new LNode(new ChaNode(k));
	enQueue(tmp);
}

int Queue::getCount() const {
	return count;
}


LNode *swap(LNode* L1, LNode* L2){
	L1->next = L2->next;
	L2->next = L1;
	return L2;
}

void Queue::sort()
{
	LNode *cur,*pre = front;
	bool change = 1;
	while(change){
		change = 0;
		for(cur = front,pre = front; cur->next != NULL;pre = cur, cur = cur->next){
			if (cur->next != NULL && cur->node->weight > cur->next->node->weight){

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

void Queue::display(){
	LNode* p= front;
	while(p != NULL){
		cout<<"Ky tu: "<<((ChaNode*)p->node)->symbol  << ":" <<"Tan so: "<<p->node->weight <<endl;
		p=p->next;
	}
}


Node* Queue::creatHuffmanTree(){

	LNode* child1;
	LNode* child2;
	while(getCount() > 1){
		child1 = deQueue();
		child2 = deQueue();
		LNode* root = new LNode;
		root->node = new Node;
		root->node->left = child1->node; // node nho dat ben trai
		root->node->right= child2->node; // node lon dat ben phai
		root->node->weight = child1->node->weight + child2->node->weight;
		enQueue(root);
	}
	return deQueue()->node;
}

void convertHuffmanToMap(char**& codemap,Node* root, char*& code,int& bodysize,int& sumofcharacter, int& totalbit){
	static int level = -1;
	//static char *code = new char[8];
	if(root->left == NULL && root->right == NULL){
		strcpy(codemap[((ChaNode*)root)->symbol],code);

		totalbit += strlen(code);
		bodysize += strlen(code)*root->weight;
		sumofcharacter += root->weight;

	}
	else{
		++level;
		code[level] = '0';
		convertHuffmanToMap(codemap,root->left, code,bodysize,sumofcharacter,totalbit);
		code[level] = '1';
		convertHuffmanToMap(codemap,root->right, code,bodysize,sumofcharacter,totalbit);
		code[level] = '\0';
		--level;
	}

}

void convertMaptoHuffman(Node*& root, char** codemap,char cha, int totalChar){
	static int level = -1;
	if(totalChar == 1 || codemap[char2Int(cha)][level+1] == '\0'  ){
		((ChaNode*)root)->symbol = cha;
		return;
	}
	else{

		++level;
		if(codemap[char2Int(cha)][level] == '0'){
			if(root->left == NULL){
				root->left = new ChaNode;
			}
			convertMaptoHuffman(root->left , codemap , cha,totalChar);
		}
		else{
			if(root->right == NULL){
				root->right = new ChaNode;
			}
			convertMaptoHuffman(root->right, codemap , cha,totalChar);
		}
		--level;
	}
}

void deCode(Reader* reader, Writer* writer,Node* root, int& bodysize){

	if( root->right == NULL && root->left == NULL){
		writer->writeByte(((ChaNode*)root)->symbol);
	}
	else{
		--bodysize;
		if(reader->readBit()){
			deCode(reader, writer, root->right,bodysize);
		}
		else{
			deCode(reader, writer, root->left,bodysize);
		}
	}
}

////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//////////////////////MAIN CODE////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


void display(Node* root){
	static int a = 0;
	static int flag = 0;
	++flag;
	if(root->left == NULL && root->right == NULL){
		cout<<((ChaNode*)root)->symbol<<" : "<<root->weight<<endl;
		++a;
	}
	else
	{
		display(root->left);
		display(root->right);
	}
	--flag;
	if(flag == 0){
		cout<<"\n sumofelement: "<<a<<endl;
	}
}

int HuffmanCode::zip(char* inputFile, char* outputFile) {

	CStopWatch time;
	time.startTimer();

	cout<<"Zipping.."<<endl;

	// Declare variable
	Reader *reader = new Reader(inputFile);		// Readfile object
	Writer *writer = new Writer(outputFile);	// Writefile object
	HCZHeader header;							// Header object


	Queue priQueue;							// Creat a Queue
	Node* huffmantree = NULL;				// root of Huffman tree

	char **codemap;// Map of chareacter code
	char *code;						// temp of code

	int bodysize = 0;				// Sum of bit in body
	int totalcharater = 0;			// Sum of character in text
	int usedcharacter = 0;			// Number of character used in txt
	int totalbit = 0;				// Total bit of coding map

	// Initialize the table of character code
	codemap = new char*[256];
	for(int i = 0; i < 256; i++){
    	codemap[i] = new char[16];
    	memset(codemap[i],'\0',strlen(codemap[i]));
    }

	// Initialize the temp variable to save encode
    code = new char[16];
    memset(code,'\0',strlen(code));
    code[0]='0';

	//	Count character and add to the Queue
	while(reader->isHasNext()){
		priQueue.freq(reader->readChar());
	}
	delete reader;

    // Get number of used character
    usedcharacter = priQueue.getCount();

    // Sort the Queue
	priQueue.sort();

	// Get the huffman tree
	huffmantree = priQueue.creatHuffmanTree();

	// Conver huffman tree to code map and get nessessary information
    convertHuffmanToMap(codemap,huffmantree,code,bodysize,totalcharater,totalbit);

    // Set important info to Header
    header.setBodySize(bodysize);
    header.setTotal(usedcharacter,totalbit);

    // Set codelist to header
    for(int i = 0 ; i < 256 ; i++){
    	if(codemap[i][0] != '\0'){
    		header.set(i,strlen(codemap[i]),codemap[i]);
    	}
    }

    // Writer header to file
    header.write(writer);

    // Encode file
    reader = new Reader(inputFile);
    char k;
    int limit;
    while(reader->isHasNext()){

    	k = reader->readChar();
    	limit = strlen(codemap[char2Int(k)]);

    	for(char j = 0 ; j < limit ; j++){
    		writer->writeBit(codemap[char2Int(k)][char2Int(j)] - '0');
    	}
    }

    delete reader;
    delete writer;
    cout<< "Total character encoded: "<<totalcharater<<endl;
    cout<<"Done!..."<<endl;
    time.stopTimer();
    cout<<"Excution time: "<<time.getElapsedTime()<<"s"<<endl;
    return SUCCESS;
}

int HuffmanCode::unzip(char* inputFile, char* outputFile) {
	CStopWatch time;
	time.startTimer();


    cout << "unzipping..."<<endl;

    // Declare variable
    Writer *writer = new Writer(outputFile);	// Writer ref object
    Reader *reader = new Reader(inputFile);		// Reader ref object
    HCZHeader *header = new HCZHeader;

	char **codemap;								// Map of chareacter code
	Node* huffmantree = new Node;				// huffmantree
	int totalChar;
	int totalBit;
	header->getTotal(totalChar, totalBit);

	// Check if file is right format
	if( header->read(reader) != -2){


		// Initialize the table of character code
		codemap = new char*[256];
		for(int i = 0; i < 256; i++){
			codemap[i] = new char[16];
			memset(codemap[i],'\0',16);
		}

		for(int i = 0, nbit; i < 256; i++){
			header->get((char)i,nbit,codemap[char2Int(i)]);
		}
		for(int i = 0; i< 256; i++){
			if(codemap[i][0] != '\0'){
				convertMaptoHuffman(huffmantree, codemap, (char)i, totalChar);
			}
		}

		int bodysize = header->getBodySize();
		while(bodysize){
			deCode(reader, writer, huffmantree, bodysize);
		}






	}
	delete reader;
	delete writer;
	delete header;

	cout<<"done!"<<endl;
    time.stopTimer();
    cout<<"Excution time: "<<time.getElapsedTime()<<"s"<<endl;
    return UN_IMPLEMENT;
}


#endif
