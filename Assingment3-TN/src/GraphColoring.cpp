#include "defs.h"

template<typename T>
void out(T* data, int size){
	for(int i = 0 ; i < size ; i++){
		cout<<data[i]<<" ";
	}
	cout<<endl;
}

int GraphColoring(FILE* f, Vertex* &v){// output: "Vertex* v" chua cac dinh da duoc to mau hop ly

	int vertexTotal, colorcount = 0;
	Vertex* run = NULL;

	char* temp = new char[100];
	for(int i = 0 ; i < 100 ; i++){
		temp[i] = '\0';
	}

	fgets(temp,100,f);
	sscanf(temp, "%d", &vertexTotal);


	bool** matrix = new bool*[vertexTotal];
	for(int i = 0 ; i < vertexTotal ; i ++){
		matrix[i] = new bool[vertexTotal];
		for(int j = 0 ; j < vertexTotal ; j++){
			matrix[i][j] = 0;
		}
	}

	int* vertexdegree = new int [vertexTotal];
	for(int i = 0 ; i < vertexTotal ; i++){
		vertexdegree[i] = 0;
	}

	int* vertexcolor = new int[vertexTotal];
	for(int i = 0 ; i < vertexTotal ; i++){
		vertexcolor[i] = 0;
	}




	// Get input
	for(int i = 0 ; i < vertexTotal ; i++){
		char vertex, next;
		int degree =0;
		fscanf(f,"%c%c", &vertex, &next);

		while(next != '\n'){
			if(next != ' ' && next != '\r'){
				matrix[vertex -'A'][next - 'A'] = true;
				++degree;
			}
			fscanf(f,"%c",&next);
		}
		vertexdegree[vertex - 'A'] = degree;
	}

	for(int  i = 0 ; i < vertexTotal ; i++){
		int k = 0;
		int max = -1;
		int color = 1;
		bool flag = 1;



		for(int j = 0 ; j < vertexTotal ; j++){
			if(vertexcolor[j] == 0 && vertexdegree[j] > max){
				max = vertexdegree[j];
				k = j;
			}
		}

		while(flag){
			flag = 0;
			for(int j = 0 ; j < vertexTotal ; j ++){
				if(matrix[k][j] && vertexcolor[j] == color){
					++color;
					flag = 1;
				}
			}
		}
		vertexcolor[k] = color;
		if( color > colorcount) colorcount = color;

	}
	for(int i = 0 ; i < vertexTotal ; i++){
		if(run == NULL){
			run = new Vertex;
			v = run;
		}
		else
		{
			run->next = new Vertex;
			run = run->next;

		}
		run->name = i + 'A';
		run->color = vertexcolor[i];
		run->next = NULL;
	}

	return colorcount;
}


