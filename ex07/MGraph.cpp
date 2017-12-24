#include "MGraph.h"
//ADT Graph 图的邻接矩阵存储
//C++ 结构体
#include <iostream>
using namespace std;

Status InitVexset(VexType * &vexset, int size)
{
	vexset = new VexType[size];
	
	if (!vexset)
		return ERROR;
	else
		return OK;
}

Status InitMat(int ** &mat, int size)
{
	mat = new int*[size];
	if (!mat)
		return ERROR;

	for (int i = 0; i < size; i++)
		mat[i] = new int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mat[i][j] = INT16_MAX;			//会溢出，导致判断不正常，可使用 short 的 max 可大约认为是无穷
	for (int i = 0; i < size; i++)
		mat[i][i] = 0;

	return OK;
}

//----------------基本操作-----------------

Status InitMGraph(MGraph & G)
{
	G.edgenum = 0;
	G.vexnum = 0;
	G.vexset = NULL;
	G.mat = NULL;

	return OK;
}

Status DestroyMGraph(MGraph & G)
{
	for (int i = 0; i < G.vexnum; i++)
		delete G.mat[i];

	delete G.mat;
	G.mat = NULL;

	G.vexnum = -1;
	G.edgenum = -1;

	return OK;
}

Status CreatMGraph(MGraph & G)
{
	cout << "请输入顶点数和边数:\n";
	cin >> G.vexnum >> G.edgenum;

	InitVexset(G.vexset, G.vexnum);
	InitMat(G.mat, G.vexnum);

	/*可以在此创建输入边集的函数，简化为 0~G.vexnum-1 */		//初始化边集
	for (int i = 0;i < G.vexnum;++i)							//初始化边
		G.vexset[i] = i;

	cout << "请输入图的类型,无向网、有向网，分别为0，1\n";
	int graphType;
	cin >> graphType;

	cout << "请依次输入边的两个顶点及边的权值\n";
	int v, w, value;
	if (graphType == 0)		//无向
	{
		for (int i = 0; i < G.edgenum; i++)
		{
			cin >> v >> w >> value;
			G.mat[w][v] = G.mat[v][w] = value;
		}
	}
	else					//有向
	{
		for (int i = 0; i < G.edgenum; i++)
		{
			cin >> v >> w >> value;
			G.mat[v][w] = value;
		}
	}

	return OK;
}

int LocateVex(MGraph & G, VexType v)
{
	for (int i = 0; i < G.vexnum; i++)
		if (G.vexset[i] == v)
			return i;

	return -1;
}

int FirstAdj(MGraph & G, int v)
{
	for (int w = 0; w < G.vexnum; w++)
		if (G.mat[v][w] < INT16_MAX)
			return w;

	return -1;
}

int NextAdj(MGraph & G, int v, int w)
{
	for (int u = w; u < G.vexnum; u++)
		if (G.mat[v][w] < INT16_MAX)
			return u;

	return -1;
}

void PrintGraph(MGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
		cout << G.vexset[i] << '\t';
	cout << '\n' << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			cout << G.mat[i][j] << "\t";
		}
		cout << '\n';
	}
}

//---------------- 最短路径 ---------------

void ShortestPath_DIJ(MGraph G, int v0, int* &P, int* &D)
{
	bool* finished;
	finished = new bool[G.vexnum];

	for (int v = 0; v < G.vexnum; v++)				//初始化P，D，finished
	{
		P[v] = v0;
		D[v] = G.mat[v0][v];
		finished[v] = false;
	}
	finished[v0] = true;
	for (int i = 1; i < G.vexnum; i++)				//找到最近的邻接点和新的最短距离
	{
		int min = INT16_MAX, v;

		for (int w = 0; w < G.vexnum; w++)
			if (!finished[w] && D[w] < min)
			{
				min = D[w];
				v = w;
			}

		finished[v] = true;
		
		for (int w = 0; w < G.vexnum; w++)			//修改路径
			if (!finished[w] && (D[w] > G.mat[v][w] + min))			//使用 INT32_MAX 在此处可能溢出，导致结果错误
			{
				D[w] = G.mat[v][w] + min;
				P[w] = v;							//修改被修改最短距离的点的路径来源
			}
	}

	delete[] finished;
}

void ShortestPath_FLOYD(MGraph G, int **& D)
{
	int N = G.vexnum;

	for (int v = 0;v < N;v++)				//初始化距离
		for (int w = 0;w < N;w++)
			D[v][w] = G.mat[v][w];

	for (int u = 0; u < N; u++)				//计算最短距离
		for (int v = 0; v < N; v++)
			for (int w = 0; w < N; w++)
				if (D[v][u] + D[u][w] < D[v][w])
				{
					D[v][w] = D[v][u] + D[u][w];
					if (D[v][w] > INT16_MAX)
						D[v][w] = INT16_MAX;		//防止溢出
				}
}
