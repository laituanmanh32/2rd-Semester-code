#ifndef _HUFFMAN_CODE_H_
#define _HUFFMAN_CODE_H_

#include <iostream>
#include <fstream>
#include <cstring>

#include "Reader.h"
#include "Writer.h"
#include "HCZHeader.h"

using namespace std;

#define ERR -1

#define SUCCESS 0
#define UN_IMPLEMENT -2
#define MAXBUFSIZE 10000

// convert byte to character
#define byte2Char(val) ((unsigned char) ((val) % 256))

// convert character to ASCII
#define char2Int(ch) ((int) (ch) < 0 ? 128 + (((int) (ch)) & 127): (((int) (ch)) & 127))

class HuffmanCode {
public:
    int zip(char* inputFile, char* outputFile);
    int unzip(char* inputFile, char* outputFile);
    HuffmanCode() {
    }

private:

};

#endif
