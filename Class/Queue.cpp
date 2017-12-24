#include "Queue.h"
//ADT Queue
//��������

template<typename ElemType>
Queue<ElemType>::Queue()
{
	front = new QNode<ElemType>;

	front->next = nullptr;
	rear = front;
}

template<typename ElemType>
Queue<ElemType>::~Queue()
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


template<typename ElemType>
bool Queue<ElemType>::Empty()
{
	if (front == rear)
		return true;
	else
		return false;
}

template<typename ElemType>
bool Queue<ElemType>::Pop(ElemType &e)				//����
{
	if (front == rear)		//��Ϊ�����ܳ���
		return false;

	Queueptr p;
	p = front->next;

	if (p == rear)			//��� rear ��ɾ������ָ�� front
		rear = front;

	front->next = p->next;
	delete p;
	p = nullptr;

	return true;
}

template<typename ElemType>
bool Queue<ElemType>::Push(ElemType e)				//���
{
	Queueptr s;
	MakeQNode(s, e);

	rear->next = s;
	rear = s;

	return true;
}
