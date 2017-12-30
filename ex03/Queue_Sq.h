//SqQueue ѭ������ʵ��
//(C++�ṹ��)

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

//���ж���
#define QUEUE_INIT_SIZE 100
#define QUEUEINCREMENT 10
struct SqQueue
{
	int *base;
	int *front;
	int *rear;
	int length;
	int queuesize;
};

//ʮ����������ʵ��

//����һ���ն���Q
Status InitQueue_Sq(SqQueue &Q)
{
	Q.base = new int[QUEUE_INIT_SIZE];
	if (!Q.base)
		return OVERFLOW;

	Q.front = Q.base;
	Q.rear = Q.front;
	Q.length = 0;
	Q.queuesize = QUEUE_INIT_SIZE;

	return OK;
}

//���ٶ���Q
Status DestroyQueue_Sq(SqQueue &Q)
{
	//������л���ַ�����ڣ�����Ϊ���� Q �Ѿ�����
	if (!Q.base)
		return OK;

	delete Q.base;

	Q.front = NULL;
	Q.rear = NULL;
	Q.length = -1;
	Q.queuesize = -1;
	Q.base = NULL;

	return OK;
}

//��Q��Ϊ�ն���
Status ClearQueue_Sq(SqQueue &Q)
{
	Q.front = Q.rear;
	Q.length = 0;

	return OK;
}

//������Ϊ�գ��򷵻�TRUE�����򷵻�FALSE
Status QueueEmpty_Sq(SqQueue Q)
{
	if (Q.length == 0)
		return TRUE;
	else
		return FALSE;
}

//���ض��г���
int QueueLength_Sq(SqQueue Q)
{
	return Q.length;
}

//�����в�Ϊ�գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�FALSE
Status GetHead_Sq(SqQueue Q, int &e)
{
	if (Q.length == 0)
	{
		return ERROR;
	}
	else
	{
		e = *Q.front;
		return OK;
	}
}

//����Ԫ��eΪQ���µĶ�βԪ��
Status EnQueue_Sq(SqQueue &Q, int e)
{
	//�ж϶����Ƿ������������������µĿռ�
	if (Q.length == Q.queuesize)
	{
		//����ռ�
		int *newbase;
		newbase = new int[Q.length + QUEUEINCREMENT];
		if (!newbase)
			return OVERFLOW;
		//����Ԫ��
		int i;
		for (i = 0; i < Q.queuesize + Q.base - Q.front; i++)
		{
			newbase[i] = Q.front[i];
		}
		for (int j = 0; j < Q.rear - Q.base; j++)
		{
			newbase[i + j] = Q.base[j];
		}
		//����ԭ�ռ�
		delete Q.base;
		//�޸�ָ��,�޸�Ԫ��ֵ
		Q.base = newbase;
		Q.front = Q.base;
		Q.rear = Q.front + Q.length;
		Q.queuesize += QUEUEINCREMENT;
	}
	//����Ԫ��
	*Q.rear = e;
	//ѭ�����ö��пռ�
	if (Q.rear - Q.base + 1 == Q.queuesize)
	{
		Q.rear = Q.base;
	}
	else
	{
		Q.rear++;
	}
	//�޸Ķ���Ԫ��ֵ
	Q.length++;

	return OK;
}

//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ�����e������ֵ��������OK�����򷵻�FALSE
Status DeQueue_Sq(SqQueue &Q, int &e)
{
	if (Q.length == 0)
	{
		return FALSE;
	}
	//ȡԪ�أ���ɾ��
	e = *Q.front;
	//ѭ�����ö��пռ�
	if (Q.front - Q.base + 1 == Q.queuesize)
	{
		Q.front = Q.base;
	}
	else
	{
		Q.front++;
	}
	//�޸Ķ���Ԫ�ز���
	Q.length--;

	return OK;
}

//�����������
Status QueueTraverse_Sq(SqQueue Q)
{
	//����Ϊ��ʱ��
	if (Q.length == 0)
	{
		cout << "����Ϊ��" << endl;
		return OK;
	}
	//���в�Ϊ��ʱ
	if (Q.front - Q.rear >= 0)
	{
		for (int i = 0; i < Q.queuesize + Q.base - Q.front; i++)
		{
			cout << Q.front[i] << '\t';
		}
		for (int i = 0; i < Q.rear - Q.base; i++)
		{
			cout << Q.base[i] << '\t';
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < Q.length; i++)
		{
			cout << Q.front[i] << '\t';
		}
		cout << endl;
	}
	return OK;
}

//��ʼ������������
Status CreatQueue_Sq(SqQueue &Q, int n)
{
	int e;
	//��ʼ������
	InitQueue_Sq(Q);
	//����Ԫ�أ�Ȼ��������
	for (int i = 0; i < n; i++)
	{
		cin >> e;
		EnQueue_Sq(Q, e);
	}

	return OK;
}