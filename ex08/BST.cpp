#include "BST.h"
#include <iostream>
using namespace std;

void InitBiTree(BiTree & T)
{
	T = NULL;
}

Status SearchBST(BiTree T, int key, BiTNode *& f, BiTNode *& p)
{
	if (!T)
	{
		p = f;
		return FALSE;
	}

	if (T->data == key)
	{
		p = T;
		return OK;
	}
	else if (T->data < key)			// 在右子树中寻找
	{
		f = T;
		return SearchBST(T->right, key, f, p);
	}
	else
	{
		f = T;
		return SearchBST(T->left, key, f, p);
	}
}

Status InsertBST(BiTree & T, int key)
{
	BiTNode* f = NULL, *p;

	if (SearchBST(T, key, f, p))		// 如果要插入的数存在，则不执行插入操作
		return FALSE;

	// 不存在时 p 指向 要插入位置的双亲

	BiTNode *s;
	s = new BiTNode;
	s->data = key;
	s->left = s->right = NULL;

	if (!p)									// p 不存在，即 T 为 NULL ,直接将 T 指向新分配的结点
		T = s;
	else if (p->data < key)					// 插入右侧
		p->right = s;
	else
		p->left = s;

	return OK;
}

Status CreatBST(BiTree & T)
{
	int data;

	cin >> data;
	while (data != -1)				// 输入 -1 时停止建树 ( 可修改为其它数据 )
	{
		InsertBST(T, data);
		cin >> data;
	}

	return OK;
}

Status DestroyBiTree(BiTree & T)
{
	if (!T)
		return OK;
	else
	{
		DestroyBiTree(T->left);
		DestroyBiTree(T->right);

		delete T;
	}
		T = NULL;
		return OK;
}

void PreOrderTraverse(BiTree T)
{
	if (!T)
		return;
	else
	{
		cout << T->data << '\t';
		PreOrderTraverse(T->left);
		PreOrderTraverse(T->right);
	}
}

int *P, num = 0;

Status Search(BiTree T, int key, BiTNode *& p)
{
	if (!T)
	{
		return FALSE;
	}

	if (T->data == key)
	{
		p = T;
		return OK;
	}
	else if (T->data < key)			// 在右子树中寻找
	{
		P[num++] = T->data;
		return Search(T->right, key, p);
	}
	else
	{
		P[num++] = T->data;
		return Search(T->left, key, p);
	}
}

void SearchPrint(BiTree & T)		// 算法思想 保存搜索时的路径上的值，要搜索的值不存在时，在该路径上寻找
{
	int key;
	BiTNode *p = NULL;
	
	P = new int[20];				// 申请记录路径的空间，可以修改为数的结点数，在建树过程中记录 此处简化处理
	num = 0;

	cout << "\n请输入要查找的数\n";
	cin >> key;
	
	if (Search(T, key, p))										// 存在则输出
		cout << p->data;
	else														// 不存在输出最接近的两个数( 相等时为一个 )
	{
		int sub[20];											// 用于求差值 以便找到最接近的数 ( 可改为动态申请空间 )
		
		int Min1 = INT32_MAX;		// 记录数据
		int Min2 = INT32_MAX;
		int min1 = 0;				// 记录位序
		int min2 = 0;
		
		for (int i = 0;i < num;i++)
			sub[i] = abs(P[i] - key);
		for (int i = 0; i < num; i++)
		{
			if (sub[i] < Min1)
			{
				Min2 = Min1;			/* !!! 注意顺序 !!! */
				Min1 = sub[i];

				min2 = min1;
				min1 = i;
			}
			else if (sub[i] < Min2)
			{
				Min2 = sub[i];

				min2 = i;
			}
		}

		cout << "该数不存在,最接近的数为:\n";
		if (min1 < num)
		{
			cout << P[min1] << '\t';
		}
		if (min2 < num)
		{
			cout << P[min2] << '\n';
		}
	}

	delete[] P;
}
