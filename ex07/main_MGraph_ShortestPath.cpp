#include <iostream>
#include "MGraph.h"
using namespace std;

int main()
{
	MGraph G;
	InitMGraph(G);

	CreatMGraph(G);

	PrintGraph(G);

	//------------------- FLOYD ----------------
	int  **D;
	D = new int*[G.vexnum];
	for (int i = 0; i < G.vexnum; i++)
	{
		D[i] = new int[G.vexnum];
	}
	ShortestPath_FLOYD(G, D);

	//------------------ DIJKSTRA --------------
	//int *P;
	//P = new int[G.vexnum];
	//ShortestPath_DIJ(G, 0, P, D);

	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
			cout << D[i][j] << '\t';
		cout << '\n';
	}
	DestroyMGraph(G);

	system("pause");

	return 0;
}