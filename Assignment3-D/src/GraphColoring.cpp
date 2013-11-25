#include "defs.h"

int n, somau;
bool** matranke;
int* mangmau;
bool* kiemtratomau;

int loadGragh(FILE* f){
	fscanf(f,"%d",&n);
	matranke = new bool*[n];
	for(int i = 0 ; i < n ; i++){
		matranke[i] = new bool[n];
		memset(matranke[i],0,n);
	}
	kiemtratomau = new bool[n];
	for(int i = 0 ; i < n ; i++){
		kiemtratomau[i] = 0;
	}
	mangmau = new int[n];
	for(int i = 0 ; i < n ; i++){
		mangmau[i] = 0;
	}
	fscanf(f,"%d");
	char* temp;
	temp = new char[100];
	for(int i = 0 ; i < 100 ; i++){
		temp[i] = '\0';
	}
	for(int i = 0; i < n; i ++){
		fgets(temp,100,f);
		int j = 1;
		while(temp[j] != '\n')
		{
			if(temp[j] != ' '){
				matranke[temp[0] - 'A'][temp[j] - 'A'] = true;
			}
			j++;
		}
	}
	return 1;
}

int bac(int index){
	int dem = 0;
	for(int i = 0 ; i < n ; i++){
		if(matranke[index][i]) ++dem;
	}
	return dem;
}

int getNext(){
	int k = 0;
	int min = 100;
	for(int i = 0 ; i < n ; i++){
		if(!kiemtratomau[i]){
			if(bac(i) < min){ min = bac(i); k = i;}
		}
	}
	return k;
}


void tomau(){
	int k = 0;

	for(int i = 0 ; i< n ;i++){
		int max = -1;
		int mau = 1;
		bool khongtrung = 0;
		while(!khongtrung){
			khongtrung = 1;
			for(int i = 0 ; i<n;i++){
				if(matranke[k][i] == true && mangmau[i] == mau){ mau++; khongtrung = 0;}
			}

		}
		if(somau < mau) somau = mau;
		mangmau[k] = mau;
		kiemtratomau[k] = true;
		for(int j = 0 ; j < n ; j++){
			if(kiemtratomau[j] == false && bac(j) > max)
			{
				max = bac(j);
				k = j;
			}
		}
	}
}
int GraphColoring(FILE* f, Vertex* &v){// output: "Vertex* v" chua cac dinh da duoc to mau hop ly

	loadGragh(f);
	tomau();
	for(int i = 0 ; i < n ; i++){
		Vertex *tmp = new Vertex;
		tmp->color = mangmau[i];
		tmp->name = i + 'A';
		tmp->next = v;
		v= tmp;
	}
	return somau;
}


