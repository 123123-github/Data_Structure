#pragma once

#include <fstream>
using namespace std;
// ADT BinaryTree 二叉链表结构实现
// C++

//-----------------------函数结果状态代码--------------------

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;			//Status 为函数类型，值为函数结果状态代码
typedef int ElemType;		//ElemType 为二叉树结点存储数据类型


//------------------------ BiTree 定义------------------------

#define LEFT 0
#define RIGHT 1

struct BiTreeNode			//二叉树结点
{
	ElemType data;
	BiTreeNode *left;
	BiTreeNode *right;
};

typedef BiTreeNode *BiTree;	//结点指针

Status MakeBiTNode(BiTreeNode* &T, ElemType e);


//------------------------基本操作 20个-----------------------

Status InitBiTree(BiTree &T);

Status DestroyBiTree(BiTree &T);		//递归销毁树，前序

Status ClearBiTree(BiTree &T);			//前序清空树

Status BiTreeEmpty(BiTree &T);

Status BiTreeDepth(BiTree &T);


//---------二叉树遍历---------

Status PreOrderTraverse(BiTree T);			//前序遍历输出

Status InOrderTraverse(BiTree T);			//中序遍历输出

Status PostOrderTraverse(BiTree T);			//后序遍历输出

//-------------层次遍历---------------

//-------树用队列定义-------

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

//-----树用队列定义结束-----

Status LevelOrderTraverse(BiTree T);		//层次遍历二叉树

//-------------层次遍历结束---------------

//------------------------基本操作 20个结束-----------------------


//------------非递归遍历------------

//-----树用栈定义-----
#define STACK_INIT_SIZE 100 //栈存储空间 初始分配量
#define STACKINCREMENT 10   //栈存储空间 分配增量

struct stackelem
{
	BiTreeNode* t;
	bool flag;
};

struct Stack_t
{
	stackelem* base;
	stackelem* top;
	int stacksize;
};

Status InitStack_t(Stack_t &S);

Status DestroyStack_t(Stack_t &S);

bool StackEmpty_t(Stack_t S);

Status GetTop(Stack_t S, BiTreeNode* &t, bool &flag);

Status Pop_t(Stack_t &S, BiTreeNode* &t);

Status Push_t(Stack_t &S, BiTreeNode* t);

Status ChangeTopFlag(Stack_t &S);

//-----树用栈定义结束-----

Status PreOrderTraverse_1(BiTree T);	//前序非递归

Status InOrderTraverse_1(BiTree T);		//中序非递归

Status PostOrderTraverse_1(BiTree T);	//后序非递归


//----------------------------其它函数-----------------------------

bool IsCompleteBiTree(BiTree T);		//判断是否是完全二叉树

Status FindAndDelete(BiTree &T,ElemType x);		//递归	在树 T 中删除每个以值 x 为根的子树

Status FindAndDelete_1(BiTree &T, ElemType x);	//非递归	在树 T 中删除每个以值 x 为根的子树


bool IsBST(BiTree T);

int Depth(BiTree T);

int Width(BiTree T);

int NodeNum(BiTree T);

void FileCreat(ifstream & in, BiTree & T, const char * filename);

