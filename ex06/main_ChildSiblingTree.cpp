#include <iostream>
#include "ChildSiblingTree.h"
using namespace std;

int main()
{
	CSTree T;
	
	InitCSTree(T);

	CreatCSTree(T);

	cout << "ǰ�����Ϊ:\n";
	PreOrderTraverse(T);

	cout << "ԭ����Ϊ:\n";
	PrintPriLevel(T);

	DestroyCSTree(T);

	system("pause");

	return OK;
}