#include <iostream>
#include "GraphM.h"
using namespace std;



int main()
{
	GraphM G;
	InitGraphM(G);

	CreatGraphM(G);

	//输出邻接矩阵
	for (int i = 1; i <= G.vexnum; i++)
	{
		for (int j = 1; j <= G.vexnum; j++)
		{
			cout << G.mat.elem[i][j].adj << '\t';
		}
		cout << '\n';
	}
	cout << endl;

	DestroyGraphM(G);

	system("pause");

	return 0;
}