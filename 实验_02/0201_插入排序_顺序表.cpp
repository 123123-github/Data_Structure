//建立元素值为整型的顺序表，插入排序算法实现顺序表排序。
//C++结构体实现

#include "List_Sq.h"

void ListInsertionSort_Sq(SqList &L)
{
	// a 为顺序表数组头指针, t 临时存放数据
	int *a = L.elem, t;
	int i, j;

	//简单插入法排序
	for ( i = 1;i < L.length;i++)
	{
		t = a[i];
		for ( j = i - 1;j >= 0 && a[j] > t;j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}

	return;
}

int main()
{
	//排序算法测试
	SqList L;
	int n;

	cout << "请输入元素个数n及元素" << endl;
	cin >> n;

	CreatList_Sq(L, n);
	cout << "线性表元素为:" << endl;
	ListTraverse_Sq(L);

	//排序函数调用
	ListInsertionSort_Sq(L);
	cout << "排序后为：" << endl;
	ListTraverse_Sq(L);

	//顺序表销毁
	DestroyList_Sq(L);

	system("pause");

	return 0;
}