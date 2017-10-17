// ADT List ��������
// ��ʽʵ�� (C++�ṹ��)
#include <iostream>
using namespace std;
//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status Ϊ�������ͣ�ֵΪ�������״̬����
typedef int Status;

//���Ա�_������

//��㶨��
struct LNode
{
	int data;
	int* next;
};
typedef LNode *Link;
//������
struct LinkList
{
	Link head;
	Link tail;

	int len;
};

//���������غ���:

//���� pָ��Ľ�㣬��ֵΪe���ɹ�����OK�����򷵻�ERROR
Status MakeNode(Link &p, int e)
{
	p = new LNode;
	if (p == NULL)
		return ERROR;

	p->data = e;
	p->next = NULL;

	return OK;
}
//�ͷ� ���
Status DeleteNode(Link &p)
{
	if (p == NULL)
		return ERROR;

	delete p;
	return OK;
}


//ʮ���� ��������ʵ�֣�

//����ձ�L,�ɹ�ʱ����OK�����򷵻�ERROR
Status InitList_Link(LinkList &L)
{
	L.head = new LNode;
	if (L.head == NULL)
		return ERROR;

	L.head->next = NULL;
	tail = head;
	len = 0;

	return OK;
}
//�������Ա�L
Status DestroyList_Link(LinkList &L)
{
	if (L.head == NULL)
		return OK;

	Link p, q;
	p = L.head;
	q = p->next;

	while (q != NULL)
	{
		delete p;
		p = q;
		q = q->next;
	}
	delete p;

	L.head = NULL;
	L.tail = L.head;
	len = -1;

	return OK;
}
//������Ϊ�ձ�,�ɹ�����OK�����򷵻�ERROR
Status ClearList_Link(LinkList &L)
{
	if (L.head == NULL)
		return ERROR;
	if (L.head == NULL)
		return OK;

	Link p, q;
	p = L.head->next;
	q = p->next;
	while (q != NULL)
	{
		delete p;
		p = q;
		q = q->next;
	}
	delete p;

	L.tail = L.head;
	len = 0;
}
//��Ϊ�շ���TRUE�����򷵻�FALSE
Status ListEmpty_Link(LinkList L)
{
	if (L.len == 0)
		return	TRUE;
	else
		return FALSE;
}
//���ر�ĳ���
int ListLength_Link(LinkList L)
{
	return L.len;
}
//��e����L�еĵ�i��ֵ���ɹ�ʱ��������OK�����򷵻�FALSE
Status GetElem_Link(LinkList L, int i, int &e)
{
	if (i<1 || i>L.len)
		return ERROR;

	Link p = L.head;
	int j = 1;

	while (j<i)
	{
		p = p->next;
		j++;
	}
	e = p->data;

	return	OK;
}
//����L�е�һ����e��ȵ�Ԫ�ص�λ�򣬲�����ʱ����0
int LocateElem_Link(LinkList L, int e)
{
	Link p = L.head;
	int i = 1;

	while (p->data != e && p != NULL)
	{
		p = p->next;
		i++;
	}
	if (p == NULL)
		return	0;

	return i;
}
//�� pre_e ����Ԫ�� cur_e ��ǰ���������ɹ�����OK�����򷵻�ERROR
Status PriorElem_Link(LinkList L, int cur_e, int &pre_e)
{
	int i = LocateElem_Link(L, cur_e);

	if (i<2 || i>L.len)
		return ERROR;

	GetElem_Link(L, i - 1, pre_e);
	return OK;
}
//�� next_e ����Ԫ�� cur_e �ĺ�̣������ɹ�����OK�����򷵻�ERROR
Status NextElem_Link(LinkList L, int cur_e, int &next_e)
{
	int i = LocateElem_Link(L, cur_e);

	if (i<1 || i>L.len - 1)
		return ERROR;

	GetElem_Link(L, i + 1, next_e)
		return OK;
}
//�����Ա�ĵ�i��λ�ò���e;���ɹ�����OK�����򷵻�ERROR
Status ListInsert_Link(LinkList &L, int i, int e)
{
	if (i<1 || i>L.len + 1)
		return ERROR;

	Link s;
	MakeNode(s, e);
	Link p, q;
	int j = 1;
	p = L.head;
	q = p->next;
	while (j < i)
	{
		p = p->next;
		q = q->next;
		j++;
	}
	s->next = q;
	p->next = p;

	L.len++;

	return OK;

}
//�����Ա�ĵ�i��λ��ɾ��,��e������ֵ;���ɹ�����OK�����򷵻�ERROR
Status ListDelete_Link(LinkList &L, int i, int &e)
{
	if (i<1 || i>L.len)
		return ERROR;

	Link p, q;
	int j = 1;
	p = L.head;
	q = p->next;
	while (j < i)
	{
		p = p->next;
		q = q->next;
		j++;
	}
	p->next = q->next;
	e = q->data;
	DeleteNode(q);

	L.len--;

	return OK;
}
//�������Ա�
Status ListTraverse_Sq()
{

}


