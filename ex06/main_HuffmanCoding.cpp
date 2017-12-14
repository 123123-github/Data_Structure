#include <iostream>
#include "HaffumanCoding.h"
using namespace std;

int main()
{
	int w[8] = { 5,29,7,8,14,23,3,11 };
	int n=8;

	HuffmanTree HT;
	HuffmanCode HC;

	HuffmanCoding(HT, HC, w, n);

	PrintHuffmanCode(HC, n);

	HuffmanCodingDestroy(HT, HC, n);

	system("pause");

	return 0;
}