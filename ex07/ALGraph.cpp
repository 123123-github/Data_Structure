#include "ALGraph.h"
#include <iostream>
#include "Stack.h"
#include "Queue.h"
using namespace std;

//---------------- 邻接表结构的图定义 --------------

Status InitVexset(VNode *& vexset, int size)
{
	vexset = new VNode[size];
	if (!vexset)
		return ERROR;

	for (int i = 0; i < size; i++)
	{
		vexset[i].firstedge = NULL;
		vexset[i].vex = i;				/*此处可增加函数，输入顶点名等信息，此省略*/
	}

	return OK;
}

Status MakeENode(EdgeNode* & s, int v, int weight)
{
	s = new EdgeNode;
	if (!s)
		return ERROR;

	s->adjvex = v;
	s->weight = weight;
	s->nextedge = NULL;

	return OK;
}


//----------------- 图的基本操作 -------------------

Status InitALGraph(ALGraph & G, int size)
{
	G.vexnum = 0;
	G.edgenum = 0;
	G.vexset = NULL;

	return OK;
}

Status DestroyALGraph(ALGraph & G)
{
	EdgeNode *p, *q;
	for (int i = 0; i < G.vexnum; i++)
	{
		p = q = G.vexset[i].firstedge;
		while (p)
		{
			q = q->nextedge;
			delete p;
			p = q;
		}
	}

	delete[] G.vexset;
	G.vexnum = -1;
	G.edgenum = -1;

	return OK;
}

Status CreatALGraph(ALGraph & G)
{
	cout << "请输入图的顶点数及边数\n";
	cin >> G.vexnum >> G.edgenum;

	if (!InitVexset(G.vexset, G.vexnum))
		return ERROR;

	cout << "请输入图的类型，无向网，有向网分别为 0，1\n";
	int type;
	cin >> type;

	cout << "请分别输入边的两端及权值\n";
	int v, w, weight;
	EdgeNode *s, *p;

	if (type == 0)		//无向
	{
		for (int i = 0; i < G.edgenum; i++)
		{
			cin >> v >> w >> weight;

			p = G.vexset[v].firstedge;
			MakeENode(s, w, weight);
			if (!p)
			{
				G.vexset[v].firstedge = s;
			}
			else
			{
				while (p->nextedge)
					p = p->nextedge;
				p->nextedge = s;
			}
			
			p = G.vexset[w].firstedge;
			MakeENode(s, v, weight);
			if (!p)
			{
				G.vexset[w].firstedge = s;
			}
			else
			{
				while (p->nextedge)
					p = p->nextedge;
				p->nextedge = s;
			}
		}
	}
	else			//有向
	{
		for (int i = 0; i < G.edgenum; i++)
		{
			cin >> v >> w >> weight;

			p = G.vexset[v].firstedge;
			MakeENode(s, w, weight);
			if (!p)
			{
				G.vexset[v].firstedge = s;
			}
			else
			{
				while (p->nextedge)
					p = p->nextedge;
				p->nextedge = s;
			}
		}
	}

	return OK;
}

int LocateVex(ALGraph G, VexType v)
{
	for (int i = 0; i < G.vexnum; i++)
		if (G.vexset[i].vex == v)
			return i;

	return -1;
}

int FirstAdj(ALGraph G, int v)
{
	EdgeNode* p;
	p = G.vexset[v].firstedge;

	if (!p)
		return -1;
	else
		return p->adjvex;
}

int NextAdj(ALGraph G, int v, int w)
{
	EdgeNode *p;
	p = G.vexset[v].firstedge;

	if (!p)
		return -1;
	else
	{
		while (p->nextedge && (p->adjvex != w))
			p = p->nextedge;

		if (p->nextedge)
			return p->nextedge->adjvex;
		else
			return -1;
	}
}


//--------------- 关键路径 ---------------

void FindInDegree(ALGraph G, int * indegree)
{
	EdgeNode *p;
	int k;									// k 记录邻接点
	
	for (int i = 0; i < G.vexnum; i++)		//!!!先将 indegree 初始化为 0
		indegree[i] = 0;

	for (int i = 0; i < G.vexnum; i++)		//对 n 个顶点遍历查找入度
	{
		for (p = G.vexset[i].firstedge;p; p = p->nextedge)
		{
			k = p->adjvex;
			++indegree[k];
		}
	}
}

