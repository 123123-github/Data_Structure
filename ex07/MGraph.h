//ADT Graph ͼ���ڽӾ���洢
//C++ �ṹ��

#pragma once
#include "Status.h"

//-------------- MGraph �ṹ --------------

#define INITSIZE 10

typedef int VexType;

struct MGraph
{
	int vexnum;
	int edgenum;
	VexType* vexset;		//��Ŷ�����
	int** mat;				//�ڽӾ���
};

Status InitVexset(VexType *&vexset, int size);

Status InitMat(int **&mat, int size);


//----------------��������-----------------

Status InitMGraph(MGraph &G);

Status DestroyMGraph(MGraph &G);

Status CreatMGraph(MGraph &G);

int LocateVex(MGraph &G, VexType v);		//���� v ��λ��

int FirstAdj(MGraph &G, int v);

int NextAdj(MGraph &G, int v, int w);

void PrintGraph(MGraph G);

//---------------- ���·�� ---------------

void ShortestPath_DIJ(MGraph G, int v0, int* &P, int* &D);			//�Ͻ�˹�����㷨 --- P����·����D���� v0 �����������̾���

void ShortestPath_FLOYD(MGraph G, int** &D);						//���������㷨 --- ����¼·��