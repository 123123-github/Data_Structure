#include <iostream>
#include "HashTable.h"
using namespace std;

//-------------------- 哈希表类函数实现 -----------------------

HashTable::HashTable(int size)
{
	count = 0;
	tablesize = size;
	Hash = nullptr;

	elem = new int[size];
	for (int i = 0;i < tablesize;++i)
		elem[i] = NULLKEY;
}

HashTable::HashTable(const HashTable & H)
{
	count = H.count;
	Hash = H.Hash;
	tablesize = H.tablesize;

	elem = new int[tablesize];
	for (int i = 0; i < tablesize; i++)
		elem[i] = H.elem[i];
}

HashTable::~HashTable()
{
	count = -1;
	tablesize = -1;
	Hash = nullptr;

	delete[] elem;
	elem = nullptr;
}


//------------ 基本操作 -----------

Status HashTable::Search(int key, int & p, int & c)
{
	int start;

	p = Hash(key);
	start = p;
	c = 0;

	while (elem[p] != NULLKEY && elem[p] != key)				//1. 存在 且 不相等 -> 处理冲突
		collision(start, p, ++c);

	if (elem[p] == NULLKEY)										//2. 不存在 -> 表中没有这个数据
		return UNSUCCESS;
	else														//3. 存在 且 相等 -> 找到
		return SUCCESS;
}

Status HashTable::Insert(int e)
{
	int p;										// 插入位置 
	int c = 0;									//冲突次数

	if (Search(e, p, c))						// 找到说明元素重复
		return DUPLICATE;
	else										// 没有重复 找到插入位置
	{
		elem[p] = e;
		count++;

		return OK;
	}
}

void HashTable::SetHash(int(*HashFunc)(int))
{
	Hash = HashFunc;
}

void HashTable::collision(int start, int & p, int c)
{
	int d;

	if (c % 2 == 0)									// 偶数次冲突
		d = -c * c / 4;
	else											// 奇数次冲突
		d = (c + 1)*(c + 1) / 4;

	p = (start + d + tablesize) % tablesize;					// 确定表中位置
}

void HashTable::PrintHashTable()
{
	for (int i = 0; i < tablesize; i++)
	{
		cout << elem[i] << '\t';
	}
	cout << endl;
}
