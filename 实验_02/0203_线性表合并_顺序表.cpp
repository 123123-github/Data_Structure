//线性表顺序结构实现  C = A ∪ B；
//A,B,C 均递增，且C在A的空间上建立

#include "List_Sq.h"

void ListUnion_Sq(SqList &La, SqList Lb,SqList &Lc)
{
	//a,b记录两线性表中的数组首地址
	int *a, *b;
	a = La.elem;
	b = Lb.elem;

	//i,j记录 a b 数组中元素位置
	int i = 0, j = 0;

	//La Lb 均未遍历完时
	while (i < La.length  && j < Lb.length)
	{
		if (a[i] < b[j])
			i++;
		else if (a[i] == b[j])
		{
			i++;
			j++;
		}
		else
		{
			ListInsert_Sq(La, i + 1, b[j]);
			i++;
			j++;
		}
	}
	//当A未遍历完，B遍历完成时，此时并集已完成
	//当 Lb 未遍历完时，将 Lb 中剩余元素全部插入 La 中
	while (j < Lb.length)
	{
		ListInsert_Sq(La, i + 1, b[j]);
		i++;
		j++;
	}
	//线性表 Lc 指向线性表 La 的空间
	Lc.elem = La.elem;
	Lc.length = La.length;
	Lc.listsize = La.listsize;

	return;
}

//函数测试
int main()
{
	SqList La, Lb, Lc;
	int m, n;

	cout << "创建 A B 集合，请输入元素个数 n 及元素" << endl;
	cin >> m;
	CreatList_Sq(La, m);
	cin >> n;
	CreatList_Sq(Lb, n);
	cout << "A 集合为" << endl;
	ListTraverse_Sq(La);
	cout << "B 集合为" << endl;
	ListTraverse_Sq(Lb);

	ListUnion_Sq(La, Lb, Lc);
	cout << "合并后集合C为" << endl;
	ListTraverse_Sq(Lc);

	system("pause");

	return 0;
}