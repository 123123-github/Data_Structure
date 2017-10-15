#include "List_Link.h"

//实现将结点s插入链表首位
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

//线性链表元素逆置
void Reverse_Link(LinkList &L)
{
	//链表为空时，表示逆置已完成
	if (L.head == L.tail)
		return OK;
	
	//链表不为空时
	Link p, q;
	L.tail = L.head;
	p = L.head->next;
	q = p->next;
	//链表元素多于1个时
	while (q != NULL)
	{
		Insert_First(L, p);
		p = p->next;
		q = q->next;
	
	}
	Insert_First(L, p);

	return OK;
}