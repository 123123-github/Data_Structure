#include <iostream>
#include "GraphM.h"
using namespace std;



int main()
{
	GraphM G;
	InitGraphM(G);

	CreatGraphM(G);

	PrintVexSet(G);
	PrintAdjMat(G);

	VexElemType v,w,adjvex;
	cout << "请输入一个顶点 v \n";
	cin >> v;
	FirstAdjVex(G, v, adjvex);
	cout << "第一个邻接顶点为：\n";
	cout << adjvex << endl;

	cout << "请输入顶点 w \n";
	cin >> w;
	NextAdjVex(G, v, w, adjvex);
	cout << " v 相对于 w 之后的第一个邻接结点是：\n";
	cout << adjvex;

	DestroyGraphM(G);

	system("pause");

	return 0;
}