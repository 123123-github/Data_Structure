// ADT List 基本操作
// 链式实现 (C++结构体)
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

//线性表_链表定义

//结点定义
struct LNode
{
	int data;
	int* next;
};
typedef LNode *Link;
//链表定义
struct LinkList
{
	Link head;
	Link tail;

	int len;
};

//链表基本相关函数:

//分配 p指向的结点，赋值为e；成功返回OK，否则返回ERROR
Status MakeNode(Link &p, int e)
{
	p = new LNode;
	if (p == NULL)
		return ERROR;

	p->data = e;
	p->next = NULL;

	return OK;
}
//释放 结点
Status DeleteNode(Link &p)
{
	if (p == NULL)
		return ERROR;

	delete p;
	return OK;
}


//十二个 基本函数实现：

//构造空表L,成功时返回OK，否则返回ERROR
Status InitList_Link(LinkList &L)
{
	L.head = new LNode;
	if (L.head == NULL)
		return ERROR;

	L.head->next = NULL;
	tail = head;
	len = 0;

	return OK;
}
//销毁线性表L
Status DestroyList_Link(LinkList &L)
{
	if (L.head == NULL)
		return OK;

	Link p, q;
	p = L.head;
	q = p->next;

	while (q != NULL)
	{
		delete p;
		p = q;
		q = q->next;
	}
	delete p;

	L.head = NULL;
	L.tail = L.head;
	len = -1;

	return OK;
}
//将表置为空表,成功返回OK，否则返回ERROR
Status ClearList_Link(LinkList &L)
{
	if (L.head == NULL)
		return ERROR;
	if (L.head == NULL)
		return OK;

	Link p, q;
	p = L.head->next;
	q = p->next;
	while (q != NULL)
	{
		delete p;
		p = q;
		q = q->next;
	}
	delete p;

	L.tail = L.head;
	len = 0;
}
//表为空返回TRUE，否则返回FALSE
Status ListEmpty_Link(LinkList L)
{
	if (L.len == 0)
		return	TRUE;
	else
		return FALSE;
}
//返回表的长度
int ListLength_Link(LinkList L)
{
	return L.len;
}
//用e返回L中的第i个值，成功时函数返回OK，否则返回FALSE
Status GetElem_Link(LinkList L, int i, int &e)
{
	if (i<1 || i>L.len)
		return ERROR;

	Link p = L.head;
	int j = 1;

	while (j<i)
	{
		p = p->next;
		j++;
	}
	e = p->data;

	return	OK;
}
//返回L中第一个与e相等的元素的位序，不存在时返回0
int LocateElem_Link(LinkList L, int e)
{
	Link p = L.head;
	int i = 1;

	while (p->data != e && p != NULL)
	{
		p = p->next;
		i++;
	}
	if (p == NULL)
		return	0;

	return i;
}
//用 pre_e 返回元素 cur_e 的前驱；操作成功返回OK，否则返回ERROR
Status PriorElem_Link(LinkList L, int cur_e, int &pre_e)
{
	int i = LocateElem_Link(L, cur_e);

	if (i<2 || i>L.len)
		return ERROR;

	GetElem_Link(L, i - 1, pre_e);
	return OK;
}
//用 next_e 返回元素 cur_e 的后继；操作成功返回OK，否则返回ERROR
Status NextElem_Link(LinkList L, int cur_e, int &next_e)
{
	int i = LocateElem_Link(L, cur_e);

	if (i<1 || i>L.len - 1)
		return ERROR;

	GetElem_Link(L, i + 1, next_e)
		return OK;
}
//在线性表的第i个位置插入e;若成功返回OK，否则返回ERROR
Status ListInsert_Link(LinkList &L, int i, int e)
{
	if (i<1 || i>L.len + 1)
		return ERROR;

	Link s;
	MakeNode(s, e);
	Link p, q;
	int j = 1;
	p = L.head;
	q = p->next;
	while (j < i)
	{
		p = p->next;
		q = q->next;
		j++;
	}
	s->next = q;
	p->next = p;

	L.len++;

	return OK;

}
//在线性表的第i个位置删除,用e返回其值;若成功返回OK，否则返回ERROR
Status ListDelete_Link(LinkList &L, int i, int &e)
{
	if (i<1 || i>L.len)
		return ERROR;

	Link p, q;
	int j = 1;
	p = L.head;
	q = p->next;
	while (j < i)
	{
		p = p->next;
		q = q->next;
		j++;
	}
	p->next = q->next;
	e = q->data;
	DeleteNode(q);

	L.len--;

	return OK;
}
//遍历线性表
Status ListTraverse_Sq()
{

}


