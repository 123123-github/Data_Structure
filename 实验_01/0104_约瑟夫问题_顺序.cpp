//约瑟夫问题
//顺序表实现（C++结构体）

#include <iostream>
#include "List_Sq.h"
using namespace std;

//定义函数实现约瑟夫问题求解
//输入，围绕圆桌的人的信心，可以直接是位序
void Fun_Joseohus_Sq(SqList L, int s, int m)
{
	//d为出列人的位序,n为链表的现有长度,delete_elem为出列人的信息
	int d, delete_elem;
	int n = L.length;

	//链表长度不为0时，寻找下一个出列的人
	while (n != 0)
	{
		d = (s + m - 1) % n;
		if (d == 0)
			d = n;

		ListDelete_Sq(L, d, delete_elem);
		cout << delete_elem << '\t';

		s = d;
		n--;
	}
	cout << endl;

	return 0;
}

int main()
{
	//问题的初始的输入值，n为总人数，s为初始报数人位序，m为出列人所报的数
	int n, s, m;

	cout << "请依次输入：圆桌人数n，开始报数人位序s，出列人报数数m.\n";
	cin >> n >> s >> m;
	cout << endl;

	//实现信息存储
	SqList L;
	cout << "请输入围绕圆桌的人的信息（可以是位序）" << endl;
	CreatList_Sq(L, n);
	cout << "链表初始为：" << endl;
	ListTraverse_Sq(L);

	//调用解决问题的函数
	cout << "出列人的信息依次为：" << endl;
	Fun_Joseohus_Sq(L, s, m);

	system("pause");

	return 0;
}