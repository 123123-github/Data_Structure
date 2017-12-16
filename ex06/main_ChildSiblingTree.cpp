#include <iostream>
#include "ChildSiblingTree.h"
using namespace std;

int main()
{
	CSTree T;
	
	InitCSTree(T);

	CreatCSTree(T);

	cout << "前序遍历为:\n";
	PreOrderTraverse(T);

	cout << "原层序为:\n";
	PrintPriLevel(T);

	DestroyCSTree(T);

	system("pause");

	return OK;
}