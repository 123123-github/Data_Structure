//约瑟夫问题
//链式实现（C++结构体）

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
//构造空表L,成功时返回OK，否则返回ERROR
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
//在链表中插入数据，插入第一位
void ListInsert_First(LinkList &L, Link p)
{
	p->next = L.head->next;
	L.head->next = p;

	if (L.head == L.tail)
		L.tail = p;

	L.len++;
}

int main()
{   //初始的输入值
	int n, s, m;

	cout << "请依次输入：圆桌人数n，开始报数人位序s，出列人报数数m.\n";
	cin >> n >> s >> m;
	cout << endl;

	//建立链表，存储信息
	LinkList L;
	Link t, p;

	if (!InitList_Link(L))
		return ERROR;

	for (int i = n; i > 0; i--)
	{
		MakeNode(t,i);
		ListInsert_First(L, t);
	}

	//d为位序
	int d;
	int delete_elem;
	int i = 0;//i记录是第几次出列

	while (n != 0)
	{
		d = (s + m - 1) % n;
		if (d == 0)
			d = n;

		ListDelete_Link(L, d, delete_elem);
		cout << "第" << ++i << "次出列的是" << delete_elem << endl;

		s = d;
		n--;
	}


	cin.get();
	cin.get();

	return 0;
}