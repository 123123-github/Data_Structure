#include <iostream>
#include "ChildSiblingTree.h"
using namespace std;

//------------------------ CSTree ����------------------------

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


//-------���ö��ж���-------

Status MakeQueueNode_t(QNode_t* &s, BiTreeNode *t)	//������
{
	s = new QNode_t;
	if (!s)
		return ERROR;

	s->next = NULL;
	s->elem = t;

	return OK;
}

Status InitQueue_t(Queue_t &Q)		//��ʼ������
{
	Q.front = new QNode_t;
	if (!Q.front)
		return ERROR;

	Q.front->next = NULL;
	Q.rear = Q.front;

	return OK;
}

Status DestroyQueue_t(Queue_t &Q)	//���ٶ���
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

bool QueueEmpty_t(Queue_t Q)		//���Ƿ�Ϊ��
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

Status EnQueue_t(Queue_t &Q, BiTreeNode* t)			//���
{
	QNode_t *s;
	MakeQueueNode_t(s, t);

	Q.rear->next = s;
	Q.rear = s;

	return OK;
}

Status DeQueue_t(Queue_t &Q, BiTreeNode* &t)				//����
{
	if (Q.front == Q.rear)
		return	ERROR;

	Queueptr_t p;
	p = Q.front->next;
	t = p->elem;

	if (p == Q.rear)	//�����βָ�뱻ɾ��
		Q.rear = Q.front;

	Q.front->next = p->next;
	delete p;
	p = NULL;

	return OK;
}


//------------------------ �������� -----------------------

Status InitCSTree(CSTree & T)
{
	T = NULL;

	return OK;
}

Status DestroyCSTree(CSTree & T)		//�ݹ�������������������ٷ�ʽ��ͬ
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
	//--------- ���������Ϣ --------
	
	int n;
	ElemType *value, *parent;

	cout << "���������Ľڵ���\n";
	cin >> n;

	if (n <= 0)						//Ϊ����ʱ��ǰ����
	{
		T = NULL;
		return OK;
	}

	value = new ElemType[n];		//�����������Ľ�㽨����
	if (!value)
		return ERROR;
	parent = new ElemType[n];		//����Ҫָ��ÿ������˫��
	if (!parent)
		return OK;

	cout << "�밴�ղ����������Ľ��\n";
	for (int i = 0; i < n; i++)
	{
		cin >> value[i];
	}
	cout << "����������ж�Ӧ����˫�� ���� # ��ʾ\n";
	for (int i = 0; i < n; i++)
	{
		cin >> parent[i];
	}

	//---------- ���� ----------
	/*
	---�Ƚ��ø�
	---�ٽ��� n - 1 �����
	--����ǰһ���� parent ��ͬ���ҵ�˫�ף���ǰ�ڵ���Ϊ�� first_child 
	--��ͬ����Ϊ�� next_sibling
	*/
	
	CSNode *t;			// t ָ��ǰ�������ǰһ�����
	int i=1;			// i ʼ�ձ�ʶ�����е�ǰ�������λ����Ϣ


	MakeCSNode(T, value[0]);
	t = T;
	
	while (i < n)			//�˴� i ͬʱ��ʾ������ɵĽ����		/*��дΪforʱ�ᶪʧ���ݣ���Ϊfor�в�������i++*/
	{
		while (i < n && (parent[i] == parent[i - 1]))		//��ǰһ��������ֵ�
		{
			MakeCSNode(t->next_sibling, value[i]);
			
			t = t->next_sibling;
			i++;
		}

		while (i < n && (parent[i] != parent[i - 1]))		//��ǰһ�����ĺ���
		{
			t = Search(T, parent[i]);				//�ҵ���ǰҪ�������˫��
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
	Queue_t Q_branch, Q_print;			//��ʾ��֧�Ķ��� �� �������������εĶ���
	
	InitQueue_t(Q_branch);				//�洢ÿ����֧����ʼ��ַ
	InitQueue_t(Q_print);

	EnQueue_t(Q_branch, p);				
	while (!QueueEmpty_t(Q_branch))
	{
		while (!QueueEmpty_t(Q_branch))			//���ÿ����֧
		{
			DeQueue_t(Q_branch, p);
			
			while (p)							//��֧������Ԫ��ȫ�����(���� sibling ����)
			{
				EnQueue_t(Q_print, p);
				p = p->next_sibling;
			}
		}

		while (!QueueEmpty_t(Q_print))
		{
			DeQueue_t(Q_print, p);

			if (p->first_child)					//���з�֧��Ԫ�أ����ǰ���� first_child ���
			{
				EnQueue_t(Q_branch, p->first_child);
			}

			cout << p->data << '\t';			// print �����е�ÿһ��Ԫ�ض����
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