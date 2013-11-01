#ifndef _HUFFMAN_CODE_CPP_
#define _HUFFMAN_CODE_CPP_

#include "HuffmanCode.h"

// convert byte to character
#define byte2Char(val) ((unsigned char) ((val) % 256))

// convert character to ASCII
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

struct Node{
	char kytu;
	int tanso;
	Node* left;
	Node* right;
	Node* next;

	Node(){
		kytu = '\0';
		tanso=0;
		left=right=next=NULL;
	}

	Node(char data){
		kytu = data;
		tanso=1;
		left = right =next =NULL;
	}
};


Node *swap(Node* L1, Node* L2){
	L1->next = L2->next;
	L2->next = L1;
	return L2;
}

void sapxep(Node*& root, int tong){
	Node* cur = root,*pre=root;
	for(int i = 0; i < tong; i++){
		for(;cur->next!=NULL;pre = cur,cur = cur->next){
			if(cur->tanso > cur->next->tanso){
				cur = swap(cur,cur->next);
				if(cur->next == root){
					root = cur;
					break;
				}
				pre->next = cur;
			}

		}
		cur = pre = root;
	}
}

void duyet(Node* root,char**& bangma,char*& ma,int*&bangkitu,int*& dodai,int*& bangtanso){
	static int k =-1;
	static int dem = 0;
	if(root->left == NULL && root->right == NULL)
	{
		bangkitu[char2Int(root->kytu)] = dem;
		dodai[dem] = strlen(ma);
		strcpy(bangma[dem],ma);
		bangtanso[dem] = root->tanso;
		++dem;
	}
	else{++k;
		ma[k]='0';duyet(root->left,bangma,ma,bangkitu,dodai,bangtanso);
		ma[k]='1'; duyet(root->right,bangma,ma,bangkitu,dodai,bangtanso);
		ma[k]='\0';
		--k;
	}
}

int HuffmanCode::zip(char* inputFile, char* outputFile) {
	Reader *input = new Reader(inputFile);
	Writer *output = new Writer(outputFile);
	HCZHeader header;
	Node* cayhuffman = NULL;
	int tongsokituduocsudungtrongfiletext =0;
	// dem tan so
	while(input->isHasNext()){
		char k = input->readChar();
		bool daxuly = 0;
		Node* cur = cayhuffman,*pre=cayhuffman;
		if(cayhuffman == NULL){cayhuffman = new Node(k);tongsokituduocsudungtrongfiletext+=1;continue;}
		while(cur != NULL){ if(cur->kytu ==k){ cur->tanso +=1; daxuly = 1; break;} pre = cur; cur = cur->next;}
		if(!daxuly){pre->next = new Node(k);tongsokituduocsudungtrongfiletext+=1;}
	}

	// tao cay
	sapxep(cayhuffman,tongsokituduocsudungtrongfiletext);
	int count = tongsokituduocsudungtrongfiletext;
	while(count > 1){
		Node* child1 = cayhuffman; cayhuffman = cayhuffman->next; child1->next = NULL;
		Node* child2 = cayhuffman; cayhuffman = cayhuffman->next; child2->next = NULL;
		Node* father = new Node; father->right = child1; father->left = child2; father->tanso = child1->tanso + child2->tanso; father->next = cayhuffman;
		cayhuffman = father;
		sapxep(cayhuffman,--count);
	}
	// tao bang ma
	char **bangma; // bang ma
	bangma = new char*[256];
	for(int i = 0 ; i < 256 ; i++){
		bangma[i] = new char[256];
		memset(bangma[i],0,256);
	}
	char *ma = new char[256]; // ma tam thoi
	memset(ma,0,256);
	int *bangkitu = new int[256]; // vi tri luu thong tin ki tu
	for(int i = 0 ; i < 256 ; i++) bangkitu[i] = -1;
	int *dodai = new int[256]; // do dai ki tu
	int *bangtanso = new int[256]; // tan so ki tu
	duyet(cayhuffman,bangma,ma,bangkitu,dodai,bangtanso);
	int bodysize = 0;
	int tongsobitdungdemahoa = 0;
	for(int i = 0;i<256;i++){ if(bangkitu[i] != -1){ bodysize+=bangtanso[bangkitu[i]]*dodai[bangkitu[i]]; tongsobitdungdemahoa += dodai[bangkitu[i]];}}
	delete input;
	input= new Reader(inputFile);
	header.setBodySize(bodysize);
	header.setTotal(tongsokituduocsudungtrongfiletext,tongsobitdungdemahoa);
	for(int i = 0; i < 256 ; i++){ if(bangkitu[i] != -1 ) header.set((char)i,dodai[bangkitu[i]],bangma[bangkitu[i]]);}
	header.write(output);
	while(input->isHasNext()){int k = input->readChar();for(int i = 0 ; i < dodai[bangkitu[char2Int(k)]]; i++) output->writeBit(bangma[bangkitu[char2Int(k)]][i] - 48);}
    cout << "zipping...";
    delete output;
    delete input;
    return UN_IMPLEMENT;
}

int HuffmanCode::unzip(char* inputFile, char* outputFile) {
    Node huffman[6000];
    Reader *input = new Reader(inputFile);
    Writer *output = new Writer(outputFile);
    HCZHeader header;
    header.read(input);
    int bodysize =header.getBodySize();
    int tongsokidasudung = 0;
    int tongsobitduocdungdemahoa = 0;
    int dodai;
    char* code = new char[256];
    memset(code,'\0',256);
    header.getTotal(tongsokidasudung,tongsobitduocdungdemahoa);
    for(int i = 0 ; i < 256 ; i++){
    	if(header.get((char)i,dodai,code) == SUCCESS){
    		int vitri = 0;
    		for(int  j = 0 ; j < dodai ; j++) if(code[j] == '0') vitri = 2*vitri + 1;else vitri = 2*vitri +2;
    		huffman[vitri].kytu=(char)i;huffman[vitri].tanso = 1;
    	}
    }
    while(bodysize >0){
    	int vitri = 0;
    	while(input->isHasNext()){
    		if(input->readBit()) vitri = 2*vitri +2; else vitri = 2*vitri +1; --bodysize;
    		if(huffman[vitri].tanso == 1){ output->writeByte(char2Int(huffman[vitri].kytu));break;
    		}
    	}
    }

    delete input;
    delete output;

    cout << "unzipping...";
    return UN_IMPLEMENT;
}


#endif
