//BiTree.h 函数实现

#include <iostream>
#include "BiTree.h"
using namespace std;

//------------------------ BiTree 定义------------------------

Status MakeBiTNode(BiTreeNode* &T, ElemType e)		//为结点指针分配空间
{
	T = new BiTreeNode;
	if (!T)
		return ERROR;

	T->data = e;
	T->left = NULL;
	T->right = NULL;

	return OK;
}


//------------------------基本操作 20个-----------------------

Status InitBiTree(BiTree &T)
{
	T = NULL;
	return OK;
}

Status DestroyBiTree(BiTree &T)			//递归销毁树，前序
{
	if (!T)
		return OK;
	if ((!T->left) && (!T->right))	//可减少递归次数
	{
		delete T;
		T = NULL;
		return	OK;
	}

	DestroyBiTree(T->left);
	DestroyBiTree(T->right);

	delete T;
	T = NULL;
	return OK;
}

Status CreatBiTree(BiTree &T)			//前序创建树，树结点为空则输入‘#’
{
	ElemType e;
	cin >> e;

	if (e == '#')
		T = NULL;
	else
	{
		MakeBiTNode(T, e);
		CreatBiTree(T->left);
		CreatBiTree(T->right);
	}

	return OK;
}

Status ClearBiTree(BiTree &T)			//前序清空树
{
	if (!T)
		return OK;
	if ((!T->left) && (!T->right))
	{
		delete T;
		T = NULL;
		return OK;
	}
	ClearBiTree(T->left);
	ClearBiTree(T->right);
	delete T;
	T = NULL;

	return	OK;
}

Status BiTreeEmpty(BiTree &T)
{
	if (!T)
		return TRUE;
	else
		return FALSE;
}

ElemType Root(BiTree &T)		//返回树的根结点值,不存在时返回'\0'
{
	if (T)
		return T->data;
	else
		return '\0';
}

Status BiTreeDepth(BiTree &T)
{
	if (!T)
		return 0;
	/*此处判断有误，应取反
		else if ((T->left) && (T->right))
		return 1;
	*/
	else if ((!T->left) && (!T->right))
		return 1;
	else
	{
		int ld, rd, d;
		ld = BiTreeDepth(T->left);
		rd = BiTreeDepth(T->right);
		d = ld > rd ? ld : rd;

		return d + 1;
	}
}

ElemType Value(BiTree &T, BiTreeNode *e)					// e 指向 T 中的某个结点，函数返回 e 指向的值
{
	return e->data;
}

Status Assign(BiTree &T, BiTreeNode *e, ElemType value)		//将 e 指向的值改为 value
{
	e->data = value;

	return OK;
}

BiTreeNode* Parent(BiTree &T, BiTreeNode *e)			//返回 e 所指向结点的双亲的指针 
{
	if (!T)					//树不存在
		return NULL;
	if (e == T)
		return NULL;		// e 指向根,无双亲
	if (T->left == e || T->right == e)
		return T;			// 此时 T 为 e 的双亲

	//------以上情况都不成立时，在 T 的子树中寻找 e 的双亲-------
	BiTreeNode *p;

	if (T->left)		//左孩子存在时，在左子树中寻找,未能找到时返回值为 NULL 则不输出
	{
		p = Parent(T->left, e);
		if (p)
			return p;
	}
	if (T->right)		//在右子树中寻找
	{
		p = Parent(T->right, e);
		if (p)
			return p;
	}

	return NULL;		//都未能找到返回空值，若输入正确，则返回值不应当为空
}

BiTreeNode* LeftChild(BiTree &T, BiTreeNode *e)		//返回 e 的左孩子
{
	if (e)
		return e->left;
	else
		return NULL;
}

BiTreeNode* RightChild(BiTree &T, BiTreeNode *e)		//返回 e 的右孩子
{
	if (e)
		return e->right;
	else
		return NULL;
}

BiTreeNode* LeftSibling(BiTree &T, BiTreeNode *e)		//返回 e 的左兄弟
{
	BiTreeNode *p;
	p = Parent(T, e);	// p 指向 e 的双亲

	if (!p)				// p 不存在则说明 e 是根，无双亲，无兄弟
		return NULL;

	if (p->left == e)	// e 是左孩子，则无左兄弟
		return NULL;

	return p->left;		//返回 p 的左孩子，亦为 e 的左兄弟，包含了右兄弟不存在的情况
}

BiTreeNode* RightSibling(BiTree &T, BiTreeNode *e)		//返回 e 的右兄弟
{
	BiTreeNode *p;
	p = Parent(T, e);	// p 指向 e 的双亲

	if (!p)				// p 不存在则说明 e 是根，无双亲，无兄弟
		return NULL;

	if (p->right == e)	// e 是右孩子，则无右兄弟
		return NULL;

	return p->right;	//返回 p 的右孩子，亦为 e 的右兄弟，包含了右兄弟不存在的情况
}

