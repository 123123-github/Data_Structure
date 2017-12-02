//ADT BinaryTree 二叉链表结构
//基本操作测试

#include <iostream>
#include "BiTree.h"
using namespace std;

//--------------------主函数测试----------------------
int main()
{
	BiTree T;
	InitBiTree(T);

	//创建树
	cout << "请前序输入树结点，为空则使用'#'代替\n";
	CreatBiTree(T);

	cout << "请输入要删除的结点\n";
	ElemType x;
	cin >> x;
	FindAndDelete(T, x);

	cout << "删除后的层序遍历为:\n";
	LevelOrderTraverse(T);

	//销毁树
	DestroyBiTree(T);

	system("pause");

	return 0;
}