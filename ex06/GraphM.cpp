#include <iostream>
#include <string.h>
#include "GraphM.h"
using namespace std;

//----------------基本元素空间分配---------------

//-----顶点集向量-----

Status VexInit(VertexType  &vertex)			//初始化顶点向量组
{
	vertex.elem = new VertexElemType[VEX_INIT_NUM + 1];	//vertex[0]不使用
	if (!vertex.elem)
		return ERROR;

	vertex.vexsize = VEX_INIT_NUM;

	return OK;
}

Status VexDestroy(VertexType &vertex)		//销毁顶点集向量组
{
	delete[] vertex.elem;
	vertex.elem = NULL;

	vertex.vexsize = -1;

	return OK;
}

//------邻接矩阵------

Status AdjMatInit(AdjMat &mat)				//初始化图的邻接矩阵
{
	mat.elem = new AdjMatElem*[MAT_INIT_SIZE + 1];	//数组 0 空间不使用 
	if (!mat.elem)
		return ERROR;
	for (int i = 0; i <= MAT_INIT_SIZE; i++)
	{
		mat.elem[i] = new AdjMatElem[MAT_INIT_SIZE + 1];
		if (!mat.elem[i])
			return ERROR;
	}
	//得到了大小为 (MAT_INIT_SIZE + 1) × (MAT_INIT_SIZE + 1) 的二维矩阵

	mat.size = MAT_INIT_SIZE;

	for (int i = 0; i <= MAT_INIT_SIZE; i++)
	{
		for (int j = 0; j <= MAT_INIT_SIZE; j++)
		{
			mat.elem[i][j] = { 0,NULL };
		}
	}

	return OK;
}

Status AdjMatDestroy(AdjMat &mat)			//销毁图的邻接矩阵
{
	for (int i = 0; i <= mat.size; i++)
	{
		delete[] mat.elem[i];

	}
	delete[] mat.elem;
	mat.elem = NULL;

	mat.size = -1;

	return OK;
}


//-----------------------GraphM 基本操作----------------------

Status InitGraphM(GraphM & G)
{
	G.kind = UNDEFINE;
	G.vexnum = 0;
	G.edgenum = 0;
	VexInit(G.vex);
	AdjMatInit(G.mat);

	return OK;
}

Status DestroyGraphM(GraphM & G)
{
	G.kind = UNDEFINE;
	G.vexnum = -1;
	G.edgenum = -1;

	VexDestroy(G.vex);
	AdjMatDestroy(G.mat);

	return OK;
}

int LocateVex(GraphM G, VertexElemType v)
{
	VertexElemType *vex = G.vex.elem;
	for (int i = 1; i <= G.vexnum; i++)
	{
		if (strcmp(vex[i], v) == 0)
			return i;
	}

	return 0;
}

Status CreatGraphM(GraphM & G)		//依据图的类型创建图
{
	cout << "请输入图的类型:\n无向图，有向图，无向网，有向网分别为 1 2 3 4\n";
	int kind;
	cin >> kind;
	G.kind = GraphKind(kind);
	
	switch (G.kind)
	{
	case UNDEFINE:
		return ERROR;
	case UDG:
	{
		CreatUDG(G);
		return OK;
	}
	case DG:
	{
		CreatDG(G);
		return OK;
	}
	case UDN:
	{
		CreatUDN(G);
		return OK;
	}
	case DN:
	{
		CreatDN(G);
		return OK;
	}
	default:
		break;
	}
	return OK;
}

Status CreatUDG(GraphM &G)		//无向图
{
	cout << "请输入图的顶点数及边数:\n";
	cin >> G.vexnum >> G.edgenum;

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		/*判断空间是否已满*/
		//若满则需扩大顶点集及邻接矩阵的空间
		cin >> G.vex.elem[i];
	}

	cout << "请输入每条边的两端顶点\n";		//创建邻接矩阵
	VertexElemType v1, v2;
	int i, j;
	for (int k = 1; k <= G.edgenum; k++)
	{
		cin >> v1 >> v2;

		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.mat.elem[i][j].adj = 1;
		G.mat.elem[j][i].adj = 1;
	}

	return OK;
}
Status CreatDG(GraphM & G)		//有向图
{
	cout << "请输入图的顶点数及边数:\n";
	cin >> G.vexnum >> G.edgenum;

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		/*判断空间是否已满*/
		//若满则需扩大顶点集及邻接矩阵的空间
		cin >> G.vex.elem[i];
	}

	cout << "请输入边的两端顶点，及边的权值\n";		//创建邻接矩阵
	VertexElemType v1, v2;
	int i, j;
	for (int k = 1; k <= G.edgenum; k++)
	{
		cin >> v1 >> v2;

		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.mat.elem[i][j].adj = 1;
	}

	return OK;
}
Status CreatUDN(GraphM & G)		//无向网
{
	cout << "请输入图的顶点数及边数:\n";
	cin >> G.vexnum >> G.edgenum;

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		/*判断空间是否已满*/
		//若满则需扩大顶点集及邻接矩阵的空间
		cin >> G.vex.elem[i];
	}

	cout << "请输入边的两端顶点，及边的权值\n";		//创建邻接矩阵
	VertexElemType v1, v2;
	VRType w;
	int i, j;
	for (int k = 1; k <= G.edgenum; k++)
	{
		cin >> v1 >> v2 >> w;

		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.mat.elem[i][j].adj = w;
		G.mat.elem[j][i].adj = w;
	}

	return OK;
}
Status CreatDN(GraphM & G)		//有向网
{
	cout << "请输入图的顶点数及边数:\n";
	cin >> G.vexnum >> G.edgenum;

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		/*判断空间是否已满*/
		//若满则需扩大顶点集及邻接矩阵的空间
		cin >> G.vex.elem[i];
	}

	cout << "请输入边的两端顶点，及边的权值\n";		//创建邻接矩阵
	VertexElemType v1, v2;
	VRType w;
	int i, j;
	for (int k = 1; k <= G.edgenum; k++)
	{
		cin >> v1 >> v2 >> w;

		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.mat.elem[i][j].adj = w;
	}

	return OK;
}

