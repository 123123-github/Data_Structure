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
//Status 为函数类型，值为函数结果状态代码
typedef int Status;

//线性表_链表定义

//结点定义
struct LNode
{
	int data;
	LNode* next;
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
Status MakeNode(Link &p,int e)
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

//构造空链表L,成功时返回OK，否则返回ERROR
Status InitList_Link(LinkList &L)
{
	L.head = new LNode;
	if (L.head == NULL)
		return ERROR;
	
	L.head->next = NULL;
	L.tail = L.head;
	L.len = 0;

	return OK;
}	
//销毁链表L
Status DestroyList_Link(LinkList &L)
{
	if (L.head == NULL)
		return OK;

	Link p, q;
	p = L.head;
	q = p->next;

	while (q)
	{
		delete p;
		p = q;
		q = q->next;
	}
	delete p;
	
	L.head = NULL;
	L.tail = NULL;
	L.len = -1;

	return OK;
}
//将链表置为空表,成功返回OK，否则返回ERROR
Status ClearList_Link(LinkList &L)
{
	if (L.head == NULL)
		return ERROR;
	
	Link p, q;
	p = L.head->next;
	q = p;
	//将表头及元素断开,将链表置空
	L.head->next = NULL;
	L.tail = L.head;
	L.len = 0;

	//释放多余结点空间
	while (p)
	{
		q = q->next;
		delete p;
		p = q;
	}
	
	return OK;
}
//链表为空返回TRUE，否则返回FALSE
Status ListEmpty_Link(LinkList L)
{
	if (L.len == 0)
		return	TRUE;
	else
		return FALSE;
}
//返回链表的长度
int ListLength_Link(LinkList L)
{
	return L.len;
}
//用e返回L中的第i个值，成功时函数返回OK，否则返回FALSE
Status GetElem_Link(LinkList L, int i,int &e)
{
	if (i<1 || i>L.len)
		return ERROR;

	//j为p所指的结点位序(不包含头结点)
	Link p = L.head->next;
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
int LocateElem_Link(LinkList L,int e)
{
	Link p = L.head->next;
	int i = 1;

	//p存在时再访问p所指向的元素，与的两条语句顺序不能互换
	while (p && p->data != e)
	{
		p = p->next;
		i++;
	}
	if (p == NULL)
		return	0;

	return i;	
}
//用 pre_e 返回元素 cur_e 的前驱；操作成功返回OK，否则返回ERROR
Status PriorElem_Link(LinkList L,int cur_e,int &pre_e)
{
	int i = LocateElem_Link(L, cur_e);
	//有前驱的元素位序应满足的关系：2->L.len
	if (i<2 || i>L.len)
		return ERROR;
	
	GetElem_Link(L, i - 1, pre_e);
	
	return OK;
}
//用 next_e 返回元素 cur_e 的后继；操作成功返回OK，否则返回ERROR
Status NextElem_Link(LinkList L, int cur_e, int &next_e)
{
	int i = LocateElem_Link(L, cur_e);
	//有后继的元素位序应满足的关系：1->L.len-1
	if (i<1 || i>L.len - 1)
		return ERROR;

	GetElem_Link(L, i + 1, next_e);
	
	return OK;
}
//在链表的第i个位置插入e;若成功返回OK，否则返回ERROR
Status ListInsert_Link(LinkList &L,int i,int e)
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
		p = q;
		q = q->next;
		j++;
	}
	s->next = q;
	p->next = s;

	//假如插入前是 空表 或 插入位置为链表尾部，则需要改变尾指针指向。这两种情况下q为NULL
	if (q == NULL)
		L.tail = s;
	L.len++;

	return OK;

}
//在链表的第i个位置删除,用e返回其值;若成功返回OK，否则返回ERROR
Status ListDelete_Link(LinkList &L,int i,int &e)
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

	//若删除位置为链表尾部，则需修改尾指针指向
	if (p->next == NULL)
		L.tail = p;
	L.len--;

	return OK;
}
//遍历链表
Status ListTraverse_Link(LinkList L)
{
	Link p;
	p = L.head->next;

	//p结点存在则输出该节点的数据，p指针遍历链表头结点之后的结点
	while (p)
	{
		cout << p->data << '\t';
		p = p->next;
	}
	cout << endl;

	return 0;
}
//创建链表
void CreatList_Link(LinkList &L, int n)
{
	// s 指向为数据分配的结点 ; data 为结点中存入的数据
	Link s;
	int data;
	
	//初始化链表
	InitList_Link(L);
	for (int i = 0;i < n;i++)
	{
		cin >> data;
		MakeNode(s, data);
		L.tail->next = s;
		L.tail = s;
	}
	L.tail->next = NULL;
	L.len = n;

	return;
}


int main()
{
	LinkList L;

	int n;
	//1.创建 2.遍历 3.初始化函数 检验
	cout << "请输入元素个数n，及元素\n";
	cin >> n;
	CreatList_Link(L, n);
	ListTraverse_Link(L);

	int i, e, pre_e, next_e;

	//4.获取元素函数 检验
	cout << "请输入所要选取元素的位数：\n";
	cin >> i;
	GetElem_Link(L, i, e);
	cout << "该元素为：" << e << endl;

	//5.前一个 6.后一个 函数检测
	cout << "请输入一个表中的元素\n";
	cin >> e;
	NextElem_Link(L, e, next_e);
	PriorElem_Link(L, e, pre_e);
	cout << "该元素前一个为: " << pre_e << endl;
	cout << "该元素后一个为: " << next_e << endl;

	//7.长度
	cout << "此时线性表长度为：" << ListLength_Link(L) << endl;

	//8.插入 9.删除
	cout << "请输入插入元素e，插入位置i\n";
	cin >> e >> i;
	ListInsert_Link(L, i, e);
	cout << "插入后为：" << endl;
	ListTraverse_Link(L);

	cout << "请输入删除的元素位置i\n";
	cin >> i;
	ListDelete_Link(L, i, e);
	cout << "删除的元素为 " << e << endl;
	cout << "删除后为：" << endl;
	ListTraverse_Link(L);

	//10.定位 11.清空  12.是否为空 13.销毁
	cout << "输入一个元素\n";
	cin >> e;
	cout << "该元素位置为：";
	cout << LocateElem_Link(L, e) << endl;

	//清空线性表
	cout << "清空函数调用\n";
	ClearList_Link(L);
	ListTraverse_Link(L);

	if (ListEmpty_Link(L))
		cout << "线性表为空" << endl;

	DestroyList_Link(L);

	system("pause");

	return 0;
}

