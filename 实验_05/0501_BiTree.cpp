// ADT BinaryTree 二叉链表结构实现
// C++
#include <iostream>
using namespace std;

//-----------------------函数结果状态代码--------------------
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;			//Status 为函数类型，值为函数结果状态代码
typedef char ElemType;		//ElemType 为二叉树结点存储数据类型
							
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

//------------------------基本操作 20个 -----------------------

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
	else if ((T->left) && (T->right))
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

Status PreOrderTraverse(BiTree &T)			//前序遍历输出
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
		cout << T->data;
		PreOrderTraverse(T->left);
		PreOrderTraverse(T->right);
		return OK;
	}
}

Status InOrderTraverse(BiTree &T)			//中序遍历输出
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
		cout << T->data;
		InOrderTraverse(T->right);
		return OK;
	}
}

Status PostOrderTraverse(BiTree &T)			//后序遍历输出
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
		cout << T->data;
		return OK;
	}
}

Status LevelOrderTraverse(BiTree &T)		//层次遍历二叉树
{
	/*暂未完成*/
	return OK;
}





//--------------------主函数测试----------------------
int main()
{


	return 0;
}


