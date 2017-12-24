#include "Stack.h"
//ջ��������ʵ��

template<class ElemType>
Stack<ElemType>::Stack(int size)
{
	base = new ElemType[size];
	top = base;
	stacksize = size;
}

template<class ElemType>
Stack<ElemType>::~Stack()		
{
	delete base;
	
	base = nullptr;
	top = base;
	stacksize = -1;
}


template<class ElemType>
bool Stack<ElemType>::Empty()
{
	if (base == top)
		return true;
	else
		return false;
}

template<class ElemType>
ElemType Stack<ElemType>::Pop()
{
	ElemType e;

	if (top == base)
		return nullptr;
	else
	{
		top--;
		e = *top;
		return e;
	}
}

template<class ElemType>
bool Stack<ElemType>::Push(ElemType e)
{
	if (top - base >= stacksize)		//��ջ��
	{
		ElemType newbase;										//�����¿ռ�
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
bool Stack<ElemType>::GetTop(ElemType &e)
{
	if (top == base)
		return false;

	e = *(top - 1);
	return true;
}
