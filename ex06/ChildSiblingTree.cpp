#include <iostream>
#include "ChildSiblingTree.h"
using namespace std;

//------------------------ CSTree 定义------------------------

Status MakeCSNode(CSNode *& T, ElemType e)
{
	T = new CSNode;
	if (!T)
		return ERROR;

	T->data = e;
	T->first_child = NULL;
	T->next_sibling = NULL;

	return OK;
}


//-------树用队列定义-------

Status MakeQueueNode_t(QNode_t* &s, BiTreeNode *t)	//分配结点
{
	s = new QNode_t;
	if (!s)
		return ERROR;

	s->next = NULL;
	s->elem = t;

	return OK;
}

Status InitQueue_t(Queue_t &Q)		//初始化队列
{
	Q.front = new QNode_t;
	if (!Q.front)
		return ERROR;

	Q.front->next = NULL;
	Q.rear = Q.front;

	return OK;
}

Status DestroyQueue_t(Queue_t &Q)	//销毁队列
{
	Queueptr_t p, q;
	p = q = Q.front;

	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	Q.front = NULL;
	Q.rear = NULL;

	return OK;
}

bool QueueEmpty_t(Queue_t Q)		//队是否为空
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

Status EnQueue_t(Queue_t &Q, BiTreeNode* t)			//入队
{
	QNode_t *s;
	MakeQueueNode_t(s, t);

	Q.rear->next = s;
	Q.rear = s;

	return OK;
}

Status DeQueue_t(Queue_t &Q, BiTreeNode* &t)				//出队
{
	if (Q.front == Q.rear)
		return	ERROR;

	Queueptr_t p;
	p = Q.front->next;
	t = p->elem;

	if (p == Q.rear)	//避免队尾指针被删除
		Q.rear = Q.front;

	Q.front->next = p->next;
	delete p;
	p = NULL;

	return OK;
}


//------------------------ 基本操作 -----------------------

Status InitCSTree(CSTree & T)
{
	T = NULL;

	return OK;
}

Status DestroyCSTree(CSTree & T)		//递归销毁树，与二叉树销毁方式相同
{
	if (!T)
		return OK;

	DestroyCSTree(T->first_child);
	DestroyCSTree(T->next_sibling);

	return OK;
}

CSNode * Search(CSTree T, ElemType e)
{
	if (!T)
		return NULL;

	if (T->data == e)
		return T;

	CSNode* t;
	if (t = Search(T->first_child, e))
		return t;
	if (t = Search(T->next_sibling, e))
		return t;

	return NULL;
}

Status CreatCSTree(CSTree & T)
{
	//--------- 输入相关信息 --------
	
	int n;
	ElemType *value, *parent;

	cout << "请输入树的节点数\n";
	cin >> n;

	if (n <= 0)						//为空树时提前返回
	{
		T = NULL;
		return OK;
	}

	value = new ElemType[n];		//层序输入数的结点建造树
	if (!value)
		return ERROR;
	parent = new ElemType[n];		//并需要指明每个结点的双亲
	if (!parent)
		return OK;

	cout << "请按照层序输入树的结点\n";
	for (int i = 0; i < n; i++)
	{
		cin >> value[i];
	}
	cout << "请输入层序中对应结点的双亲 根以 # 表示\n";
	for (int i = 0; i < n; i++)
	{
		cin >> parent[i];
	}

	//---------- 建树 ----------
	/*
	---先建好根
	---再建立 n - 1 个结点
	--当与前一个的 parent 不同，找到双亲，当前节点作为其 first_child 
	--相同，作为其 next_sibling
	*/
	
	CSNode *t;			// t 指向当前插入结点的前一个结点
	int i=1;			// i 始终标识数组中当前插入结点的位置信息


	MakeCSNode(T, value[0]);
	t = T;
	
	while (i < n)			//此处 i 同时表示了已完成的结点数		/*错写为for时会丢失数据，因为for中不该再有i++*/
	{
		while (i < n && (parent[i] == parent[i - 1]))		//与前一个结点是兄弟
		{
			MakeCSNode(t->next_sibling, value[i]);
			
			t = t->next_sibling;
			i++;
		}

		while (i < n && (parent[i] != parent[i - 1]))		//是前一个结点的孩子
		{
			t = Search(T, parent[i]);				//找到当前要分配结点的双亲
			MakeCSNode(t->first_child, value[i]);

			t = t->first_child;
			i++;
		}
	}

	delete[] value;
	delete[] parent;

	return OK;
}

Status PrintPriLevel(CSTree & T)
{
	CSNode* p = T;
	Queue_t Q_branch, Q_print;			//表示分支的队列 和 用于输出整个层次的队列
	
	InitQueue_t(Q_branch);				//存储每个分支的起始地址
	InitQueue_t(Q_print);

	EnQueue_t(Q_branch, p);				
	while (!QueueEmpty_t(Q_branch))
	{
		while (!QueueEmpty_t(Q_branch))			//针对每个分支
		{
			DeQueue_t(Q_branch, p);
			
			while (p)							//分支相连的元素全部入队(沿着 sibling 的链)
			{
				EnQueue_t(Q_print, p);
				p = p->next_sibling;
			}
		}

		while (!QueueEmpty_t(Q_print))
		{
			DeQueue_t(Q_print, p);

			if (p->first_child)					//带有分支的元素，输出前将其 first_child 入队
			{
				EnQueue_t(Q_branch, p->first_child);
			}

			cout << p->data << '\t';			// print 队列中的每一个元素都输出
		}
	}

	DestroyQueue_t(Q_branch);
	DestroyQueue_t(Q_print);

	return OK;
}

Status PreOrderTraverse(CSTree T)
{
	if (!T)
		return OK;

	cout << T->data << '\t';

	PreOrderTraverse(T->first_child);
	PreOrderTraverse(T->next_sibling);

	return OK;
}