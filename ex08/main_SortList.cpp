#include <iostream>
#include "List.h"
using namespace std;

int main()
{
	List L;

	for (int i = 1; i <= 10; i++)
		L.ListInsert(10 - i);
	
	L.PrintList();

	//L.RadixSort();

	int	 keynum = L.GetKeynum();			// 1.获得循环次数

	queue Q[10];						// 初始化队列
	for (int i = 0;i < 10;++i)
	{
		Q[i].front = Q[i].tail = new qnode;
		Q[i].tail->next = NULL;
	}
	qnode* Head;						// 2.转换为链表
	L.ChangeToLink(Head);

	L.Distribute(Head, Q, 1);		// 结点分配到相应的队列，依据 rixnum
	L.Collect(Q, Head);

	L.PrintList();

	qnode *p;
	for (int i = 0;i < 10;++i)
	{
		p = Q[i].front->next;
		while (p)
		{
			cout << p->data << '\t';
			p = p->next;
		}
		cout << '\n';
	}

	L.ChangeToList(Head);




	system("pause");

	return 0;
}