//线性表顺序结构实现  C = A ∪ B；
//A,B,C 均递增，且C在A的空间上建立；

#include <iostream>
#include "List_Sq.h"

void ListUnion_Sq(SqList &La, SqList Lb)
{
	//a,b记录两线性表中的数组首地址
	int *a, *b;
	a = La.elem;
	b = Lb.elem;

	//i,j记录 a b 数组中元素位置，num_Equal为A B集合中相等元素的个数，num_Insert为B集合插入A集合中元素的个数；
	int i, j, num_Equal, num_Insert;

	//当a b数组均为遍历完时
	while (i <= La.length + num_Insert && j <= Lb.length)
	{
		if (a[i - 1] <= b[j - 1])
			i++;
		if (a[i - 1] == b[j - 1])
		{
			i++;
			j++;
			num_Equal++;
		}
		if (a[i-1]>b[j-1])
		{
			ListInsert_Sq(La, i, b[j - 1]);
			i++;
			j++;
			num_Insert++;
		}
	}
	//当b未遍历完时，将B中剩余元素全部插入A集合中
	while (j <= Lb.length)
	{
		ListInsert_Sq(La, i, b[j - 1]);
		i++;
		j++;
	}
	//当A未遍历完，B遍历完成时，此时并集已完成

	return;
}