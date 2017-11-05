//建立元素值为整型的单链表，插入排序算法实现单链表排序。
//C++结构体实现

#include "List_Link.h"

//该函数实现将结点s插入非递减链表L后仍保持L为非递减链表
void AscendingInsert_Link(LinkList &L, Link s)
{
	Link p, q;
	p = L.head;
	q = p->next;

	//循环结束后 q 指向第一个数据 >= s->data 的结点
	while (q && q->data < s->data)
	{
		p = q;
		q = q->next;
	}
	p->next = s;
	s->next = q;

	//若插入位置为链表尾部，则需要对尾指针做调整
	if (!q)
		L.tail = p;

	return;
}

//插入法排序链式实现
void ListInsertionSort_Link(LinkList &L)
{
	// p 指针遍历链表元素结点， t 暂存 p 结点的下一个位置
	Link p, t;
	p = L.head->next;

	//将链表置空，再将未释放的结点非递减插入
	L.head->next = NULL;
	L.tail = L.head;

	while (p)
	{
		t = p->next;
		AscendingInsert_Link(L, p);
		p = t;
	}

	return;
}

//测试函数功能
int main()
{
	//排序算法测试
	LinkList L;
	int n;

	cout << "请输入元素个数n及元素" << endl;
	cin >> n;

	CreatList_Link(L, n);
	cout << "线性表元素为:" << endl;
	ListTraverse_Link(L);

	//排序函数调用
	ListInsertionSort_Link(L);
	cout << "排序后为：" << endl;
	ListTraverse_Link(L);

	//链表销毁
	DestroyList_Link(L);

	system("pause");

	return 0;
}