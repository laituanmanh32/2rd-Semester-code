#include "defs.h"
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

int numberEdge, colorcount;

template<typename T>
void init(T* data, T value, int size){
	for(int  i = 0 ; i < size ; i++){
		data[i] = value;
	}
}

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
		init(connection,false,numberEdge);
	}

};


bool isExit(VertexInfo* vertexMap, int pos, int where)
{
	for(int i=0; i<pos; i++){
		if(vertexMap[where].connection[i] && vertexMap[i].color == vertexMap[pos].color){
			return true;
		}
	}
	return false;
}

void add(VertexInfo vertex, Vertex*& head){
	if(head == NULL){
		head = new Vertex;
		head->color = vertex.color;
		head->name = vertex.name;
		head->next = NULL;
	}
	else
	{
		Vertex* tmp = head;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new Vertex;
		tmp = tmp->next;
		tmp->color = vertex.color;
		tmp->name = vertex.name;
		tmp->next = NULL;
	}
}

int ArroundColor(VertexInfo* map, int current){
	int count = 0;
	for(int i = 0 ; i < numberEdge ; i++){
		if(map[current].connection[i] && map[i].color != -1 && !isExit(map,i,current)){
			count++;
		}
	}
	return count;
}

void color(VertexInfo* map, int current){
	int color = 1;
	int isSame = 1;
	while(isSame)
	{
		isSame = 0;
		for(int j = 0 ; j < numberEdge ; j++){
	//			cout<< check(vertexMap,j,current);
			if(map[current].connection[j] && map[j].color == color){
				++color;
				isSame = 1;
			}
		}
	}
	map[current].color = color;
	map[current].vertexlevel = -1;
//	cout<<map[current].name<<" mau :"<<map[current].color<<endl;

	colorcount = (colorcount > color ? colorcount : color);
}



int GraphColoring(FILE* f, Vertex* &v){// output: "Vertex* v" chua cac dinh da duoc to mau hop ly

	// Creat data from input
	char* buffer = new char[100];
	init(buffer,'\0',100);

	fgets(buffer,100,f);
	sscanf(buffer, "%d", &numberEdge);
	VertexInfo *vertexMap = new VertexInfo[numberEdge];

	for(int i = 0; i < numberEdge; i ++){
		fgets(buffer,100,f);
		int current = char2Int(buffer[0] - 'A');
		int j = 0;
		int level = 0;

		vertexMap[current].name = buffer[0];

		while(buffer[j] != '\n')
		{
			if(buffer[j] != ' ' && buffer[j] != '\r' && char2Int(buffer[j] - 'A')!=i){
				vertexMap[current].connection[char2Int(buffer[j] - 'A')] = true;
				++level;
			}
			j++;
		}
		vertexMap[current].vertexlevel = level;
//		display(vertexMap[current].connection);
	}

	// Coloring graph
	int current = 0;
	for(int i = 0 ; i < numberEdge ; i++){
		int max = -1;
		for(int i = 0 ; i < numberEdge ; i++){
			if(vertexMap[i].color == -1){
				int temp = ArroundColor(vertexMap,i);
				if( temp > max){
					max = temp;
					current = i;
				}
				if( temp == max){
					if(vertexMap[i].vertexlevel > vertexMap[current].vertexlevel)
						current = i;
				}
			}
		}
		color(vertexMap,current);
		add(vertexMap[current],v);
	}

//	cout<<maxColor;
	return colorcount;
}


