#include "BST.h"
#include <iostream>
using namespace std;

int main()
{
	BiTree T;
	InitBiTree(T);

	cout << "请输入正整数数值,输入 -1 结束输入\n";
	CreatBST(T);

	cout << "建树成功\n\n" << "前序遍历结果为:\n";
	PreOrderTraverse(T);

	SearchPrint(T);
	
	DestroyBiTree(T);

	system("pause");

	return 0;
}