#pragma once
#include <iostream>

//ADT Queue
//C++ 类 队列实现

//------------------ 队列结点定义 ------------------

template<typename ElemType>
struct QNode								//结点定义
{
	ElemType data;
	QNode* next;
};

template<typename ElemType>
bool MakeQNode(QNode<ElemType>* &p, ElemType e);			//为 e 分配结点空间

//-------------------- 队列定义 --------------------

template<typename ElemType>
class Queue
{
	typedef QNode<ElemType>* Queueptr;		//确定类型后才能起别名

private:
	Queueptr front;
	Queueptr rear;

public:
	Queue();
	Queue(const Queue& Q);
	~Queue();

public:
	bool Empty();
	ElemType Pop();
	bool Push(ElemType e);
};

template<typename ElemType>
inline bool MakeQNode(QNode<ElemType>*& p, ElemType e)		//分配队列结点
{
	p = new QNode<ElemType>;
	if (!p)
		return false;

	p->data = e;
	p->next = nullptr;

	return true;
}


//-------------------- 队列基本操作实现 --------------------

template<typename ElemType>
Queue<ElemType>::Queue()							//构造
{
	front = new QNode<ElemType>;

	front->next = nullptr;
	rear = front;
}

template<typename ElemType>
inline Queue<ElemType>::Queue(const Queue & Q)		//拷贝构造
{
	Queueptr p = Q.front->next, s;

	front = new QNode<ElemType>;
	front->next = NULL;
	rear = front;
	
	while (p)
	{
		MakeQNode(s, p->data);			//复制数据
		rear->next = s;
		rear = s;

		p = p->next;
	}
}

template<typename ElemType>
Queue<ElemType>::~Queue()							//析构
{
	Queueptr p, q;
	p = q = front;

	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	front = nullptr;
	rear = nullptr;
}


//-------- 基本函数操作 --------

template<typename ElemType>
bool Queue<ElemType>::Empty()						//判断是否空
{
	if (front == rear)
		return true;
	else
		return false;
}

template<typename ElemType>
ElemType Queue<ElemType>::Pop()				//出队
{
	if (front == rear)		//队为空则不能出队
		return NULL;

	Queueptr p;
	ElemType e;
	p = front->next;
	e = p->data;

	if (p == rear)			//如果 rear 被删，则将其指向 front
		rear = front;

	front->next = p->next;
	delete p;
	p = nullptr;

	return e;
}

template<typename ElemType>
bool Queue<ElemType>::Push(ElemType e)				//入队
{
	Queueptr s;
	MakeQNode(s, e);

	rear->next = s;
	rear = s;

	return true;
}
