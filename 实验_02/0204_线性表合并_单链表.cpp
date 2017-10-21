//线性表链式结构实现  C = A ∪ B；
//A,B,C 均递增，且C在A的空间上建立；

#include "List_Link.h"

void ListUnion_Link(LinkList &La, LinkList Lb,LinkList &Lc)
{
	// p q 指向 La 中的结点 , s 指向 Lb 中的结点
	Link p, q, s;
	// t 记录 s 的前一个位置
	Link t;
	int e;

	p = La.head;
	q = p->next;
	t = Lb.head;
	s = t->next;

	while (q && s)
	{
		if (q->data == s->data)
		{
			p = q;
			q = q->next;

			t = s;
			s = s->next;
		}
		else if (q->data < s->data)
		{
			p = q;
			q = q->next;
		}
		else
		{
			t->next = s->next;

			p->next = s;
			s->next = q;
			p = s;

			s = t->next;
		}
	}
	//当A未遍历完，B遍历完成时，此时并集已完成
	//如果 Lb 未遍历完，将 Lb 中剩余元素一次全部插入 La 中
	if (s)
	{
		p->next = s;

		// La 的尾部有添加元素，则此时需要修改尾指针
		La.tail = Lb.tail;
	}
	//线性表 Lc 指向线性表 La 的空间
	Lc.head = La.head;
	Lc.len = La.len;
	Lc.tail = La.tail;

	return;

}

//函数测试
int main()
{
	LinkList La, Lb, Lc;
	int m, n;

	cout << "创建 A B 集合，请输入元素个数 n 及元素" << endl;
	cin >> m;
	CreatList_Link(La, m);
	cin >> n;
	CreatList_Link(Lb, n);
	cout << "A 集合为" << endl;
	ListTraverse_Link(La);
	cout << "B 集合为" << endl;
	ListTraverse_Link(Lb);

	ListUnion_Link(La, Lb, Lc);
	cout << "合并后集合C为" << endl;
	ListTraverse_Link(Lc);

	system("pause");

	return 0;
}