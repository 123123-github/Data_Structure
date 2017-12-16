#pragma once
// ADT Child-Sibling Tree

//-----------------------函数结果状态代码--------------------

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;			//Status 为函数类型，值为函数结果状态代码

typedef char ElemType;		//ElemType 为树结点存储数据类型


//------------------------ CSTree 定义------------------------

struct CSNode				//树结点
{
	ElemType data;
	CSNode *first_child;
	CSNode *next_sibling;
};

typedef CSNode *CSTree;	//结点指针

Status MakeCSNode(CSNode* &T, ElemType e);


//-------树用队列定义-------

typedef CSNode BiTreeNode;

struct QNode_t			//存放树结点的队列
{
	BiTreeNode *elem;
	QNode_t *next;
};
typedef QNode_t *Queueptr_t;

Status MakeQueueNode_t(QNode_t* &s, BiTreeNode *t);	//分配结点

struct Queue_t			//队列定义
{
	Queueptr_t front;
	Queueptr_t rear;
};

Status InitQueue_t(Queue_t &Q);		//初始化队列

Status DestroyQueue_t(Queue_t &Q);	//销毁队列

bool QueueEmpty_t(Queue_t Q);		//队是否为空

Status EnQueue_t(Queue_t &Q, BiTreeNode* t);			//入队

Status DeQueue_t(Queue_t &Q, BiTreeNode* &t);			//出队


//------------------------ 基本操作 -----------------------

Status InitCSTree(CSTree &T);			//初始化树

Status DestroyCSTree(CSTree &T);		//销毁树

CSNode* Search(CSTree T, ElemType e);	//寻找 e 的位置

Status CreatCSTree(CSTree &T);			//创建树

Status PrintPriLevel(CSTree &T);		//按照原结构层序输出

Status PreOrderTraverse(CSTree T);		//现在结构的前序输出