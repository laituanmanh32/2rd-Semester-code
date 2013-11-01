/*
 * main.cpp
 *
 *  Created on: 23-10-2013
 *      Author: Manh
 */




#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
#include <sstream>

using namespace std;

#define LIMIT 1000
#define INPUT_NUMBER 1
#define CHA_LIMIT 256

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
int main(int argc, char **argv) {
	ofstream output;
	ofstream command;


	ifstream in;
	in.open("seed.txt");
	int s=0;
	in>>s;
	in.close();

	ofstream out;
	out.open("seed.txt");
	out<<s+1;
	out.close();

	int code[3] = {0,1,1};
	cout<<"Start generaing input!"<<endl;
	srand(s);

	command.open("command.txt");

	for(int k = 1 ; k <= INPUT_NUMBER ; k++){
		if(code[rand()%3]){

			command<<"zip"<<endl;
			output.open("input.txt");
			long long int a = (rand() * rand())%LIMIT + 1;
			for(int i = 0 ; i < a ; i++){
				output<<(char)(rand()%CHA_LIMIT);
			}
			output.close();
			cmd("cp input.txt input/input" + __(k) + _(".txt"));
			cmd("move input.txt Solution/output" + __(k) + _(".txt"));
		}
		else{
			command<<"unzip"<<endl;
			output.open("temp.txt");

			long long int a = (rand() * 30000)%LIMIT + 1;
			for(int i = 0 ; i < a ; i++){
			output<<(char)(rand()%CHA_LIMIT);
			}
			output.close();
			cmd("huffman zip temp.txt " +  _("input.txt"));
			cmd("move temp.txt " + _("Solution/output") + __(k) + _(".txt"));
			cmd("move input.txt input/input" + __(k) + _(".txt"));
		}

	}
	cout<<"done!";
}
