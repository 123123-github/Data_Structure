#include "Maze.h"
#include <stack>
#include <queue>
#include <fstream>
#include <iostream>
using namespace std;

//------------------ 迷宫基本元素定义 -------------------

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


//-------------------- 迷宫类定义 -----------------------

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
		cout << "不能打开文件:" << filename << '\n';
		return FALSE;
	}

	// 读入数据
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

	//-------- 申请空间 ---------

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
	case 1:				// 右
		++p.n;
		break;
	case 2:				// 下
		++p.m;
		break;
	case 3:				// 左
		--p.n;
		break;
	case 4:				// 上
		--p.m;
		break;
	default:			// 不应该出现的情况
		p.m = 0;
		p.n = 0;
		break;
	}

	return p;
}

Status Maze::DFS_Search()
{
	stack<Point> S;
	Point p;			// 点坐标
	int pos;			// 一维位置

	p = start;
	pos = p.pos(row, col);

	for (int i = 0; i < size; i++)					// 初始化 访问列表 及 路径
	{
		visited[i] = false;
		P[i] = pos;
	}
	
	// 起点入栈
	if (!visited[pos] && maze[p.m][p.n] == 1)		// 未被访问 且 可以通过
	{
		S.push(p);
		visited[pos] = true;

		if (p == end)
			return OK;
	}

	Point k;			// p 的相邻点
	int kpos;

	// 深度优先搜索
	while (!S.empty())
	{
		p = S.top();
		S.pop();
		pos = p.pos(row, col);

		for (int di = 1; di <= 4; di++)				// 相邻点依次入栈
		{
			k = NextPos(p, di);
			kpos = k.pos(row, col);

			if (!visited[kpos] && maze[k.m][k.n] == 1)			// 省略了是否在地图范围内的判断
			{
				S.push(k);

				visited[kpos] = true;
				P[kpos] = pos;						// 标记路径来源

				if (k == end)						// 一旦遇到终点即可停止搜索
					return OK;
			}
		}
	}

	return FALSE;
}

Status Maze::BFS_Search()
{
	queue<Point> Q;
	Point p;			// 点坐标
	int pos;			// 一维位置

	p = start;
	pos = p.pos(row, col);

	for (int i = 0; i < size; i++)					// 初始化 访问列表 及 路径
	{
		visited[i] = false;
		P[i] = pos;
	}

	// 起点入队
	if (!visited[pos] && maze[p.m][p.n] == 1)		// 未被访问 且 可以通过
	{
		Q.push(p);
		visited[pos] = true;

		if (p == end)
			return OK;
	}

	Point k;			// p 的相邻点
	int kpos;

	// 广度优先搜索
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		pos = p.pos(row, col);

		for (int di = 1; di <= 4; di++)				// 相邻点依次入队
		{
			k = NextPos(p, di);
			kpos = k.pos(row, col);

			if (!visited[kpos] && maze[k.m][k.n] == 1)			// 省略了是否在地图范围内的判断
			{
				Q.push(k);

				visited[kpos] = true;
				P[kpos] = pos;						// 标记路径来源

				if (k == end)						// 一旦遇到终点即可停止搜索
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
				cout << "□";
			else
				cout << "■";
		}
		cout << '\n';
	}
	cout << endl;
}

void Maze::PrintPath()
{
	int **mat;								// 复制原迷宫图
	mat = new int*[row];
	for (int i = 0; i < row; i++)
		mat[i] = new int[col];
	for (int i = 0;i < row;++i)
		for (int j = 0;j < col;++j)
			mat[i][j] = maze[i][j];

	//---------- 根据 P 获得路径 ----------

	int start_pos, end_pos;
	start_pos = start.pos(row, col);
	end_pos = end.pos(row, col);

	int num = 0;
	int *path;
	path = new int[size];

	for (int i = end_pos; i != start_pos; i = P[i])		// 计算获得路径
	{
		path[num] = i;
		++num;
	}
	path[num++] = start_pos;

	//---------- 在地图上标记 ---------

	int m, n, p;
	for (int i = 0; i < num; i++)
	{
		p = path[i];
		m = p / col;
		n = p - m * col;

		++mat[m][n];
	}

	//--------- 输出路线 ---------

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mat[i][j] == 1)
				cout << "□";
			else if (mat[i][j] == 0)
				cout << "■";
			else
				cout << "★";
		}
		cout << '\n';
	}
	cout << endl;

	//----------- 释放空间 -----------

	delete path;
	path = NULL;

	for (int i = 0; i < row; i++)
		delete[] mat[i];
	delete mat;
	mat = NULL;
}

