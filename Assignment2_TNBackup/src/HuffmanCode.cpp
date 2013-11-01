#ifndef _HUFFMAN_CODE_CPP_
#define _HUFFMAN_CODE_CPP_

#include "HuffmanCode.h"

// convert byte to character
#define byte2Char(val) ((unsigned char) ((val) % 256))

// convert character to ASCII
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

#define max 256

struct Node{
	char kitu;
	int tanso;
	char* mabit;
	int dodai;
	Node *next;
	Node *left;
	Node* right;

	Node(){
		dodai = 0;
		kitu = '\0';
		tanso = 0;
		mabit = new char[max];
		for(int i = 0 ; i < max ; i++){
			mabit[i] = '\0';
		}
		next = left = right = NULL;
	}
	Node(char newchar){
		dodai = 0;
		this->kitu = newchar;
		tanso = 1;
		mabit = new char[max];
		for(int i = 0 ; i < max ; i++){
			mabit[i] = '\0';
		}
		next = left = right = NULL;
	}

	Node(Node* left,Node* right)
	{
		dodai = 0;
		kitu = '\0';
		tanso = left->tanso + right->tanso;
		mabit = NULL;
		next = NULL;
		this->left = left;
		this->right = right;
	}

};


void dem(Node *&root, char k)
{
	if(root == NULL){
		root = new Node(k);
	}
	else{
		Node* cur = root,*pre=root;
		while(cur!=NULL){
			if(cur->kitu == k){
				cur->tanso++;
				return;
			}
			pre = cur;
			cur = cur->next;
		}
		cur = new Node(k);
		pre->next = cur;

	}
}

void xuat(Node* root){
	Node* tmp = root;
	while (tmp != NULL){
		cout<<tmp->kitu<<" : "<< tmp->tanso;
		if(tmp->mabit != '\0')
		{
			cout<<" : "<<tmp->mabit<<endl;
		}
		else
		{
			cout<<endl;
		}
		tmp = tmp->next;
	}
}

Node* layra(Node*& root)
{
	int min = root->tanso;
	Node* tmp = root;
	while(tmp != NULL)
	{
		if (min > tmp->tanso) min = tmp->tanso;
		tmp = tmp ->next;
	}
	Node* cur=root,*pre=root;
	while(cur != NULL)
	{
		if(cur->tanso == min)
		{
			if(cur == root)
			{
				root = root->next;
				cur->next = NULL;
				return cur;
			}
			else
			{
				pre->next = cur->next;
				cur->next = NULL;
				return cur;
			}

		}
		pre= cur;
		cur= cur->next;
	}
	return NULL;
}

void travao(Node*& root,Node* newnode)
{
	Node* cur = root;
	root = newnode;
	root->next = cur;
}

void chuyenthanhcay(Node*& root){
	Node* head = root;
	while(head->next != NULL){
		travao(root,new Node(layra(root),layra(root)));
		head = root;
	}
}

void mahoa(Writer* output,Node* boma, char k)
{
	Node* tmp = boma;
	while(tmp!=NULL)
	{
		if (tmp->kitu == k)
		{
			for(int i = 0; i< tmp->dodai;i++)
			{
				output->writeBit(tmp->mabit[i] - 48);
			}
			return;
		}
		tmp = tmp->next;
	}
}

Node* timnode(Node *root,char k)
{
	Node* tmp = root;
	while(tmp!=NULL)
	{
		if(tmp->kitu == k)
		{
			return tmp;
		}
	}
	return NULL;
}

void chuyencaythanhmabit(Node* root,Node*& bitcode,int& bodysize,char* code = new char[256],int level = 0){
	static bool flag = 1;
	if(flag){
		memset(code,'\0',256);
		flag = 0;
	}
	if(root->right ==NULL && root->left == NULL)
	{
		Node* tmp = new Node(root->kitu);
		strcpy(tmp->mabit,code);
		tmp->dodai = strlen(tmp->mabit);
		travao(bitcode,tmp);
		bodysize += root->tanso*tmp->dodai;
	}
	else
	{
		code[level] = '0';
		chuyencaythanhmabit(root->left,bitcode,bodysize,code,level+1);
		code[level] = '1';
		chuyencaythanhmabit(root->right,bitcode,bodysize,code,level+1);
		code[level] = '\0';
	}

}


int HuffmanCode::zip(char* inputFile, char* outputFile) {

	Reader* input = new Reader(inputFile);
	Writer* output = new Writer(outputFile);
	HCZHeader *header = new HCZHeader;
	int tongkitu = 0, tongsobit = 0, bodysize = 0;
	Node* cayhuffman = NULL;
	Node* chuoibitcode = NULL;
	Node* tmp;
	while(input->isHasNext())
	{
		char k = input->readChar();
		dem(cayhuffman,k);
	}

	tmp = cayhuffman;
	for(int i = 1; tmp != NULL; i++) {tmp = tmp->next; tongkitu = i;}

	chuyenthanhcay(cayhuffman);
	chuyencaythanhmabit(cayhuffman,chuoibitcode,bodysize);

	tmp = chuoibitcode;
	for(;tmp != NULL; tmp = tmp->next)
	{
		tongsobit += tmp->dodai;
	}

	header->setBodySize(bodysize);
	header->setTotal(tongkitu,tongsobit);

	tmp = chuoibitcode;
	for(;tmp != NULL; tmp = tmp->next)
	{
		header->set(tmp->kitu,tmp->dodai,tmp->mabit);
	}

	header->write(output);
	delete input;
	input = new Reader(inputFile);

	while(input->isHasNext())
	{
		char k = input->readChar();
		mahoa(output,chuoibitcode,k);
	}

    cout << "zipping...";

    delete input;
    delete output;
    delete header;
    return UN_IMPLEMENT;
}

void taobangma(Node* bangma,int nbit,char* code, char k)
{
	int vitri = 0;
	for(int i = 0 ; i < nbit ; i++)
	{
		if(code[i] == '0')
		{
			vitri = vitri*2 +1;
		}
		else
		{
			vitri = vitri*2 +2;
		}
	}
	bangma[vitri].kitu = k;
	bangma[vitri].dodai = nbit;
}

void giaima(Reader*& input,Writer* output,Node *bangma, int& bodysize)
{
	int vitri = 0;
	while(input->isHasNext())
	{
		if(input->readBit())
		{
			vitri = vitri*2 +2;
		}
		else
		{
			vitri = vitri*2 +1;
		}
		--bodysize;
		if(bangma[vitri].dodai)
		{
			output->writeByte(char2Int(bangma[vitri].kitu));
			return;
		}
	}
}

int HuffmanCode::unzip(char* inputFile, char* outputFile) {
    // TODO implement for unzip
	Reader* input = new Reader(inputFile);
	Writer* output = new Writer(outputFile);
	HCZHeader* header = new HCZHeader;
	header->read(input);
	Node bangma[10000];
	char *code = new char[256];
	for(int i = 0 ; i < max; i++){
		code[i] = '\0';
	}
	int bodysize = header->getBodySize();
	int nbit = 0;
	for(int i = 0 ; i < max ; i++)
	{
		if(header->get(char(i),nbit,code) == SUCCESS)
		{
			taobangma(bangma,nbit,code,char(i));
		}
	}


	while(bodysize>0)
	{
		giaima(input,output,bangma,bodysize);
	}

	delete input;
	delete output;
	delete header;







    cout << "unzipping...";
    return UN_IMPLEMENT;
}


#endif
