#include "Maze.h"
#include <stack>
#include <queue>
#include <fstream>
#include <iostream>
using namespace std;

//------------------ �Թ�����Ԫ�ض��� -------------------

int Point::pos(int row, int col)
{
	return 	(m*col + n);
}

bool Point::operator==(const Point & p)
{
	if (m == p.m && n == p.n)
		return true;
	else
		return false;
}


//-------------------- �Թ��ඨ�� -----------------------

Maze::Maze()
{
	maze = NULL;
	row = 0;
	col = 0;
	size = 0;

	start = { 0,0 };
	end = { 0,0 };

	P = NULL;
	visited = NULL;
}

Maze::~Maze()
{
	for (int i = 0;i < row;++i)
		delete[] maze[i];
	delete[] maze;
	maze = NULL;

	row = 0;
	col = 0;
	size = 0;

	start = { 0,0 };
	end = { 0,0 };

	delete P;
	P = NULL;

	delete visited;
	visited = NULL;
}


Status Maze::FileCreatMaze(const char * filename)
{
	ifstream in;

	in.open(filename);
	if (in.fail())
	{
		cout << "���ܴ��ļ�:" << filename << '\n';
		return FALSE;
	}

	// ��������
	in >> row >> col;
	size = row * col;

	maze = new bool*[row];
	if (!maze)
		return ERROR;
	for (int i = 0; i < row; i++)
		maze[i] = new bool[col];

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			in >> maze[i][j];

	in.close();

	//-------- ����ռ� ---------

	visited = new bool[size];
	P = new int[size];

	return OK;
}

void Maze::SetStart(Point p)
{
	start = p;
}

void Maze::SetEnd(Point p)
{
	end = p;
}


Point Maze::NextPos(Point p, int di)
{
	switch (di)
	{
	case 1:				// ��
		++p.n;
		break;
	case 2:				// ��
		++p.m;
		break;
	case 3:				// ��
		--p.n;
		break;
	case 4:				// ��
		--p.m;
		break;
	default:			// ��Ӧ�ó��ֵ����
		p.m = 0;
		p.n = 0;
		break;
	}

	return p;
}

Status Maze::DFS_Search()
{
	stack<Point> S;
	Point p;			// ������
	int pos;			// һάλ��

	p = start;
	pos = p.pos(row, col);

	for (int i = 0; i < size; i++)					// ��ʼ�� �����б� �� ·��
	{
		visited[i] = false;
		P[i] = pos;
	}
	
	// �����ջ
	if (!visited[pos] && maze[p.m][p.n] == 1)		// δ������ �� ����ͨ��
	{
		S.push(p);
		visited[pos] = true;

		if (p == end)
			return OK;
	}

	Point k;			// p �����ڵ�
	int kpos;

	// �����������
	while (!S.empty())
	{
		p = S.top();
		S.pop();
		pos = p.pos(row, col);

		for (int di = 1; di <= 4; di++)				// ���ڵ�������ջ
		{
			k = NextPos(p, di);
			kpos = k.pos(row, col);

			if (!visited[kpos] && maze[k.m][k.n] == 1)			// ʡ�����Ƿ��ڵ�ͼ��Χ�ڵ��ж�
			{
				S.push(k);

				visited[kpos] = true;
				P[kpos] = pos;						// ���·����Դ

				if (k == end)						// һ�������յ㼴��ֹͣ����
					return OK;
			}
		}
	}

	return FALSE;
}

Status Maze::BFS_Search()
{
	queue<Point> Q;
	Point p;			// ������
	int pos;			// һάλ��

	p = start;
	pos = p.pos(row, col);

	for (int i = 0; i < size; i++)					// ��ʼ�� �����б� �� ·��
	{
		visited[i] = false;
		P[i] = pos;
	}

	// ������
	if (!visited[pos] && maze[p.m][p.n] == 1)		// δ������ �� ����ͨ��
	{
		Q.push(p);
		visited[pos] = true;

		if (p == end)
			return OK;
	}

	Point k;			// p �����ڵ�
	int kpos;

	// �����������
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		pos = p.pos(row, col);

		for (int di = 1; di <= 4; di++)				// ���ڵ��������
		{
			k = NextPos(p, di);
			kpos = k.pos(row, col);

			if (!visited[kpos] && maze[k.m][k.n] == 1)			// ʡ�����Ƿ��ڵ�ͼ��Χ�ڵ��ж�
			{
				Q.push(k);

				visited[kpos] = true;
				P[kpos] = pos;						// ���·����Դ

				if (k == end)						// һ�������յ㼴��ֹͣ����
					return OK;
			}
		}
	}

	return FALSE;
}

void Maze::PrintMazeMap()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (maze[i][j])
				cout << "��";
			else
				cout << "��";
		}
		cout << '\n';
	}
	cout << endl;
}

void Maze::PrintPath()
{
	int **mat;								// ����ԭ�Թ�ͼ
	mat = new int*[row];
	for (int i = 0; i < row; i++)
		mat[i] = new int[col];
	for (int i = 0;i < row;++i)
		for (int j = 0;j < col;++j)
			mat[i][j] = maze[i][j];

	//---------- ���� P ���·�� ----------

	int start_pos, end_pos;
	start_pos = start.pos(row, col);
	end_pos = end.pos(row, col);

	int num = 0;
	int *path;
	path = new int[size];

	for (int i = end_pos; i != start_pos; i = P[i])		// ������·��
	{
		path[num] = i;
		++num;
	}
	path[num++] = start_pos;

	//---------- �ڵ�ͼ�ϱ�� ---------

	int m, n, p;
	for (int i = 0; i < num; i++)
	{
		p = path[i];
		m = p / col;
		n = p - m * col;

		++mat[m][n];
	}

	//--------- ���·�� ---------

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mat[i][j] == 1)
				cout << "��";
			else if (mat[i][j] == 0)
				cout << "��";
			else
				cout << "��";
		}
		cout << '\n';
	}
	cout << endl;

	//----------- �ͷſռ� -----------

	delete path;
	path = NULL;

	for (int i = 0; i < row; i++)
		delete[] mat[i];
	delete mat;
	mat = NULL;
}

