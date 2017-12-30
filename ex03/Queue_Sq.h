//SqQueue 循环队列实现
//(C++结构体)

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

//队列定义
#define QUEUE_INIT_SIZE 100
#define QUEUEINCREMENT 10
struct SqQueue
{
	int *base;
	int *front;
	int *rear;
	int length;
	int queuesize;
};

//十个基本函数实现

//构造一个空队列Q
Status InitQueue_Sq(SqQueue &Q)
{
	Q.base = new int[QUEUE_INIT_SIZE];
	if (!Q.base)
		return OVERFLOW;

	Q.front = Q.base;
	Q.rear = Q.front;
	Q.length = 0;
	Q.queuesize = QUEUE_INIT_SIZE;

	return OK;
}

//销毁队列Q
Status DestroyQueue_Sq(SqQueue &Q)
{
	//如果队列基地址不存在，可认为队列 Q 已经销毁
	if (!Q.base)
		return OK;

	delete Q.base;

	Q.front = NULL;
	Q.rear = NULL;
	Q.length = -1;
	Q.queuesize = -1;
	Q.base = NULL;

	return OK;
}

//将Q清为空队列
Status ClearQueue_Sq(SqQueue &Q)
{
	Q.front = Q.rear;
	Q.length = 0;

	return OK;
}

//若队列为空，则返回TRUE，否则返回FALSE
Status QueueEmpty_Sq(SqQueue Q)
{
	if (Q.length == 0)
		return TRUE;
	else
		return FALSE;
}

//返回队列长度
int QueueLength_Sq(SqQueue Q)
{
	return Q.length;
}

//若队列不为空，则用e返回Q的队头元素，并返回OK；否则返回FALSE
Status GetHead_Sq(SqQueue Q, int &e)
{
	if (Q.length == 0)
	{
		return ERROR;
	}
	else
	{
		e = *Q.front;
		return OK;
	}
}

//插入元素e为Q的新的队尾元素
Status EnQueue_Sq(SqQueue &Q, int e)
{
	//判断队列是否已满，若满则申请新的空间
	if (Q.length == Q.queuesize)
	{
		//申请空间
		int *newbase;
		newbase = new int[Q.length + QUEUEINCREMENT];
		if (!newbase)
			return OVERFLOW;
		//复制元素
		int i;
		for (i = 0; i < Q.queuesize + Q.base - Q.front; i++)
		{
			newbase[i] = Q.front[i];
		}
		for (int j = 0; j < Q.rear - Q.base; j++)
		{
			newbase[i + j] = Q.base[j];
		}
		//销毁原空间
		delete Q.base;
		//修改指向,修改元素值
		Q.base = newbase;
		Q.front = Q.base;
		Q.rear = Q.front + Q.length;
		Q.queuesize += QUEUEINCREMENT;
	}
	//插入元素
	*Q.rear = e;
	//循环利用队列空间
	if (Q.rear - Q.base + 1 == Q.queuesize)
	{
		Q.rear = Q.base;
	}
	else
	{
		Q.rear++;
	}
	//修改队列元素值
	Q.length++;

	return OK;
}

//若队列不空，则删除Q的队头元素，并用e返回其值，并返回OK，否则返回FALSE
Status DeQueue_Sq(SqQueue &Q, int &e)
{
	if (Q.length == 0)
	{
		return FALSE;
	}
	//取元素，并删除
	e = *Q.front;
	//循环利用队列空间
	if (Q.front - Q.base + 1 == Q.queuesize)
	{
		Q.front = Q.base;
	}
	else
	{
		Q.front++;
	}
	//修改队列元素参数
	Q.length--;

	return OK;
}

//遍历输出队列
Status QueueTraverse_Sq(SqQueue Q)
{
	//队列为空时，
	if (Q.length == 0)
	{
		cout << "队列为空" << endl;
		return OK;
	}
	//队列不为空时
	if (Q.front - Q.rear >= 0)
	{
		for (int i = 0; i < Q.queuesize + Q.base - Q.front; i++)
		{
			cout << Q.front[i] << '\t';
		}
		for (int i = 0; i < Q.rear - Q.base; i++)
		{
			cout << Q.base[i] << '\t';
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < Q.length; i++)
		{
			cout << Q.front[i] << '\t';
		}
		cout << endl;
	}
	return OK;
}

//初始化并创建队列
Status CreatQueue_Sq(SqQueue &Q, int n)
{
	int e;
	//初始化队列
	InitQueue_Sq(Q);
	//输入元素，然后插入队列
	for (int i = 0; i < n; i++)
	{
		cin >> e;
		EnQueue_Sq(Q, e);
	}

	return OK;
}