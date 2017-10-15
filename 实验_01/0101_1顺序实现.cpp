// ADT List 基本操作
// 顺序实现 (C++结构体)

#include "stdafx.h"
#include <iostream>
using namespace std;
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status 为函数类型，值为函数结果状态代码
typedef int Status;

//线性表定义
#define LIST_INIT_SIZE 100 //线性表存储空间 初始分配量
#define LISTINCREMENT 10   //线性表存储空间 分配增量	 
struct SqList
{
	int *elem;
	int length;
	int listsize;
};

//十二个 基本函数实现：

//构造空表L
Status InitList_Sq(SqList &L)
{
	L.elem = new int[LIST_INIT_SIZE];
	if (L.elem == NULL)
		exit(OVERFLOW);

	L.length  =  0;
	L.listsize  =  LIST_INIT_SIZE;

	return OK;
}	
//销毁线性表L
Status DestroyList_Sq(SqList &L)
{
	if (L.elem == NULL)
		return ERROR;
	
	delete[] L.elem;

	return OK;
}
//将表置为空表
Status ClearList_Sq(SqList &L)
{
	if (L.elem == NULL)
		return ERROR;

	L.length = 0;

	return OK;
}
//表为空返回TRUE，否则返回FALSE
Status ListEmpty_Sq(SqList L)
{
	if (L.elem == NULL)
		return ERROR;

	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}
//返回表的长度
int ListLength_Sq(SqList L)
{
	if (L.elem == NULL)
		return ERROR;

	return L.length;
}
//用e返回L中的第i个值，成功时函数返回OK，否则返回FALSE
Status GetElem_Sq(SqList L, int i, int &e)
{
	if (i < 1 || i>L.length)
		return FALSE;

	e = *(L.elem + i - 1);

	return OK;
}
//返回L中第一个与e相等的元素的位序，不存在时返回0
int LocateElem_Sq(SqList L, int e)
{
	if (L.elem == NULL)
		return ERROR;

	for (int i = 0;i <= L.length - 1;i++)
		if (L.elem[i] == e)
			return i + 1;

	return 0;
}
//用 pre_e 返回元素 cur_e 的前驱；操作成功返回OK，否则返回ERROR
Status PriorElem_Sq(SqList L, int cur_e, int &pre_e)
{
	if (L.elem == NULL)
		return ERROR;

	int i = LocateElem_Sq(L, cur_e);
	if (i < 2 || i> L.length)
		return ERROR;

	pre_e = *(L.elem + i - 2);

	return	OK;
}
//用 next_e 返回元素 cur_e 的后继；操作成功返回OK，否则返回ERROR
Status NextElem_Sq(SqList L, int cur_e, int &next_e)
{
	if (L.elem == NULL)
		return ERROR;

	int i = LocateElem_Sq(L, cur_e);
	if (i < 1 || i> L.length - 1)
		return ERROR;

	next_e = *(L.elem + i);

	return	OK;
}
//在线性表的第i个位置插入e;若成功返回OK，否则返回ERROR
Status ListInsert_Sq(SqList &L, int i, int e)
{
	if (i<1 || i> L.length + 1) //判断i是否合法
		return ERROR;

	//若线性表已满，则扩展线性表长度
	if (L.length == L.listsize)
	{
		//申请新空间
		int* newbase;
		newbase = new int[L.length + LISTINCREMENT];
		if (newbase == NULL)
			exit(OVERFLOW);

		//移动元素
		for (int i = 0;i < L.length;i++)
			newbase[i] = L.elem[i];

		//更改线性表数组指针指向,修改线性表长度参数
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}

	//移动元素
	int j;
	for (j = L.length;j >= i;j--)
		*(L.elem + j) = *(L.elem + j - 1);

	//插入元素，并修改线性表长度（长度+1）
	*(L.elem + i - 1) = e;
	L.length++;

	return OK;
}
//在线性表的第i个位置删除元素，并用e返回其值;若成功返回OK，否则返回ERROR
Status ListDelete_Sq(SqList &L, int i, int &e)
{
	if (i<1 || i>L.length) //判断i是否合法
		return ERROR;

	//返回第i个元素的值
	e = *(L.elem + i - 1);
	//移动元素并删除
	int j;
	for (j = i + 1;j <= L.length;j++)
		*(L.elem + j - 2) = *(L.elem + j - 1);

	//修改线性表长度（长度-1）
	L.length--;

	return OK;
}
//遍历线性表
Status ListTraverse_Sq(SqList L)
{}



int main()
{
    return 0;
}

