#include "defs.h"

class myVertex{
public:
	int color;
	bool isConnected;

	myVertex(){
		color = -1;
		isConnected = 0;
	}
};

int vertexNumber = 0, colorNumber = 0;
myVertex** adjMatrix;
int* color;


void reset(char*& a, int size){
	for(int i = 0 ; i < size ; i++){
		a[i] = 0;
	}
}

void display(myVertex** a ,int index, int size){
	for(int i = 0 ; i < size ; i++){
		cout<<a[index][i].isConnected<<" ";
	}
	cout<<endl;
}

int getDegree(int index){
	int count = 0;
	for(int i = 0 ; i < vertexNumber ; i ++){
		if(adjMatrix[index][i].isConnected) ++count;
	}
	return count;
}

int getMin()
{
	int min = 1000;
	int chosed;
	for(int i = 0 ; i < vertexNumber ; i++){
		int d = getDegree(i);
		if(adjMatrix[i][0].color == -1){
			if( d < min){
				min = d;
				chosed = i;
			}
		}
	}
	return chosed;
}

void coloring(int index){
	int  color = 1;
	bool flag =  1;
	while(flag){
		flag = 0;
		for(int i = 0 ; i < vertexNumber ; i++){
			if(adjMatrix[i][index].isConnected == 1 && adjMatrix[i][0].color == color){
				++color;
				flag = 1;
			}
		}
	}
	if(color > colorNumber ) colorNumber = color;
	adjMatrix[index][0].color = color;
}

int GraphColoring(FILE* f, Vertex* &v){// output: "Vertex* v" chua cac dinh da duoc to mau hop ly


	char* temp = new char[60];
	reset(temp, 60);

	fscanf(f,"%d", &vertexNumber);
	fscanf(f,"%d");

	adjMatrix = new myVertex*[vertexNumber];
	for(int i = 0 ; i < vertexNumber ; i++){
		adjMatrix[i] = new myVertex[vertexNumber];
	}

	for(int i= 0 ; i < vertexNumber ; i++){
		fgets(temp,60,f);
		for(int j = 1 ; temp[j] != '\n'; j++){
			if(temp[j] >= 'A' && temp[j] <= 'Z'){
				adjMatrix[temp[0] - 'A'][temp[j]-'A'].isConnected = true;
			}
		}
	}

	for(int i = 0 ; i < vertexNumber ; i++){
		coloring(getMin());

	}

	for(int i = 0 ; i  < vertexNumber ; i++){
		Vertex* temp = new Vertex;
		temp->color = adjMatrix[i][0].color;
		temp->name = i + 'A';
		temp->next = v;
		v = temp;
	}
	return colorNumber;
}


