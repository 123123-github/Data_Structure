#include "Stack.h"
//栈基本操作实现

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
	if (top - base >= stacksize)		//若栈满
	{
		ElemType newbase;										//申请新空间
		newbase = new ElemType[stacksize + STACKINCREMENT];

		for (int i = 0; i < stacksize; i++)						//复制元素
			newbase[i] = base[i];

		delete base;											//释放久空间

		base = newbase;											//指向新空间
		top = base + stacksize;
		
		stacksize += STACKINCREMENT;							//栈长增加
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
