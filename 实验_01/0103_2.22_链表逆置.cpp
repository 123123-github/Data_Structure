#include "List_Link.h"

//ʵ�ֽ����s����������λ
Status Insert_First(LinkList &L, Link &s)
{
	if (L.head == L.tail) 
	{
		L.tail = s;
		L.head->next = s;
		s->next = NULL;

		return OK;
	}

	s->next = L.head->next;
	L.head->next = s;

	return OK;
}

//��������Ԫ������
void Reverse_Link(LinkList &L)
{
	//����Ϊ��ʱ����ʾ���������
	if (L.head == L.tail)
		return OK;
	
	//����Ϊ��ʱ
	Link p, q;
	L.tail = L.head;
	p = L.head->next;
	q = p->next;
	//����Ԫ�ض���1��ʱ
	while (q != NULL)
	{
		Insert_First(L, p);
		p = p->next;
		q = q->next;
	
	}
	Insert_First(L, p);

	return OK;
}