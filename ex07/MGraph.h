//ADT Graph 图的邻接矩阵存储
//C++ 结构体

#pragma once
#include "Status.h"

//-------------- MGraph 结构 --------------

#define INITSIZE 10

typedef int VexType;

struct MGraph
{
	int vexnum;
	int edgenum;
	VexType* vexset;		//存放顶点名
	int** mat;				//邻接矩阵
};

Status InitVexset(VexType *&vexset, int size);

Status InitMat(int **&mat, int size);


//----------------基本操作-----------------

Status InitMGraph(MGraph &G);

Status DestroyMGraph(MGraph &G);

Status CreatMGraph(MGraph &G);

int LocateVex(MGraph &G, VexType v);		//返回 v 的位置

int FirstAdj(MGraph &G, int v);

int NextAdj(MGraph &G, int v, int w);

void PrintGraph(MGraph G);

//---------------- 最短路径 ---------------

void ShortestPath_DIJ(MGraph G, int v0, int* &P, int* &D);			//迪杰斯特拉算法 --- P返回路径，D返回 v0 到各顶点的最短距离

void ShortestPath_FLOYD(MGraph G, int** &D);						//弗洛伊德算法 --- 不记录路径