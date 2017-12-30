// 二叉排序树
// 结构体
#pragma once
#include "Status.h"

struct BiTNode
{
	int data;
	BiTNode *left;
	BiTNode *right;
};



typedef BiTNode* BiTree;

void InitBiTree(BiTree &T);

Status SearchBST(BiTree T, int key, BiTNode* &f, BiTNode* &p);			// 找到时 f 指向 p 的双亲, p 指向搜索的结点;否则 p = f 

Status InsertBST(BiTree &T, int key);

Status CreatBST(BiTree &T);

Status DestroyBiTree(BiTree &T);

void PreOrderTraverse(BiTree T);

Status Search(BiTree T, int key, BiTNode *& p);

void SearchPrint(BiTree &T);											// 寻找指定值 存在输出 不存在输出最接近的值