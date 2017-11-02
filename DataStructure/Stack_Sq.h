// ADT Stack 基本操作
// 顺序实现 (C++结构体)

#include <iostream>
using namespace std;

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//Status 为函数类型，值为函数结果状态代码
typedef int Status;

//栈定义
#define STACK_INIT_SIZE 100 //栈存储空间 初始分配量
#define STACKINCREMENT 10   //栈存储空间 分配增量	 
struct SqStack
{
	int *top;
	int *base;
	int stacksize;
};

//十个 基本函数实现：

//构造(初始化)空栈
Status InitStack(SqStack &S)
{
	S.base = new int[STACK_INIT_SIZE];
	if (!S.base)
		exit(OVERFLOW);

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;

	return OK;
}
//销毁栈S
Status DestroyStack(SqStack &S)
{
	if (!S.base)
		return ERROR;

	delete S.base[];
	S.top = NULL;
	S.stacksize = -1;

	return OK;
}
//将栈置为空栈
Status ClearStack(SqStack &S)
{
	if (!S.base)
		return ERROR;

	S.top = S.base;

	return OK;
}
//栈为空返回TRUE，否则返回FALSE
Status StackEmpty(SqStack S)
{
	if (!S.base)
		return ERROR;

	if (S.top - S.base == 0)
		return TRUE;
	else
		return FALSE;
}
//返回栈的长度
int StackLength(SqStack S)
{
	if (!S.base)
		return ERROR;

	return S.top - S.base;
}
//若栈不空，用e返回S的栈顶元素，并返回OK；否则返回FALSE
Status GetTop(SqStack S,int &e)
{
	if (S.top - S.base == 0)
		return FALSE;

	e = *(S.top - 1);

	return OK;
}
//插入e为新的栈顶元素
Status Push(SqStack &S, int e)
{
	if (S.top - S.base == S.stacksize)
	{
		int *newbase;
		newbase = new int[S.stacksize + STACKINCREMENT];
		if (!newbase)
			exit(OVERFLOW);

		for (int i = 0;i < S.stacksize;i++)
			newbase[i] = S.base[i];

		S.base = newbase;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}

	*S.top = e;
	S.top++;

	return OK;
}
//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回FALSE
Status Pop(SqStack &S, int &e)
{
	if (S.top - S.base == 0)
		return ERROR;

	e = *(S.top - 1);
	S.top--;

	return OK;
}
//遍历栈,从栈底到栈顶
Status StackTraverse(SqStack S)
{
	for (int i = 0; i < S.top - S.base; i++)
		cout << S.base[i] << '\t';
	cout << endl;

	return OK;
}
//创建栈
Status CreatStack(SqStack &S, int n)
{
	int e;
	InitStack(S);

	for (int i = 0; i < n; i++)
	{
		cin >> e;
		Push(S, e);
	}

	return OK;
}