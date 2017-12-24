#pragma once
//ADT Queue
//C++ ��

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
