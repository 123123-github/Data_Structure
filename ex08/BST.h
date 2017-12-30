// ����������
// �ṹ��
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

Status SearchBST(BiTree T, int key, BiTNode* &f, BiTNode* &p);			// �ҵ�ʱ f ָ�� p ��˫��, p ָ�������Ľ��;���� p = f 

Status InsertBST(BiTree &T, int key);

Status CreatBST(BiTree &T);

Status DestroyBiTree(BiTree &T);

void PreOrderTraverse(BiTree T);

Status Search(BiTree T, int key, BiTNode *& p);

void SearchPrint(BiTree &T);											// Ѱ��ָ��ֵ ������� �����������ӽ���ֵ