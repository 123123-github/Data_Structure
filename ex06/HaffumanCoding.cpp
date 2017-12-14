// HuffmanCoding 相关函数定义

#include <iostream>
#include <cstring>
#include "HaffumanCoding.h"
using namespace std;

//------------------- 相关调用函数 ------------------

Status Select(HuffmanTree p, int n, int & s1, int & s2)			/* parent 不存在下 ； 按照位序选 */
{
	int k = 1;
	while (p[k].parent != 0)			// k 到达第一个可判断位置
		k++;
	s1 = k;
	k++;
	while (p[k].parent != 0)			//第二个
		k++;
	if (p[s1].weight <= p[k].weight)	//相等时， s1 指向最前面的 ！！！
	{
		s2 = k;
	}
	else
	{
		s2 = s1;
		s1 = k;
	}

	for (int i = k + 1; i <= n; i++)
	{
		if (p[i].parent != 0)				//判断条件为 parent ！= 0
			continue;

		if (p[i].weight < p[s1].weight)
		{
			s2 = s1;
			s1 = i;
		}
		else if (p[i].weight < p[s2].weight)
		{
			s2 = i;
		}
	}

	return OK;
}


//------------------- 生成 Huffman 树 ------------------

Status CreatHuffmanTree(HuffmanTree & HT, int * w, int n)
{
	int m = 2 * n - 1;											// m 为树的节点数

	HT = new HTNode[m + 1];										// 0 号单元不使用
	if (!HT)
		return ERROR;

	for (int i = 1; i <= n; i++)								//初始化树--------------两个部分
		*(HT + i) = { *(w + i - 1), 0 , 0 ,0 };
	for (int i = n + 1;i <= m;i++)
		*(HT + i) = { 0,0,0,0 };

	int s1, s2;
	for (int i = n + 1; i <= m; i++)							//建树
	{
		Select(HT, i - 1, s1, s2);

		HT[s1].parent = i;
		HT[s2].parent = i;

		HT[i].left = s1;
		HT[i].right = s2;

		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	return OK;
}

void PrintHuffmanTree(HuffmanTree HT,int n)
{
	int m = 2 * n - 1;
	for (int i = 1;i <= m;i++)
	{
		cout << HT[i].weight << '\t' << HT[i].parent << '\t' << HT[i].left << '\t' << HT[i].right;
		cout << '\n';
	}
}

Status DestroyHuffmanTree(HuffmanTree & HT)
{
	delete[] HT;

	return OK;
}


//------------------- 读取编码 ------------------

Status GetHuffmanCode(HuffmanTree & HT, HuffmanCode & HC, int n)
{
	HC = new char*[n + 1];			// 0 号单元不使用
	if (!HC)
		return ERROR;

	char* temp;
	temp = new char[n];				//编码最长为 n - 1; temp 是长度为 n 的字符串，可存储 n - 1 位编码
	if (!temp)
		return ERROR;
	for (int i = 0;i < n;i++)		//初始化串
		temp[i] = '\0';

	int start;				//输入字符串编码的起始位置

	int c;														//当前字符位置
	int f;														//该字符的双亲
	for (int i = 1; i <= n; i++)
	{
		start = n - 2;											// start 归位 ！

		for (c = i, f = HT[c].parent; f != 0; c = f, f = HT[c].parent)			//调试中的错误，for后多加了分号！
		{
			if (c == HT[f].left)
				temp[start] = '0';
			else
				temp[start] = '1';

			start--;
		}

		HC[i] = new char[n - start - 1];
		if (!HC[i])
			return ERROR;

		strcpy_s(HC[i],n-start-1 ,temp + start + 1);		//从 temp 的存有字符处开始复制
	}

	delete[] temp;
	temp = NULL;

	return OK;
}

Status DestroyHuffmanCode(HuffmanCode & HC, int n)
{
	for (int i = 1; i <= n; i++)
		delete[] HC[i];

	delete[] HC;

	return OK;
}

void PrintHuffmanCode(HuffmanCode & HC,int n)
{
	for (int i = 1; i <= n; i++)
		cout << HC[i] << '\n';

	return;
}


//------------------- Huffman 编码 ------------------

Status HuffmanCoding(HuffmanTree & HT, HuffmanCode & HC, int * w, int n)
{
	if (n <= 1)
		return ERROR;

	CreatHuffmanTree(HT, w, n);

	GetHuffmanCode(HT, HC, n);

	return OK;
}

Status HuffmanCodingDestroy(HuffmanTree & HT, HuffmanCode & HC, int n)
{
	DestroyHuffmanTree(HT);

	DestroyHuffmanCode(HC, n);

	return OK;
}