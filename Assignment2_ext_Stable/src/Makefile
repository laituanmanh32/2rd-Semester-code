# This is Makefile for assingment 2 - Data structure and Algorithm
# Writen by: Hung Vo (vthung)
# Date: Oct 1, 2013

all: huffman

huffman: main.o Reader.o Writer.o HCZHeader.o HuffmanCode.o hr_time.o
	g++ main.o Reader.o Writer.o HCZHeader.o HuffmanCode.o hr_time.o -o huffman

main.o: main.cpp
	g++ -c main.cpp

Reader.o: Reader.cpp Reader.h
	g++ -c Reader.cpp

Writer.o: Writer.cpp    Writer.h
	g++  -c Writer.cpp

HCZHeader.o: HCZHeader.cpp  HCZHeader.h
	g++ -c HCZHeader.cpp

HuffmanCode.o: HuffmanCode.cpp  HuffmanCode.h
	g++ -c HuffmanCode.cpp -o HuffmanCode.o
    
hr_time.o: hr_time.h hr_time.cpp
	g++ -c hr_time.cpp -o hr_time.o
clean:
	rm -rf *o huffman
    