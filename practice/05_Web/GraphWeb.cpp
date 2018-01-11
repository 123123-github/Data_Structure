#include <fstream>
#include "GraphWeb.h"
#include <iostream>
using namespace std;


GraphWeb::GraphWeb(const char * filename)
{
	ifstream in;

	in.open(filename);
	if (in.fail())
	{
		cout << "�ļ���ʧ��\n";
		return;
	}

	in >> vexnum;
	++vexnum;										// ���ϻ�۵�
	position = new Point[vexnum];					// �洢���������
	position[0] = { 0,0 };

	int temp;
	for (int i = 1; i <= vexnum - 1; i++)
		in >> temp >> position[i].x >> position[i].y;
	in.close();

	mat = new int*[vexnum];
	for (int i = 0; i < vexnum; i++)
		mat[i] = new int[vexnum];

	for (int i = 0;i < vexnum;++i)					// ������ڽӾ���
	{
		for (int j = i;j < vexnum;++j)
		{
			mat[i][j] = position[i].dis(position[j]);
			mat[j][i] = mat[i][j];
		}
	}

	for (int i = 0; i < vexnum; i++)				// ���� 10 �ı��Ϊ���ɴ�
		for (int j = i; j < vexnum; j++)
		{
			cout << mat[i][j] << '\n';				// --------����
			if (mat[i][j] > MAXDIS)
				mat[i][j] = mat[j][i] = INT32_MAX;
		}
	P = new int[vexnum];
	D = new int[vexnum];
	Emat = NULL;
}

GraphWeb::~GraphWeb()
{
	delete[] position;
	position = NULL;

	for (int i = 0; i < vexnum; i++)
		delete[] mat[i];
	delete mat;
	mat = NULL;

	delete P;
	P = NULL;

	delete D;
	D = NULL;

	if (Emat)
	{
		for (int i = 0; i < vexnum; i++)
			delete[] Emat[i];
		delete[] Emat;
		Emat = NULL;
	}
}

void GraphWeb::PrintGraph()
{
	for (int i = 0; i < vexnum; i++)
	{
		for (int j = 0; j < vexnum; j++)
		{
			cout << mat[i][j] << '\t';
		}
		cout << '\n';
	}
	cout << endl;
}

void GraphWeb::Dijkstra(int v0)
{
	bool *finished;
	finished = new bool[vexnum];

	for (int i = 0; i < vexnum; i++)							// ��ʼ�� P D finished
	{
		P[i] = v0;
		D[i] = mat[v0][i];
		finished[i] = false;
	}

	finished[v0] = true;
	for (int i = 0; i < vexnum; i++)
	{
		int v = 0;
		int min = INT32_MAX;										// !!! ����д�ڴ�ѭ���� !!!

		for (int w = 0; w < vexnum; w++)
		{
			if (!finished[w] && D[w] < min)
			{
				min = D[w];
				v = w;
			}
		}
		finished[v] = true;											// �ҵ���Сֵ�� �������� ��ʱ min ��ǵ��� min<v0,v>

		for (int w = 0; w < vexnum; w++)
		{
			if (!finished[w] && (D[w] > min + mat[v][w]))
			{
				if (min == INT32_MAX || mat[v][w] == INT32_MAX)		// ��������ж�����
					continue;
				else
				{
					D[w] = min + mat[v][w];							// ������̾���
					P[w] = v;											// �޸�·��
				}
			}
		}
	}

	delete[] finished;
}

void GraphWeb::PrintShortest(const char* filename)
{
	ofstream out;
	out.open(filename);
	if (out.fail())
	{
		cout << "�������� 1 ʧ��\n";
		return;
	}

	out << "---------------- ���ʱ�� -------------\n";
	for (int i = 1; i < vexnum; i++)					// ������ԭ��
	{
		out << "����:" << i << '\t' << "��̾���:\t";
		
		if (D[i] == INT32_MAX)
			out << "���ɴ�\n";
		else
			out << D[i] << '\n';

		out << '\n';
	}

	out << "---------------- ·�� -------------\n";
	for (int i = 1; i < vexnum; i++)
	{
		out << "����:" << i << '\t' << "����·��:\t";
		
		if (D[i] == INT32_MAX)
		{
			out << "���ɴ�\n";
			continue;
		}

		int j = i;	
		while (P[j]!=0)
		{
			out << j << '\t';
			j = P[j];
		}
		out << j << '\t'  << '0' << '\n';
	}

	out.close();
}

void GraphWeb::Prim()
{
	// 1.��ȡ�ܺľ���
	Emat = new int*[vexnum];
	for (int i = 0;i < vexnum;++i)
		Emat[i] = new int[vexnum];

	for (int i = 0; i < vexnum;++i)
	{
		for (int j = i; j < vexnum; ++j)
		{
			if (mat[i][j] == INT32_MAX)
				Emat[i][j] = Emat[j][i] = INT32_MAX;
			else
			{
				Emat[i][j] = mat[i][j] * mat[i][j];
				Emat[j][i] = Emat[i][j];
			}
		}
	}

	// 2.����С������
	bool* finished;
	finished = new bool[vexnum];
	for (int i = 0; i < vexnum; i++)
	{
		P[i] = 0;
		D[i] = Emat[0][i];
		finished[i] = false;
	}

	finished[0] = true;

	for (int i = 0; i < vexnum - 1; i++)
	{
		int min = INT32_MAX;
		int v = 0;
		for (int w = 0; w < vexnum; w++)					// �ҵ���Сֵ
			if (!finished[w] && D[w] < min)
			{
				min = D[w];
				v = w;
			}

		finished[v] = true;
		
		for (int w = 0; w < vexnum; w++)
			if (!finished[w] && D[w] > Emat[v][w])			// �޸�Ϊ���·��
			{
				D[w] = Emat[v][w];
				P[w] = v;
			}
	}

	delete[] finished;
}

void GraphWeb::PrintLowE(const char * filename)
{
	ofstream out;
	out.open(filename);
	if (out.fail())
	{
		cout << "�������� 2 ʧ��\n";
		return;
	}

	out << "---------------- ����ܺ� -------------\n";
	for (int i = 1; i < vexnum; i++)					// ������ԭ��
	{
		out << "����:" << i << '\t' << "����ܺ�:\t";

		if (D[i] == INT32_MAX)
			out << "���ɴ�\n";
		else
			out << D[i] << '\n';

		out << '\n';
	}

	out << "---------------- ·�� -------------\n";
	for (int i = 1; i < vexnum; i++)
	{
		out << "����:" << i << '\t' << "����·��:\t";

		if (D[i] == INT32_MAX)
		{
			out << "���ɴ�\n";
			continue;
		}

		int j = i;
		while (P[j] != 0)
		{
			out << j << '\t';
			j = P[j];
		}
		out << j << '\t' << '0' << '\n';
	}

	out.close();
}

double Point::dis(Point p)
{
	double d;
	int d1, d2;

	d1 = (p.x - x)*(p.x - x);
	d2 = (p.y - y)*(p.y - y);
	d = sqrt(d1 + d2);

	return d;
}

void WritePoint(int num, const char * filename)
{
	int x;
	int y;

	ofstream out;
	out.open(filename);
	if (out.fail())
	{
		cout << "����������ʧ��";
		return;
	}

	out << num << '\n';
	for (int i = 1;i <= num;++i)
	{
		x = rand() % 101 - 50;						// ���귶Χ �� -50~50  ֮��
		y = rand() % 101 - 50;
		
		out << i << '\t';
		out << x << '\t' << y << '\n';
	}

	out.close();
}
