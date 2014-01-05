/*
 * main.cpp
 *
 *  Created on: 21-09-2013
 *      Author: Manh
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#define NUMBER_INPUT 499
#define MAX_OPERAND 30

int main(int argc, char **argv) {

	// Variable
	char setOperator[3] = {'+','-','*'};
	char setSubOperator[4] = {' ',' '};
	char sign[3] = {'-','@','@'};
	ostringstream convert;

	// Declare filename
	string seed = "seed.txt",
			output = "";

	// seed value
	int seedNum;

	// set seed for randomize
	ifstream ifile;
	ifile.open(seed.c_str(),ios::in);
	ifile >> seedNum;
	ifile.close();
	//
	srand(seedNum);

	ofstream ofile;
	ofile.open("seed.txt");
	ofile << seedNum + 1;
	ofile.close();



	for(int k = 0; k<NUMBER_INPUT + 1; k++)
	{
		convert << k;
		output = "INPUT/input" + convert.str() + ".txt";
		convert.str(string());
		convert.clear();
		ofile.open(output.c_str(), ios::out);
		// Creat input
		int maxOperand = rand()%MAX_OPERAND +1;
		ofile << maxOperand<<endl;


		// Creat 1 input
		if (1 == maxOperand)
		{
			switch (setSubOperator[rand()%2])
					{
						case '^':

							// Creat negative number
							if (sign[rand()%3] == '-')
								ofile <<'-';

							ofile << rand()%500 << '^' << rand()%100;
							break;

						case '!':
							ofile << rand()%150 + 1 <<'!';
							break;

					}
		}

		else
		{
			if(maxOperand<=20)
			{

			// Creat Operand
				for(int i = 0; i< maxOperand;i++)
				{
					switch (setSubOperator[rand()%2])
					{
						case '^':
							// Creat negative number
							if (sign[rand()%3] == '-')
								ofile <<'-';

							ofile << rand()%500 << '^' << rand()%100<<endl;
							break;

						case '!':
							ofile << rand()%150<<'!'<<endl;
							break;

						default:
							if (sign[rand()%3] == '-')
								ofile <<'-';
							ofile <<rand()*9999<<rand()*9999<<rand()*9999<<rand()*9999<<endl;
							break;
					}


				}
			}
			else
			{
				for(int i = 0; i< maxOperand;i++)
				{
					switch (setSubOperator[rand()%2])
					{
						case '^':
							// Creat negative number
							if (sign[rand()%3] == '-')
								ofile <<'-';
							//
							ofile << rand()%100 << '^' << rand()%80<<endl;
							break;

						case '!':
							ofile << rand()%80<<'!'<<endl;
							break;

						default:
							if (sign[rand()%3] == '-')
								ofile <<'-';
							ofile <<rand()*9999<<rand()*9999<<rand()*9999<<endl;
							break;
					}
			}



		}

			//Creat Operator
			for (int i = 0; i < maxOperand-2; i++)
			{
				ofile << setOperator[rand()%3]<<endl;
			}
			ofile << setOperator[rand()%3];


		// Close file
		ofile.close();

	}



	}
	cout<<"Done!";
}
