#pragma once
// ADT Child-Sibling Tree

//-----------------------�������״̬����--------------------

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;			//Status Ϊ�������ͣ�ֵΪ�������״̬����

typedef char ElemType;		//ElemType Ϊ�����洢��������


//------------------------ CSTree ����------------------------

struct CSNode				//�����
{
	ElemType data;
	CSNode *first_child;
	CSNode *next_sibling;
};

typedef CSNode *CSTree;	//���ָ��

Status MakeCSNode(CSNode* &T, ElemType e);


//-------���ö��ж���-------

typedef CSNode BiTreeNode;

struct QNode_t			//��������Ķ���
{
	BiTreeNode *elem;
	QNode_t *next;
};
typedef QNode_t *Queueptr_t;

Status MakeQueueNode_t(QNode_t* &s, BiTreeNode *t);	//������

struct Queue_t			//���ж���
{
	Queueptr_t front;
	Queueptr_t rear;
};

Status InitQueue_t(Queue_t &Q);		//��ʼ������

Status DestroyQueue_t(Queue_t &Q);	//���ٶ���

bool QueueEmpty_t(Queue_t Q);		//���Ƿ�Ϊ��

Status EnQueue_t(Queue_t &Q, BiTreeNode* t);			//���

Status DeQueue_t(Queue_t &Q, BiTreeNode* &t);			//����


//------------------------ �������� -----------------------

Status InitCSTree(CSTree &T);			//��ʼ����

Status DestroyCSTree(CSTree &T);		//������

CSNode* Search(CSTree T, ElemType e);	//Ѱ�� e ��λ��

Status CreatCSTree(CSTree &T);			//������

Status PrintPriLevel(CSTree &T);		//����ԭ�ṹ�������

Status PreOrderTraverse(CSTree T);		//���ڽṹ��ǰ�����