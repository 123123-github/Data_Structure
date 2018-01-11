#include <iostream>
#include "GraphWeb.h"
#include <fstream>
using namespace std;

int main()
{
	//-------------------------- 问题 1 -----------------------------

	GraphWeb G("data1.txt");

	G.Dijkstra();
	G.PrintShortest("out1.txt");
	


	//-------------------------- 问题 2 -----------------------------

	//能耗与距离^2成正比 则可能改变最短距离的路线
	//算法过程 先将邻接矩阵转换为存储能耗信息的矩阵 为使得总能耗最小使用Prim算法
	//原先不可达的点依然不可达

	G.Prim();
	G.PrintLowE("out2.txt");

	system("pause");

	return 0;
}