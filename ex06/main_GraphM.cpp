#include <iostream>
#include "GraphM.h"
using namespace std;



int main()
{
	GraphM G;
	InitGraphM(G);

	CreatGraphM(G);

	PrintGraphMat(G);

	BFSTraverse(G);
	

	DestroyGraphM(G);

	system("pause");

	return 0;
}