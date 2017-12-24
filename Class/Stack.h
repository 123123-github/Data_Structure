#pragma once

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
	~Stack();

public:
	bool Empty();
	ElemType Pop();
	bool Push(ElemType e);
	bool GetTop(ElemType &e);
};