#include "MGraph.h"
//ADT Graph ͼ���ڽӾ���洢
//C++ �ṹ��
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
			mat[i][j] = INT16_MAX;			//������������жϲ���������ʹ�� short �� max �ɴ�Լ��Ϊ������
	for (int i = 0; i < size; i++)
		mat[i][i] = 0;

	return OK;
}

//----------------��������-----------------

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
	cout << "�����붥�����ͱ���:\n";
	cin >> G.vexnum >> G.edgenum;

	InitVexset(G.vexset, G.vexnum);
	InitMat(G.mat, G.vexnum);

	/*�����ڴ˴�������߼��ĺ�������Ϊ 0~G.vexnum-1 */		//��ʼ���߼�
	for (int i = 0;i < G.vexnum;++i)							//��ʼ����
		G.vexset[i] = i;

	cout << "������ͼ������,�����������������ֱ�Ϊ0��1\n";
	int graphType;
	cin >> graphType;

	cout << "����������ߵ��������㼰�ߵ�Ȩֵ\n";
	int v, w, value;
	if (graphType == 0)		//����
	{
		for (int i = 0; i < G.edgenum; i++)
		{
			cin >> v >> w >> value;
			G.mat[w][v] = G.mat[v][w] = value;
		}
	}
	else					//����
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

//---------------- ���·�� ---------------

void ShortestPath_DIJ(MGraph G, int v0, int* &P, int* &D)
{
	bool* finished;
	finished = new bool[G.vexnum];

	for (int v = 0; v < G.vexnum; v++)				//��ʼ��P��D��finished
	{
		P[v] = v0;
		D[v] = G.mat[v0][v];
		finished[v] = false;
	}
	finished[v0] = true;
	for (int i = 1; i < G.vexnum; i++)				//�ҵ�������ڽӵ���µ���̾���
	{
		int min = INT16_MAX, v;

		for (int w = 0; w < G.vexnum; w++)
			if (!finished[w] && D[w] < min)
			{
				min = D[w];
				v = w;
			}

		finished[v] = true;
		
		for (int w = 0; w < G.vexnum; w++)			//�޸�·��
			if (!finished[w] && (D[w] > G.mat[v][w] + min))			//ʹ�� INT32_MAX �ڴ˴�������������½������
			{
				D[w] = G.mat[v][w] + min;
				P[w] = v;							//�޸ı��޸���̾���ĵ��·����Դ
			}
	}

	delete[] finished;
}

void ShortestPath_FLOYD(MGraph G, int **& D)
{
	int N = G.vexnum;

	for (int v = 0;v < N;v++)				//��ʼ������
		for (int w = 0;w < N;w++)
			D[v][w] = G.mat[v][w];

	for (int u = 0; u < N; u++)				//������̾���
		for (int v = 0; v < N; v++)
			for (int w = 0; w < N; w++)
				if (D[v][u] + D[u][w] < D[v][w])
				{
					D[v][w] = D[v][u] + D[u][w];
					if (D[v][w] > INT16_MAX)
						D[v][w] = INT16_MAX;		//��ֹ���
				}
}
