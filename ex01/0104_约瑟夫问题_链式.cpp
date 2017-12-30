//约瑟夫问题
//链表实现（C++结构体）

#include <iostream>
#include "List_Link.h"
using namespace std;

//实现将结点s插入链表首位
Status ListInsertFirst_Link(LinkList &L, Link s)
{
	s->next = L.head->next;
	L.head->next = s;

	//如果插入前链表为空，则需要修改尾指针位置
	if (L.head == L.tail)
		L.tail = s;

	return OK;
}

//定义函数实现约瑟夫问题求解
//输入：围绕圆桌的人的信息，可以直接是位序
void Fun_Joseohus_Link(LinkList &L,int s,int m)
{
	//d为出列人的位序,n为链表的现有长度,delete_elem为出列人的信息
	int d, delete_elem;
	int n = L.len;

	//链表长度不为0时，寻找下一个出列的人
	while (n != 0)
	{
		d = (s + m - 1) % n;
		if (d == 0)
			d = n;

		ListDelete_Link(L, d, delete_elem);
		cout << delete_elem << '\t';

		s = d;
		n--;
	}
	cout << endl;

	return;
}

int main()
{   
	//问题的初始的输入值，n为总人数，s为初始报数人位序，m为出列人所报的数
	int n, s, m;

	cout << "请依次输入：圆桌人数n，开始报数人位序s，出列人报数数m.\n";
	cin >> n >> s >> m;
	cout << endl;

	//实现信息存储
	LinkList L;
	cout << "请输入围绕圆桌的人的信息（可以是位序）" << endl;
	CreatList_Link(L, n);
	cout << "链表初始为：" << endl;
	ListTraverse_Link(L);

	//调用解决问题的函数
	cout << "出列人的信息依次为：" << endl;
	Fun_Joseohus_Link(L,s,m);
	DestroyList_Link(L);

	system("pause");

	return 0;
}