Status TopologicalSort(ALGraph G)
{
	Queue<int> Q;
	int *indegree;
	int count = 0;

	indegree = new int[G.vexnum];
	FindInDegree(G, indegree);				//初始化入度

	for (int i = 0; i < G.vexnum; i++)		//入度为 0 进队
		if (!indegree[i])
			Q.Push(i);

	int j, k;								// j 为当前顶点， k 为 j 的邻接点
	EdgeNode* p;
	while (!Q.Empty())
	{
		j = Q.Pop();
		count++;
		cout << j << '\t';
		
		for (p = G.vexset[j].firstedge;p;p = p->nextedge)
		{
			k = p->adjvex;					// j 的邻接点入度 - 1 ，减至 0 的入队
			if (!(--indegree[k]))
				Q.Push(k);
		}
		/*
		for (k = FirstAdj(G, j); k >= 0; k = NextAdj(G, j, k))
			if (!(--indegree[k]))
				Q.Push(k);
		*/
	}

	delete[] indegree;

	if (count != G.vexnum)		//存在环
		return ERROR;
	else
		return OK;
}

Status TopologicalOrder(ALGraph G, Stack<int> &S, int *&ve)
{
	Queue<int> Q;
	int *indegree;
	int count = 0;

	indegree = new int[G.vexnum];
	for (int i = 0; i < G.vexnum; i++)	//初始化入度及最早发生时间
		indegree[i] = ve[i] = 0;

	FindInDegree(G, indegree);											//1.确定顶点入度

	for (int i = 0;i < G.vexnum;i++)									//2.入度为 0 入队
		if (!indegree[i])
			Q.Push(i);

	int j, k, d;						//j:当前点  k:邻接点  d:距离
	EdgeNode *p;
	while (!Q.Empty())
	{
		j = Q.Pop();
		S.Push(j);
		count++;

		for (p = G.vexset[j].firstedge;p;p = p->nextedge)				//3.元素出队，相邻点入度 - 1,为 0 时入队
		{
			k = p->adjvex;
			d = p->weight;

			if (!(--indegree[k]))
				Q.Push(k);

			if (ve[k] < ve[j] + d)		//最早发生时间取最大
				ve[k] = ve[j] + d;
		}
	}

	delete[] indegree;

	if (count == G.vexnum)				// 全部在排序内，则无环
		return OK;
	else
		return ERROR;
}

Status CriticalPath(ALGraph G)
{
	Stack<int> S;
	int *ve, *vl, ee, el;
	int N = G.vexnum;

	ve = new int[N];
	vl = new int[N];

	if (!TopologicalOrder(G, S, ve))					//1. 获得拓扑逆序 和 ve 
		return ERROR;

	int last;
	S.GetTop(last);
	for (int i = 0; i < N; i++)							//2. 初始化 vl 
		vl[i] = ve[last];

	int j, k, d;
	EdgeNode *p;
	while (!S.Empty())									//3. 通过拓扑逆序计算 vl 
	{
		j = S.Pop();

		for (p = G.vexset[j].firstedge;p;p = p->nextedge)
		{
			k = p->adjvex;
			d = p->weight;

			if (vl[j] > vl[k] - d)			//最晚发生时间取最小
				vl[j] = vl[k] - d;
		}
	}

	char flag = '\0';						//标识关键路径
	for (j = 0; j < N; j++)							//4. 遍历每条边 计算 ee el
	{
		for (p = G.vexset[j].firstedge;p;p = p->nextedge)
		{
			k = p->adjvex;
			d = p->weight;

			ee = ve[j];
			el = vl[k] - d;

			flag = (ee == el) ? '*' : '\0';
			cout << j << "  " << k << '\t'
				<< "d=" << d << '\t'
				<< ee << "  " << el << ' ' << flag << '\n';
		}
	}

	delete[] ve;
	delete[] vl;

	return Status();
}
