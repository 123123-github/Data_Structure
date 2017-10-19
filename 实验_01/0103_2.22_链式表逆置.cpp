#include "List_Link.h"

//实现将结点s插入链表首位
Status ListInsertFirst_Link(LinkList &L, Link s)
{
		s->next = L.head->next;
		L.head->next = s;

		//如果插入前链表为空，则需要修改尾指针位置
		if(L.head==L.tail)
			L.tail = s;
	
	return OK;
}

//线性链表元素逆置
Status ListReverse_Link(LinkList &L)
{
	//算法实现：先将链表置空，再将链表中的元素逐个插入链表首位
	// p 为插入链表的结点指针， q 为 p 在插入链表前的下一个结点指针
	Link p, q;

	p = L.head->next;

	//链表置为空
	L.head->next = NULL;
	L.tail = L.head;

	while (p)
	{
		q = p->next;
		ListInsertFirst_Link(L,p);
		p = q;
	}

	return OK;
}

int main()
{
	LinkList L;
	int n;

	cout << "请输入线性表的元素个数n，及元素:\n";
	cin >> n;
	CreatList_Link(L, n);

	cout << "初始化链表为:\n";
	ListTraverse_Link(L);
	cout << "调用逆置函数后为:\n";
	ListReverse_Link(L);
	ListTraverse_Link(L);

	system("pause");

	return 0;
}