// ADT Queue 基本操作
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

//链式队列定义，单链队列
struct QNode
{
	int data;
	int *next;
};

struct LinkQueue
{
	QNode *front;
	QNode *rear;
};

typedef QNode *QueuePtr;

//创建值为e的队列结点
Status MakeQNode(QueuePtr s, int e)
{
	s = new QNode;
	if (!s)
		exit(OVERFLOW);

	s->data = e;
	s->next = NULL;

	return OK;
}
//构造一个空队列Q
Status InitQueue(LinkQueue &Q)
{
	Q.front = new QNode;
	if (!Q.front)
		exit(OVERFLOW);

	Q.rear = Q.front;

	return OK;
}
//销毁队列Q，Q不存在
Status DestroyQueue(LinkQueue &Q)
{
	QueuePtr p = Q.front;
	QueuePtr q = p->next;

	while (q)
	{
		delete p;
		p = q;
		q = q->next;
	}
	delete p;

	Q.front = NULL;
	Q.rear = NULL;

	return OK;
}
//将Q清为空队列
Status ClearQueue(LinkQueue &Q)
{
	QueuePtr p, q;
	p = Q.front->next;

	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	Q.rear = Q.front;

	return OK;
}
//若队列为空，则返回TRUE，否则返回FALSE
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}
//返回队列长度
int QueueLength(LinkQueue Q)
{
	QueuePtr p = Q.front;
	int i = 0;

	while (p != Q.rear)
	{
		p = p->next;
		i++;
	}

	return i;
}
//若队列不为空，则用e返回Q的队头元素，并返回OK；否则返回FALSE
Status GetHead(LinkQueue Q, int &e)
{
	if (Q.front == Q.rear)
		return FALSE;

	QueuePtr head;
	head = Q.front->next;

	e = head->data;

	return OK;
}
//插入元素e为Q的新的队尾元素
Status EnQueue(LinkQueue &Q, int e)
{
	QueuePtr s;

	MakeQNode(s, e);

	Q.rear->next = s;
	Q.rear = s;

	return OK;
}
//若队列不空，则删除Q的队头元素，并用e返回其值，并返回OK，否则返回FALSE
Status DeQueue(LinkQueue &Q, int &e)
{
	if (Q.front == Q.rear)
		return FALSE;

	QueuePtr p;
	p = Q.front->next;

	Q.front->next = p->next;
	e = p->data;
	delete p;

	if (!Q.rear)
		Q.rear = Q.front;

	return OK;
}
//遍历输出队列
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p = Q.front->next;

	while (p)
	{
		cout << p->data << '\t';
		p = p->next;
	}
	cout >> endl;

	return OK;
}