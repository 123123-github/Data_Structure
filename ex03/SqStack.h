// ADT Stack ��������
// ˳��ʵ�� (C++�ṹ��)

#include <iostream>
using namespace std;

//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//Status Ϊ�������ͣ�ֵΪ�������״̬����
typedef int Status;

//ջ����
#define STACK_INIT_SIZE 100 //ջ�洢�ռ� ��ʼ������
#define STACKINCREMENT 10   //ջ�洢�ռ� ��������	 
struct SqStack
{
	int *top;
	int *base;
	int stacksize;
};

//ʮ�� ��������ʵ�֣�

//����(��ʼ��)��ջ
Status InitStack(SqStack &S)
{
	S.base = new int[STACK_INIT_SIZE];
	if (!S.base)
		exit(OVERFLOW);

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;

	return OK;
}
//����ջS
Status DestroyStack(SqStack &S)
{
	if (!S.base)
		return ERROR;

	delete S.base[];
	S.top = NULL;
	S.stacksize = -1;

	return OK;
}
//��ջ��Ϊ��ջ
Status ClearStack(SqStack &S)
{
	if (!S.base)
		return ERROR;

	S.top = S.base;

	return OK;
}
//ջΪ�շ���TRUE�����򷵻�FALSE
Status StackEmpty(SqStack S)
{
	if (!S.base)
		return ERROR;

	if (S.top - S.base == 0)
		return TRUE;
	else
		return FALSE;
}
//����ջ�ĳ���
int StackLength(SqStack S)
{
	if (!S.base)
		return ERROR;

	return S.top - S.base;
}
//��ջ���գ���e����S��ջ��Ԫ�أ�������OK�����򷵻�FALSE
Status GetTop(SqStack S,int &e)
{
	if (S.top - S.base == 0)
		return FALSE;

	e = *(S.top - 1);

	return OK;
}
//����eΪ�µ�ջ��Ԫ��
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
//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�FALSE
Status Pop(SqStack &S, int &e)
{
	if (S.top - S.base == 0)
		return ERROR;

	e = *(S.top - 1);
	S.top--;

	return OK;
}
//����ջ,��ջ�׵�ջ��
Status StackTraverse(SqStack S)
{
	for (int i = 0; i < S.top - S.base; i++)
		cout << S.base[i] << '\t';
	cout << endl;

	return OK;
}
//����ջ
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