Status InsertChild(BiTree &T, BiTreeNode *p, BiTreeNode *c, int LR)		// LR = 0 时对左进行操作，否则对右进行操作
{	// c 为叶子节点，插入作为 p 结点的 L/R 叶子，同时， p 的叶子成为 c 的叶子
	if (LR == LEFT)
	{
		c->left = p->left;
		p->left = c;
	}
	else
	{
		c->right = p->right;
		p->right = c;
	}

	return OK;
}

Status DeleteChild(BiTree &T, BiTreeNode *p, int LR)	//删除树 T 的 p 结点 的 L/R 孩子
{
	if (LR == LEFT)
	{
		DestroyBiTree(T->left);
		p->left = NULL;
	}
	else
	{
		DestroyBiTree(T->right);
		p->right = NULL;
	}

	return OK;
}

//---------二叉树遍历---------

Status PreOrderTraverse(BiTree T)			//前序遍历输出
{
	if (!T)
		return OK;
	else if ((!T->left) && (!T->right))
	{
		cout << T->data << '\t';
		return OK;
	}
	else
	{
		cout << T->data << '\t';
		PreOrderTraverse(T->left);
		PreOrderTraverse(T->right);
		return OK;
	}
}

Status InOrderTraverse(BiTree T)			//中序遍历输出
{
	if (!T)
		return OK;
	else if ((!T->left) && (!T->right))
	{
		cout << T->data << '\t';
		return OK;
	}
	else
	{
		InOrderTraverse(T->left);
		cout << T->data << '\t';
		InOrderTraverse(T->right);
		return OK;
	}
}

Status PostOrderTraverse(BiTree T)			//后序遍历输出
{
	if (!T)
		return OK;
	else if ((!T->left) && (!T->right))
	{
		cout << T->data << '\t';
		return OK;
	}
	else
	{
		PostOrderTraverse(T->left);
		PostOrderTraverse(T->right);
		cout << T->data << '\t';
		return OK;
	}
}

//-------------层次遍历---------------

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

//-----树用队列定义结束-----

Status LevelOrderTraverse(BiTree T)		//层次遍历二叉树
{
	if (!T)
		return OK;
						
	Queue_t Q;			//借助队列实现层次遍历	此时 T 存在
	InitQueue_t(Q);
	
	EnQueue_t(Q, T);

	BiTreeNode *t;
	while (!QueueEmpty_t(Q))	//每个结点出队后，将其子树入队
	{
		DeQueue_t(Q, t);
		if (t->left)
			EnQueue_t(Q, t->left);
		if (t->right)
			EnQueue_t(Q, t->right);

		cout << t->data << '\t';
	}
	cout << endl;

	DestroyQueue_t(Q);	//销毁队列

	return OK;
}

//-------------层次遍历结束---------------

//------------------------基本操作 20个结束-----------------------


//------------非递归遍历------------

//-----树用栈定义-----

Status InitStack_t(Stack_t &S)
{
	S.base = new stackelem[STACK_INIT_SIZE];
	if (!S.base)
		return ERROR;

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;

	return OK;
}

Status DestroyStack_t(Stack_t &S)
{
	delete[] S.base;
	S.top = S.base = NULL;
	S.stacksize = -1;

	return OK;
}

bool StackEmpty_t(Stack_t S)
{
	if (S.top == S.base)
		return true;
	else
		return false;
}

Status GetTop(Stack_t S, BiTreeNode* &t, bool &flag)
{
	if (S.top == S.base)
		return FALSE;

	stackelem s;
	s = *(S.top - 1);
	t = s.t;
	flag = s.flag;

	return OK;
}

Status Pop_t(Stack_t &S, BiTreeNode* &t)
{
	if (S.base == S.top)
		return ERROR;

	stackelem s;
	s = *(S.top - 1);
	t = s.t;

	S.top--;

	return OK;
}

Status Push_t(Stack_t &S, BiTreeNode* t)
{
	if (S.top - S.base >= S.stacksize)
	{
		stackelem *newbase;
		newbase = new stackelem[S.stacksize + STACKINCREMENT];
		if (!newbase)
			exit(OVERFLOW);

		for (int i = 0;i < S.stacksize;i++)
			newbase[i] = S.base[i];

		S.base = newbase;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}

	stackelem s;
	s = { t,true };
	*S.top = s;
	S.top++;

	return OK;
}

Status ChangeTopFlag(Stack_t &S)
{
	(*(S.top - 1)).flag = false;

	return OK;
}

//-----树用栈定义结束-----

Status PreOrderTraverse_1(BiTree T)		//前序非递归
{
	if (!T)
		return OK;

	Stack_t S;			// T 存在，开始利用栈遍历
	InitStack_t(S);
	
	Push_t(S, T);

	BiTreeNode* t;
	while (!StackEmpty_t(S))
	{
		Pop_t(S, t);
		if (t->right)
			Push_t(S, t->right);
		if (t->left)
			Push_t(S, t->left);

		cout << t->data << '\t';
	}
	cout << endl;

	DestroyStack_t(S);

	return OK;
}

