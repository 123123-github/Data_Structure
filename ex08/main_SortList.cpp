#include <iostream>
#include "List.h"
using namespace std;

int main()
{
	List L;

	for (int i = 1;i <= 20000000;++i)
	{
		L.ListInsert(rand());
	}

	//L.PrintList();

	cout << '\n';

	L.RadixSort();

	//L.PrintList();



	system("pause");

	return 0;
}