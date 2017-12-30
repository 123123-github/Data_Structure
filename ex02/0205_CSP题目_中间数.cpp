//CSP题目
//问题描述：首先输入正整数n，接着输入n个正整数，如果其中存在一个数:
//比该数大的个数等于比该数小的个数，则输出该数，如果不存在则输出 - 1。

#include <iostream>
using namespace std;

void ListSort(int a[], int n)
{
	int i, j, t;

	for (i = 1;i < n;i++)
	{
		t = a[i];
		for (j = i - 1;j >= 0 && a[j] > t;j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}

	return;

}

bool MiddleExit(int a[], int n, int position)
{
	int i;
	int count1 = 0, count2 = 0;
	int middle = a[position - 1];

	for (i = 0;i < position - 1;i++)
		if (a[i] != middle)
			count1++;
	for (i = position;i < n;i++)
		if (a[i] != middle)
			count2++;

	if (count1 == count2)
		return true;
	else
		return false;
}

int main()
{
	int n;
	int *a;

	cin >> n;
	a = new int[n];
	for (int i = 0;i < n;i++)
		cin >> a[i];

	//对输入数据排序
	ListSort(a, n);

	// n 为偶数时
	if (n%2==0)
	{
		int position1, position2;

		position1 = n / 2;
		position2 = position1 + 1;

		if (MiddleExit(a, n, position1))
			cout << a[position1 - 1];
		else if (MiddleExit(a, n, position2))
			cout << a[position2 - 1];
		else
			cout << -1;
	}
	//n 为奇数时
	if (n % 2 != 0)
	{
		int position;

		position = (n + 1) / 2;
		if (MiddleExit(a, n, position))
			cout << a[position-1];
		else
			cout << -1;
	}

	//释放空间
	delete[]a;

	system("pause");

	return 0;
}