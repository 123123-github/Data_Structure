#pragma once
#include <iostream>

//ADT Queue
//C++ �� ����ʵ��

//------------------ ���н�㶨�� ------------------

template<typename ElemType>
struct QNode								//��㶨��
{
	ElemType data;
	QNode* next;
};

template<typename ElemType>
bool MakeQNode(QNode<ElemType>* &p, ElemType e);			//Ϊ e ������ռ�

//-------------------- ���ж��� --------------------

template<typename ElemType>
class Queue
{
	typedef QNode<ElemType>* Queueptr;		//ȷ�����ͺ���������

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
inline bool MakeQNode(QNode<ElemType>*& p, ElemType e)		//������н��
{
	p = new QNode<ElemType>;
	if (!p)
		return false;

	p->data = e;
	p->next = nullptr;

	return true;
}


//-------------------- ���л�������ʵ�� --------------------

template<typename ElemType>
Queue<ElemType>::Queue()							//����
{
	front = new QNode<ElemType>;

	front->next = nullptr;
	rear = front;
}

template<typename ElemType>
inline Queue<ElemType>::Queue(const Queue & Q)		//��������
{
	Queueptr p = Q.front->next, s;

	front = new QNode<ElemType>;
	front->next = NULL;
	rear = front;
	
	while (p)
	{
		MakeQNode(s, p->data);			//��������
		rear->next = s;
		rear = s;

		p = p->next;
	}
}

template<typename ElemType>
Queue<ElemType>::~Queue()							//����
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


//-------- ������������ --------

template<typename ElemType>
bool Queue<ElemType>::Empty()						//�ж��Ƿ��
{
	if (front == rear)
		return true;
	else
		return false;
}

template<typename ElemType>
ElemType Queue<ElemType>::Pop()				//����
{
	if (front == rear)		//��Ϊ�����ܳ���
		return NULL;

	Queueptr p;
	ElemType e;
	p = front->next;
	e = p->data;

	if (p == rear)			//��� rear ��ɾ������ָ�� front
		rear = front;

	front->next = p->next;
	delete p;
	p = nullptr;

	return e;
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
