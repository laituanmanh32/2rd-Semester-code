#include "defs.h"
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

int numberEdge = 0;

class VertexInfo{
public:
	char name;
	int color;
	int vertexlevel;
	bool *connection;


	VertexInfo(){
		name = 'A';
		color = -1;
		vertexlevel = -1;
		connection = new bool[numberEdge];
		memset(connection,0,numberEdge);
	}

};

void display(bool* data){
	for(int i = 0;i<numberEdge;i++)
	{
		cout<<(data[i] == true ? 1 : 0)<<" ";
	}
	cout<<endl;
}


int getMax(VertexInfo* vertexMap){
	srand(numberEdge);
	static int last = rand()%numberEdge;
	int max = last;
	for(int i = 0 ; i < numberEdge; i++){
		max = (vertexMap[i].vertexlevel > vertexMap[max].vertexlevel ? i : max);
	}
	for(int i = 0 ; i < numberEdge; i++){
		if(vertexMap[max].connection[i] && vertexMap[i].vertexlevel>0){
			last = i;
			break;
		}
	}
	return max;
}

int getMin(VertexInfo* vertexMap)
{
	int min = 0;
	for(int i = 0 ; i < numberEdge; i++){
			min = (vertexMap[i].vertexlevel < vertexMap[min].vertexlevel ? i : min);
		}
	return min;
}

bool isExit(VertexInfo* vertexMap, int pos, int where)
{
	for(int i=0; i<pos; i++){
		if(vertexMap[where].connection[i] && vertexMap[i].color == vertexMap[pos].color){
			return true;
		}
	}
	return false;
}

int GraphColoring(FILE* f, Vertex* &v){// output: "Vertex* v" chua cac dinh da duoc to mau hop ly

	// Creat data from input
	char* buffer = new char[100];
	memset(buffer,'\0',100);

	fgets(buffer,100,f);
	sscanf(buffer, "%d", &numberEdge);
	VertexInfo *vertexMap = new VertexInfo[numberEdge];

	int maxColor = 0;

	for(int i = 0; i < numberEdge; i ++){
		fgets(buffer,100,f);
		int current = char2Int(buffer[0] - 'A');
		int j = 0;
		int level = 0;

		vertexMap[current].name = buffer[0];

		while(buffer[j] != '\n')
		{
			if(buffer[j] != ' ' && char2Int(buffer[j] - 'A')!=i){
				vertexMap[current].connection[char2Int(buffer[j] - 'A')] = true;
				++level;
			}
			j++;
		}
		vertexMap[current].vertexlevel = level;
		display(vertexMap[current].connection);
	}
//	for(int i = 0 ; i < numberEdge ; i++)
//	{
//		cout<<(char)(i+'A')<<" "<< vertexMap[i].vertexlevel<<endl;
//	}
//	cout<< getMax(vertexMap)<<endl;
	// End creat input

	// Coloring graph
	for(int i = 0 ; i < numberEdge ; i++){
		int current = getMax(vertexMap);
		int color = 1;
		int isSame = 1;
		while(isSame)
		{
			isSame = 0;
			for(int j = 0 ; j < numberEdge ; j++){
		//			cout<< check(vertexMap,j,current);
				if(vertexMap[current].connection[j] && vertexMap[j].color == color  && !isExit(vertexMap,j,current)){
					++color;
					isSame = 1;
				}
			}
		}
		vertexMap[current].color = color;
		vertexMap[current].vertexlevel = -1;
		maxColor = (color > maxColor ? color : maxColor);
		cout<<vertexMap[current].name<<" mau :"<<vertexMap[current].color<<endl;
	}

//	cout<<maxColor;
	return maxColor;
}


