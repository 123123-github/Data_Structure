//BiTree.h 函数实现

#include <iostream>
#include "BiTree.h"
#include <fstream>
#include <queue>
#include <stack>
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

		delete S.base;

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


//---------------------------- 判断是否为二叉排序树 --------------------------

bool IsBST(BiTree T)
{
	if (!T)
		return true;
	else if (!T->left && !T->right)
		return true;
	else if (!T->left)
	{
		if (T->data < T->right->data)
			return IsBST(T->right);
		else
			return false;
	}
	else if (!T->right)
	{
		if (T->left->data < T->data)
			return IsBST(T->left);
		else
			return false;
	}
	else							// 两个子树都存在
	{
		if (T->left->data < T->data && T->data < T->right->data)
			return (IsBST(T->left) && IsBST(T->right));
		else
			return false;
	}
}

int Depth(BiTree T)
{
	if (!T)
		return 0;
	else
	{
		int a, b;
		a = Depth(T->left);
		b = Depth(T->right);

		return ((a > b ? a : b) + 1);
	}
}

struct queueElem
{
	BiTreeNode* t;
	int level;
};

int Width(BiTree T)				// 算法思想 层序遍历过程记录结点层数 对同一层数结点统计个数
{
	queue < queueElem > Q;
	int levelnum[10] = { 0 };	// 数组应当大于树的深度
	queueElem q;
	int max = 0;				// 记录最大宽度

	if (!T)
		return 0;
	else
	{
		Q.push({ T,1 });		// 第一个进队结点是根 层数为 1 

		while (!Q.empty())
		{
			q = Q.front();
			levelnum[q.level]++;		// 统计同一层的结点
			Q.pop();

			if (q.t->left)
				Q.push({ q.t->left,q.level + 1 });			// ！！！  不能写成 ++ 不能改变原结点层标志
			if (q.t->right)
				Q.push({ q.t->right,q.level + 1 });
		}
		for (int i = 0; i < 10; i++)	// 找出最大值
			if (max < levelnum[i])
				max = levelnum[i];
	}

	return max;
}

int NodeNum(BiTree T)					// 层次遍历统计出队个数即可
{
	int num = 0;
	queue<BiTreeNode*> Q;
	BiTreeNode* t;

	if (!T)
		return 0;

	Q.push(T);
	while (!Q.empty())
	{
		t = Q.front();
		Q.pop();
		++num;

		if (t->left)
			Q.push(t->left);
		if (t->right)
			Q.push(t->right);
	}

	return num;
}

void FileCreat(ifstream &in, BiTree & T, const char* filename = "data.txt")		// 文件读取前序创建树
{
	ElemType e;
	in >> e;

	if (e == 0)
		T = NULL;
	else
	{
		MakeBiTNode(T, e);
		FileCreat(in, T->left, filename);
		FileCreat(in, T->right, filename);
	}
	return;
}


//--------------------------- 不使用标志位的后序遍历 -----------------------------

void PostOrder(BiTree T)
{
	stack<BiTreeNode*> S;
	BiTreeNode *t, *p;

	t = T;
	while (t)						// 结点存在，则进栈，结点左子树存在，左子树进栈，对进栈的结点做同样的处理，即左子树构成的一整条链进栈
	{
		S.push(t);
		t = t->left;
	}
	S.push(NULL);					// 加一个最后的标志位'#',标志结束，用 NULL 来表示这个 '#' 的意思

	while (!S.empty())
	{
		t = S.top();
		S.pop();
		if (t != NULL)				// 出栈结点访问
		{
			cout << t->data << '\t';
		}

		if (!S.empty())				// 出栈后，栈顶元素判断，（根据 '#' 的产生规则，此时最顶的元素一定不会是 NULL ）
		{
			p = S.top();
			if (p->right && p->right != t)			// 最顶部元素有右结点则右结点进栈（同时这个右结点没有被访问过，即 ！= t （刚刚出栈的元素））
			{
				p = p->right;		// 有元素进栈，则同最初的进栈操作；
				while (p)
				{
					S.push(p);
					p = p->left;
				}
				S.push(NULL);
			}
		}
	}
}

