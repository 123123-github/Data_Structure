#pragma once
#include <iostream>

//--------------- ջ���� ---------------

#define STACK_INIT_SIZE 100 //ջ�洢�ռ� ��ʼ������
#define STACKINCREMENT 10   //ջ�洢�ռ� ��������

//--------------- ջ�� -----------------

template <class ElemType>
class Stack
{
private:
	ElemType * base;
	ElemType* top;
	int stacksize;

public:
	Stack(int size = STACK_INIT_SIZE);
	Stack(const Stack& S);
	~Stack();

public:
	bool Empty();
	ElemType Pop();
	bool Push(ElemType e);
	bool GetTop(ElemType &e);
	void Clear();
};


//--------------- ջ��������ʵ�� -----------------

template<class ElemType>
Stack<ElemType>::Stack(int size)						//����
{
	base = new ElemType[size];
	top = base;
	stacksize = size;
}

template<class ElemType>
inline Stack<ElemType>::Stack(const Stack & S)			//�������캯��
{
	stacksize = S.stacksize;
	base = new ElemType[stacksize];

	top = base + (S.top - S.base);
	
	for (ElemType *p = base, *q = S.base; p != top; p++, q++)
		*p = *q;
}

template<class ElemType>
Stack<ElemType>::~Stack()								//����
{
	delete base;

	base = nullptr;
	top = base;
	stacksize = -1;
}

//-------- ������������ --------

template<class ElemType>
bool Stack<ElemType>::Empty()							//�ж��Ƿ��
{
	if (base == top)
		return true;
	else
		return false;
}

template<class ElemType>
ElemType Stack<ElemType>::Pop()							//����
{
	ElemType e;

	/*
	if (top == base)									// ���ⲿ�ж��Ƿ�Ϊ��
		return NULL;
	*/
	
	top--;
	e = *top;
	return e;
	
}

template<class ElemType>
bool Stack<ElemType>::Push(ElemType e)					//��ջ
{
	if (top - base >= stacksize)		//��ջ��
	{
		ElemType* newbase;										//�����¿ռ�
		newbase = new ElemType[stacksize + STACKINCREMENT];

		for (int i = 0; i < stacksize; i++)						//����Ԫ��
			newbase[i] = base[i];

		delete base;											//�ͷžÿռ�

		base = newbase;											//ָ���¿ռ�
		top = base + stacksize;

		stacksize += STACKINCREMENT;							//ջ������
	}

	*top = e;
	top++;

	return true;
}

template<class ElemType>
bool Stack<ElemType>::GetTop(ElemType &e)				//ȡ����Ԫ��
{
	if (top == base)
		return false;

	e = *(top - 1);
	return true;
}

template<class ElemType>
inline void Stack<ElemType>::Clear()
{
	top = base;
}
