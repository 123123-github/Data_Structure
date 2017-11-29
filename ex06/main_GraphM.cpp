#include <iostream>
#include "GraphM.h"
using namespace std;



int main()
{
	GraphM G;
	InitGraphM(G);

	CreatGraphM(G);

	PrintGraphMat(G);

	VexElemType v;
	cout << "请输入要添加的顶点:\n";
	cin >> v;
	InsertVex(G, v);

	PrintGraphMat(G);

	DestroyGraphM(G);

	system("pause");

	return 0;
}