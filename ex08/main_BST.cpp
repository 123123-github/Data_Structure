#include "BST.h"
#include <iostream>
using namespace std;

int main()
{
	BiTree T;
	InitBiTree(T);

	cout << "��������������ֵ,���� -1 ��������\n";
	CreatBST(T);

	cout << "�����ɹ�\n\n" << "ǰ��������Ϊ:\n";
	PreOrderTraverse(T);

	SearchPrint(T);
	
	DestroyBiTree(T);

	system("pause");

	return 0;
}