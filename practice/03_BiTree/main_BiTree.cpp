//ADT BinaryTree 二叉链表结构
//基本操作测试

#include <iostream>
#include <fstream>
#include "BiTree.h"
using namespace std;

//--------------------主函数测试----------------------
int main()
{
	BiTree T;
	ifstream in;

	InitBiTree(T);
	char filename[20] = "data2.txt";

	//创建树
	cout << "创建树\n";

	in.open(filename);
	if (in.fail())
	{
		cout << "文件打开失败\n";
		system("pause");
		return 0;
	}

	FileCreat(in, T, filename);

	in.close();

	cout << "前序遍历结果\n";
	PreOrderTraverse(T);
	
	cout << "深度\t" << Depth(T) << '\n';
	
	cout << "宽度\t" << Width(T) << '\n';
	
	if (IsBST(T))
		cout << "是二叉排序树\n";
	else
		cout << "不是二叉排序树\n";
	
	cout << "结点数\n" << NodeNum(T);
	//销毁树
	DestroyBiTree(T);
	system("pause");

	return 0;
}