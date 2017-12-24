#pragma once
//ADT Queue
//C++ 类

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
	~Queue();

public:
	bool Empty();
	bool Pop(ElemType &e);
	bool Push(ElemType e);
};

template<typename ElemType>
inline bool MakeQNode(QNode<ElemType>*& p, ElemType e)
{
	p = new QNode<ElemType>;
	if (!p)
		return false;

	p->data = e;
	p->next = nullptr;
}
