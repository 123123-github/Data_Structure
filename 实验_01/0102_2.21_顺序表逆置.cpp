//顺序表逆置函数
#include "List_Sq.h"

Status ListReverse_Sq(SqList &L)
{
	if (L.length <= 0)
		return OK;
	//i为线性表第一个元素，j为线性表最后一个元素，t为交换时的中间元素
	int i, j, t;
	i = 1;
	j = L.length;

	//当i<j时，1.表长<=1，可以认为已经逆置 2.元素已完成逆置
	while (i < j)
	{
		t = L.elem[i - 1];
		L.elem[i - 1] = L.elem[j - 1];
		L.elem[j - 1] = t;

		i++;
		j--;
	}
	return OK;
}

int main()
{
	SqList L;
	int n;

	cout << "请输入线性表的元素个数n，及元素:\n";
	cin >> n;
	CreatList_Sq(L, n);

	cout << "初始化链表为:\n";
	ListTraverse_Sq(L);
	cout << "调用逆置函数后为:\n";
	ListReverse_Sq(L);
	ListTraverse_Sq(L);

	system("pause");

	return 0;
}