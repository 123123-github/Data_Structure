#include <iostream>
#include "HashTable.h"
using namespace std;

int HashFunc(int e)
{
	return e % 13;
}

int main()
{
	HashTable H(16);

	H.SetHash(HashFunc);

	int e[] = { 19 ,14 ,23 ,1, 68, 20, 84, 27, 55, 11, 10, 79 };
	cout << "请输入要插入的数据\n";
	for (int i = 0; i < 12; i++)
	{
		H.Insert(e[i]);
	}

	H.PrintHashTable();

	int p, c;

	if (H.Search(84, p, c))
		cout << "success\n";

	cout << p << '\t' << c;

	system("pause");

	return 0;
}