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
	else if (T->data < key)			// ����������Ѱ��
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

	if (SearchBST(T, key, f, p))		// ���Ҫ����������ڣ���ִ�в������
		return FALSE;

	// ������ʱ p ָ�� Ҫ����λ�õ�˫��

	BiTNode *s;
	s = new BiTNode;
	s->data = key;
	s->left = s->right = NULL;

	if (!p)									// p �����ڣ��� T Ϊ NULL ,ֱ�ӽ� T ָ���·���Ľ��
		T = s;
	else if (p->data < key)					// �����Ҳ�
		p->right = s;
	else
		p->left = s;

	return OK;
}

Status CreatBST(BiTree & T)
{
	int data;

	cin >> data;
	while (data != -1)				// ���� -1 ʱֹͣ���� ( ���޸�Ϊ�������� )
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
	else if (T->data < key)			// ����������Ѱ��
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

void SearchPrint(BiTree & T)		// �㷨˼�� ��������ʱ��·���ϵ�ֵ��Ҫ������ֵ������ʱ���ڸ�·����Ѱ��
{
	int key;
	BiTNode *p = NULL;
	
	P = new int[20];				// �����¼·���Ŀռ䣬�����޸�Ϊ���Ľ�������ڽ��������м�¼ �˴��򻯴���
	num = 0;

	cout << "\n������Ҫ���ҵ���\n";
	cin >> key;
	
	if (Search(T, key, p))										// ���������
		cout << p->data;
	else														// �����������ӽ���������( ���ʱΪһ�� )
	{
		int sub[20];											// �������ֵ �Ա��ҵ���ӽ����� ( �ɸ�Ϊ��̬����ռ� )
		
		int Min1 = INT32_MAX;		// ��¼����
		int Min2 = INT32_MAX;
		int min1 = 0;				// ��¼λ��
		int min2 = 0;
		
		for (int i = 0;i < num;i++)
			sub[i] = abs(P[i] - key);
		for (int i = 0; i < num; i++)
		{
			if (sub[i] < Min1)
			{
				Min2 = Min1;			/* !!! ע��˳�� !!! */
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

		cout << "����������,��ӽ�����Ϊ:\n";
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