Status InOrderTraverse_1(BiTree T)
{
	if (!T)
		return OK;

	Stack_t S;
	InitStack_t(S);
	
	Push_t(S, T);

	bool flag;
	BiTreeNode* t;
	while (!StackEmpty_t(S))
	{
		GetTop(S, t, flag);

		while (flag && t->left)
		{
			ChangeTopFlag(S);
			Push_t(S, t->left);
			t = t->left;
		}

		Pop_t(S, t);
		if (t->right)
			Push_t(S, t->right);

		cout << t->data << '\t';
	}
	cout << endl;

	DestroyStack_t(S);

	return OK;
}

Status PostOrderTraverse_1(BiTree T)
{
	if (!T)
		return OK;

	Stack_t S;
	InitStack_t(S);
	
	Push_t(S, T);

	bool flag;
	BiTreeNode* t;
	while (!StackEmpty_t(S))
	{
		GetTop(S, t, flag);

		while (flag && (t->left || t->right))	//①有左或右子树 且 子树未曾入栈
		{
			if (t->right || t->left)	//修改标志位，避免已入栈的再次入栈
				ChangeTopFlag(S);

			if (t->right)					//②按顺序 右、左 子树入栈（没有的不入栈）
				Push_t(S, t->right);
			if (t->left)
				Push_t(S, t->left);

			if (t->left)					//③有左子树则沿着左子树走，否则沿着右子树走
				t = t->left;
			else
				t = t->right;
		}

		Pop_t(S, t);

		cout << t->data << '\t';
	}
	cout << endl;

	DestroyStack_t(S);

	return OK;
}


//----------------------------其它函数-----------------------------

bool IsCompleteBiTree(BiTree T)		//若是完全二叉树：层序遍历结点过程中，有右孩子必有左孩子；若只有左孩子，则其后的结点没有孩子；
{
	if (!T)					//❗在 T 存在时才向下执行，简化判断过程及函数调用❗
		return true;

	Queue_t Q;
	InitQueue_t(Q);

	EnQueue_t(Q, T);

	bool flag = true;					//flag为标志，为false时，结点存在孩子则不是完全二叉树
	BiTreeNode* t;
	while (!QueueEmpty_t(Q))
	{
		DeQueue_t(Q, t);
		
		//-------以层序遍历为基础进行判断-----
		if (flag)
		{
			if (t->right && (!t->left))		//层序遍历结点过程中，有右孩子必有左孩子；否则不是完全二叉树
			{
				DestroyQueue_t(Q);
				return false;
			}
			if (t->left && (!t->right))
			{
				flag = false;
			}
		}
		else								//已经出现结点只有左孩子，则其后的结点没有孩子；
		{
			if (t->left || t->right)
			{
				DestroyQueue_t(Q);
				return false;
			}
		}
		//-----------------------------------

		if (t->left)
			EnQueue_t(Q, t->left);
		if (t->right)
			EnQueue_t(Q, t->right);
	}

	DestroyQueue_t(Q);
	return true;
}

Status FindAndDelete(BiTree &T, ElemType x)		//递归实现,在树 T 中删除每个以值 x 为根的子树
{
	if (!T)
		return OK;

	if (T->data == x)				//根结点是，则直接删除，结束函数；在递归调用中，传入的参数不会满足该条件
	{
		DestroyBiTree(T);
		return OK;
	}

	if (T->left)					//左子树存在，值符合则删除，❗并将相应指针指向空❗；否则继续查找
	{
		if (T->left->data == x)
		{
			DestroyBiTree(T->left);
			T->left = NULL;
		}
		else
		{
			FindAndDelete(T->left, x);
		}	
	}
	if (T->right)					//对右子树同上处理
	{
		if (T->right->data == x)
		{
			DestroyBiTree(T->right);
			T->right = NULL;
		}
		else
		{
			FindAndDelete(T->right, x);
		}
	}
	return OK;
}

Status FindAndDelete_1(BiTree & T, ElemType x)	//非递归实现
{
	if (!T)						//两个提前结束的条件
		return OK;
	if (T->data == x)
	{
		DestroyBiTree(T);
		return OK;
	}

	Stack_t S;
	InitStack_t(S);

	Push_t(S, T);
	BiTreeNode* t;
	while (!StackEmpty_t(S))	//前序遍历查找
	{
		Pop_t(S, t);
		
		if (t->right)			//值不是 x 入栈，是 x 直接销毁
		{
			if (t->right->data == x)
			{
				DestroyBiTree(t->right);
				t->right = NULL;
			}
			else
			{
				Push_t(S, t->right);
			}
		}
		if (t->left)
		{
			if (t->left->data == x)
			{
				DestroyBiTree(t->left);
				t->left = NULL;
			}
			else
			{
				Push_t(S, t->left);
			}
		}
	}							//遍历完成

	DestroyStack_t(S);

	return OK;
}
