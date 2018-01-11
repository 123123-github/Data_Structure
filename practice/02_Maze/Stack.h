#pragma once
#include <iostream>

//--------------- 栈定义 ---------------

#define STACK_INIT_SIZE 100 //栈存储空间 初始分配量
#define STACKINCREMENT 10   //栈存储空间 分配增量

//--------------- 栈类 -----------------

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


//--------------- 栈基本操作实现 -----------------

template<class ElemType>
Stack<ElemType>::Stack(int size)						//构造
{
	base = new ElemType[size];
	top = base;
	stacksize = size;
}

template<class ElemType>
inline Stack<ElemType>::Stack(const Stack & S)			//拷贝构造函数
{
	stacksize = S.stacksize;
	base = new ElemType[stacksize];

	top = base + (S.top - S.base);
	
	for (ElemType *p = base, *q = S.base; p != top; p++, q++)
		*p = *q;
}

template<class ElemType>
Stack<ElemType>::~Stack()								//析构
{
	delete base;

	base = nullptr;
	top = base;
	stacksize = -1;
}

//-------- 基本函数操作 --------

template<class ElemType>
bool Stack<ElemType>::Empty()							//判断是否空
{
	if (base == top)
		return true;
	else
		return false;
}

template<class ElemType>
ElemType Stack<ElemType>::Pop()							//弹出
{
	ElemType e;

	/*
	if (top == base)									// 在外部判断是否为空
		return NULL;
	*/
	
	top--;
	e = *top;
	return e;
	
}

template<class ElemType>
bool Stack<ElemType>::Push(ElemType e)					//入栈
{
	if (top - base >= stacksize)		//若栈满
	{
		ElemType* newbase;										//申请新空间
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
bool Stack<ElemType>::GetTop(ElemType &e)				//取顶部元素
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
