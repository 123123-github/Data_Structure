#include <iostream>
#include "List.h"
using namespace std;

int main()
{
	List L;

	for (int i = 1; i <= 20000; i++)
		L.ListInsert(rand());

	L.PrintList();

	L.HeapSort();

	L.PrintList();

	system("pause");

	return 0;
}