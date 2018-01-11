#include <vector>
#include <iostream>
#include "Huffman.h"
#include <fstream>
#include <string>
using namespace std;

int main()
{
	
	char filename[] = "article.txt";

	Huffman H;

	H.FileGetWeight(filename);

	H.HuffmanCoding();

	H.PrintHC();

	H.Coding();									// 编码

	H.Decode();									// 解码

	system("pause");

	return 0;
}