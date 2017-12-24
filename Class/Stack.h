#pragma once

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
	~Stack();

public:
	bool Empty();
	ElemType Pop();
	bool Push(ElemType e);
	bool GetTop(ElemType &e);
};