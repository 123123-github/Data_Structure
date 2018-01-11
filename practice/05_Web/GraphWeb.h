// 无限传感网络

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
	int vexnum;										// 顶点数
	int** mat;										// 图的邻接矩阵
	Point *position;								// 点的坐标
	int *D;											// 记录最大距离
	int *P;											// 记录路径
	int **Emat;										// 存储能耗信息的矩阵

public:
	GraphWeb(const char* filename = "data.txt");
	~GraphWeb();

public:
	void PrintGraph();
	void Dijkstra(int v0 = 0);						// 计算从源到各点的最短距离
	void PrintShortest(const char* filename = "out1.txt");
	void Prim();
	void PrintLowE(const char* filename = "out2.txt");
};

void WritePoint(int num, const char * filename);