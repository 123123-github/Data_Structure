// 线性表类
// 主要用于查找排序
#pragma once
#include "Status.h"

//--------- 宏定义 -----------

#define INITSIZE 100
#define SIZEINCREMENT 50

//---------- 基数排序用到的辅助结构 ----------

struct qnode
{
	int data;
	qnode *next;
};

struct queue
{
	qnode* front;
	qnode* tail;
};

void makenode(qnode* &s, int e);		// 分配结点


//--------------------- 线性表 ---------------------

class List
{
private:
	int *elem;											// 线性表
	int length;											// 表中元素数
	int listsize;										// 表长
	bool order;											// 是否有序

public:
	List(int size = INITSIZE);
	List(const List& L);
	~List();

public:
	int ListLength();									// 返回元素数
	bool IsOrder();										
	Status ListInsert(int e);
	Status ListInsert(int e, int position);				// 插入指定位置
	Status ListDelete(int e);							// 删除第一个出现的元素
	void PrintList();

public:
	int Search(int key);
	int BSearch(int key);

public:
	void BubbleSort();
	void SelectSort();
	void InsertSort();

public:
	void ShellInsert(int d);										// 希尔排序
	void ShellSort();

	int Partition(int low, int high);								// 快速排序
	void QSort(int i, int j);
	void QuickSort();

	void HeapAdjust(int s, int m);									// 堆排序
	void HeapSort();

	void Merge(int s, int m, int n, int * &result);					// 归并排序
	void MergeSort();

	void RadixSort();												// 基数排序
	int GetKeynum();
	void ChangeToLink(qnode* &Head);
	void Distribute(qnode* Head, queue* Q, int rixnum);
	void Collect(queue * Q, qnode * Head);
	void ChangeToList(qnode* &Head);
};
