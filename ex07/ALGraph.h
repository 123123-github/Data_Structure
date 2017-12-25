#pragma once
#include "Status.h"
#include "Stack.h"
//ADT Graph 邻接表结构存储

//---------------- 邻接表结构的图定义 --------------

#define INITSIZE 10

typedef int VexType;

struct EdgeNode
{
	int adjvex;						//邻接点的位序
	int weight;						//边的权值
	EdgeNode* nextedge;
};

struct VNode
{
	VexType vex;					//存储顶点名称等信息
	EdgeNode* firstedge;			//第一条邻接表(关联的是第一个邻接点)
};

struct ALGraph
{
	int vexnum;
	int edgenum;
	VNode *vexset;
};

Status InitVexset(VNode* &vexset, int size = INITSIZE);

Status MakeENode(EdgeNode* &s, int v, int weight);

//----------------- 图的基本操作 -------------------

Status InitALGraph(ALGraph &G, int size = INITSIZE);		//不支持扩展大小

Status DestroyALGraph(ALGraph &G);

Status CreatALGraph(ALGraph &G);

int LocateVex(ALGraph G, VexType v);

int FirstAdj(ALGraph G, int v);

int NextAdj(ALGraph G, int v, int w);		// v 相对于 w 之后的邻接点


//--------------- 关键路径 ---------------

void FindInDegree(ALGraph G, int *indegree);

Status TopologicalSort(ALGraph G);										//对 G 进行拓扑排序

Status TopologicalOrder(ALGraph G, Stack<int> &S, int *&ve);			//求拓扑排序，通过栈 S 返回拓扑逆序，同时求得 ve ，关键路径函数调用

Status CriticalPath(ALGraph G);											//求 G 的关键路径


