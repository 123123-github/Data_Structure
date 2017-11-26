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

	//遍历
	cout << "\n前序遍历结果：\n";
	PreOrderTraverse(T);	//前序
	cout << "\n中序遍历结果：\n";
	InOrderTraverse(T);		//中序
	cout << "\n后序遍历结果：\n";
	PostOrderTraverse(T);	//后序


	cout << "\n层次遍历结果\n";
	LevelOrderTraverse(T);	//层次

	cout << "\n前序遍历结果(非递归)：\n";
	PreOrderTraverse_1(T);
	cout << "\n中序遍历结果(非递归)：\n";
	InOrderTraverse_1(T);
	cout << "\n后序遍历结果(非递归)：\n";
	PostOrderTraverse_1(T);

	if (IsComoleteBiTree(T))
		cout << "是完全二叉树\n";


	//删除某一结点
	ElemType x;
	cout << "请输入要删除的结点";
	cin >> x;
	FindAndDelete_1(T, x);



	cout << "\n层次遍历结果\n";
	LevelOrderTraverse(T);	//层次

	cout << "\n前序遍历结果(非递归)：\n";
	PreOrderTraverse_1(T);
	cout << "\n中序遍历结果(非递归)：\n";
	InOrderTraverse_1(T);
	cout << "\n后序遍历结果(非递归)：\n";
	PostOrderTraverse_1(T);

	if (IsComoleteBiTree(T))
		cout << "是完全二叉树\n";
	else
		cout << "不是完全二叉树\n";


	//销毁树
	DestroyBiTree(T);

	system("pause");

	return 0;
}