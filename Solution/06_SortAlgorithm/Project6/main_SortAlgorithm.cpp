#include <iostream>
#include "\Code_github\Data_Structure\Solution\HeaderFile\List.h"
using namespace std;

int main()
{
	List L;

	for (int i = 1;i <= 200000;++i)
	{
		L.ListInsert(rand());
	}

	//L.PrintList();

	cout << '\n';

	L.HeapSort();

	//L.PrintList();



	system("pause");

	return 0;
}