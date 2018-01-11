// ���޴�������

#pragma once

#define MAXDIS 10

struct Point
{
	int x;
	int y;

	double dis(Point p);
};

class GraphWeb
{
private:
	int vexnum;										// ������
	int** mat;										// ͼ���ڽӾ���
	Point *position;								// �������
	int *D;											// ��¼������
	int *P;											// ��¼·��
	int **Emat;										// �洢�ܺ���Ϣ�ľ���

public:
	GraphWeb(const char* filename = "data.txt");
	~GraphWeb();

public:
	void PrintGraph();
	void Dijkstra(int v0 = 0);						// �����Դ���������̾���
	void PrintShortest(const char* filename = "out1.txt");
	void Prim();
	void PrintLowE(const char* filename = "out2.txt");
};

void WritePoint(int num, const char * filename);