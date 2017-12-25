//ADT Graph
//邻接表存储

#include <iostream>
#include "ALGraph.h"
using namespace std;

void PrintVexset(ALGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
		cout << G.vexset[i].vex << '\n';
}

void PrintEdge(ALGraph G)
{
	EdgeNode *p;
	for (int i = 0; i < G.vexnum; i++)
	{
		p = G.vexset[i].firstedge;
		while (p)
		{
			cout << p->adjvex << '\t' << p->weight<<'\t';
			p = p->nextedge;
		}
		cout << '\n';
	}
}

int main()
{
	ALGraph G;
	InitALGraph(G);
	CreatALGraph(G);


	CriticalPath(G);


	DestroyALGraph(G);

	system("pause");

	return 0;
}