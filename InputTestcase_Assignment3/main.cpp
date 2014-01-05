/*
 * main.cpp
 *
 *  Created on: Nov 15, 2013
 *      Author: Manh
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <ctime>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
#include <sstream>
using namespace std;

#define INPUTNUMBER 10000

void cmd(string x){
	cout<< x<<endl;
	system(x.c_str());
}
string _(string S) {
	return "" + S + "";
}

string __(int k){
	ostringstream convert;
	convert << k;
	return convert.str();
}

void matrixGen(bool **&matrix,int maxVertex )
{
	static bool isConnected[] = {0,0,0,0,1,1};

	matrix = new bool*[maxVertex];
	for(int i = 0; i < maxVertex ; i++)
	{
		matrix[i] = new bool[maxVertex];
		memset(matrix[i],0,maxVertex);
	}

	for(int i = 0; i < maxVertex ; i++)
	{
		for(int j = 0 ; j < maxVertex; j++)
		{
			if(i==j || matrix[i][j]) continue;
			matrix[i][j] = matrix[j][i] =  isConnected[rand()%6];
		}
	}
}

void writeFile(bool**matrix,int maxVertex, string out){
	ofstream fO;
	fO.open(out.c_str());

	fO<<maxVertex<<endl;
	for(int i = 0; i < maxVertex ; i++)
	{
		fO<<(char)(i+'A')<<" ";
		for(int j = 0 ; j <maxVertex ; j ++)
		{
			if(matrix[i][j])
				fO<<(char)(j + 'A')<<" ";
		}
		fO<<endl;
	}

}

void moveFile(string file, string to)
{
	cmd("move " + file + " " + to);
}

int main(int argc, char **argv) {
	srand(time(0));
	cmd("del /F /S /Q Input\\");
	cmd("del /F /S /Q Solution\\");

	bool** matrix;


	int k = 1;
	while(k <= INPUTNUMBER)
	{
		int maxVertex = rand()%26 +1;
		matrixGen(matrix, maxVertex);

		writeFile(matrix,maxVertex,"input.txt");

		cmd("stat.exe > output.txt");
		moveFile("output.txt","Solution/output"+ __(k) + _(".txt"));
		moveFile("input.txt","Input/input"+ __(k) + _(".txt"));
		for(int i = 0; i < maxVertex ; i++)
		{
			delete matrix[i];
		}
		delete matrix;
		++k;
	}

}
