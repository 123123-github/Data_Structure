#include <iostream>
using namespace std;

void Prim(int **mat, int V, int* &P, int* &D)			//最小生成树算法
{
	bool* finished;
	finished = new bool[V + 1];
	for (int v = 1;v <= V;v++)				//初始化 P，D，finished
	{
		P[v] = 1;
		D[v] = mat[1][v];
		finished[v] = false;
	}
	
	finished[1] = true;

	for (int i = 2; i <= V; i++)
	{
		int min = INT16_MAX, v;
		for (int w = 1; w <= V; w++)
			if (!finished[w] && D[w] < min)
			{
				min = D[w];
				v = w;
			}
		finished[v] = true;
		for (int w = 1; w <= V; w++)
			if (!finished[w] && (D[w] > mat[v][w]))
			{
				D[w] = mat[v][w];
				P[w] = v;
			}
	}

	delete finished;
}

int main()
{
	int V, E;
	cin >> V >> E;						//输入顶点数及边数

	int **mat;
	mat = new int*[V + 1];				//初始化邻接矩阵
	for (int i = 0; i < V+1; i++)		
		mat[i] = new int[V + 1];
	for (int i = 0;i < V + 1;i++)
		for (int j = 0;j < V + 1;j++)
			mat[i][j] = INT16_MAX;
	for (int i = 0;i <= V;i++)
		mat[i][i] = 0;					//!!!邻接矩阵对角线为 0 ，与自身距离为 0 

	int i, j, value;					//生成邻接矩阵
	for (int e = 0; e < E; e++)
	{
		cin >> i >> j >> value;
		mat[i][j] = value;
		mat[j][i] = value;
	}

	int *P, *D;
	P = new int[V + 1];
	D = new int[V + 1];

	Prim(mat, V, P, D);

	int sum = 0;
	for (int i = 1; i <= V; i++)
		sum += mat[i][P[i]];

	cout << sum << endl;

	for (int i = 2; i <= V; i++)
		cout << "麦田" << i << "与麦田" << P[i] << '\n';



	delete[] P;
	delete[] D;

	system("pause");

	return 0;
}