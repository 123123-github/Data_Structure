// 哈希表
// 二次探测再散列处理冲突
#pragma once
#include "Status.h"

//-------------------- 宏定义 ------------------------

#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

#define NULLKEY 2147483647i32


//-------------------- 哈希表类 -----------------------

class HashTable
{
private:
	int *elem;														//哈希线性表
	int count;														//表中数据
	int tablesize;													//表长
	int(*Hash)(int);												//哈希函数

public:
	HashTable(int size);
	HashTable(const HashTable& H);
	~HashTable();

public:
	Status Search(int key, int &p, int &c);							// key:带查找元素 p:未找到后插入位置 c:冲突次数
	Status Insert(int e);											// 插入元素
	void SetHash(int(*HashFunc)(int));								// 设置哈希函数
	void collision(int start, int &p, int c);						//二次探测再散列

public:
	void PrintHashTable();											// 辅助检测函数
};