#include "Maze.h"
#include <iostream>
#include <fstream>
#include "Status.h"
using namespace std;

//------------------- 迷宫类基本函数实现 --------------------

Maze::Maze()
{
	row = 0;
	col = 0;
	maze = NULL;

	start = { 0,0 };		// 在此处设置起点终点默认值
	end = { 0,0 };

	size = 0;
	step = 0;
	curpos = { 0,0 };
	mark = NULL;
	footpoint = NULL;
}

Maze::~Maze()
{
	for (int i = 0; i < row; i++)
		delete[] maze[i];
	delete[] maze;
	maze = NULL;

	delete[] mark;
	mark = NULL;

	delete[] footpoint;
	footpoint = NULL;

	row = 0;
	col = 0;
	start = { 0,0 };
	end = { 0,0 };
	size = 0;
}


//------------- 迷宫生成 --------------

Status Maze::FileCreatMaze(const char* filename)
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

	//----- 申请空间 -----

	footpoint = new Point[size];
	mark = new Point[size];

	return OK;
}

void Maze::SetStart(Point p)
{
	start.m = p.m;
	start.n = p.n;
}

void Maze::SetEnd(Point p)
{
	end.m = p.m;
	end.n = p.n;
}


//------------- 迷宫求解 --------------

bool Maze::Pass(Point p)
{
	if (maze[p.m][p.n] == false)				// 地图上该点不通
		return false;

	Point q;			// 已经探索过的点
	for (int i = 0; i < step; i++)				// 遍历之前走过的点
	{
		q = footpoint[i];

		if (q == p)			// 已在足迹
			return false;
	}

	return true;								// 地图上可通 且 不在足迹中
}

void Maze::FootPoint(Point p)
{
	footpoint[step] = p;
}

void Maze::Mark(Point p)
{
	static int i = 0;

	mark[i] = p;
	++i;
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

Status Maze::FindMazePath()
{
	mazepath e;

	step = 0;
	curpos = start;

	do
	{
		if (Pass(curpos))													// 当前点  还没有到过 且 可通
		{
			FootPoint(curpos);			// 留下足迹
			++step;						// 足迹数 + 1

			e = { step,curpos,1 };		// 第一次探索的方向为 1 
			S.Push(e);

			if (curpos.m == end.m && curpos.n == end.n)						// 到达终点
				return OK;
			else
				curpos = NextPos(curpos, 1);
			
		}
		else																// 当前点 不通 或 已经在路径上 需要修改上一个点的方向值
		{
			if (!S.Empty())				// 当前已走路径不为空时
			{
				e = S.Pop();

				while (!S.Empty() && e.di == 4)
				{
					Mark(e.pos);		// 标记死胡同
					e = S.Pop();
				}

				if (e.di < 4)
				{
					++e.di;
					S.Push(e);
					curpos = NextPos(e.pos, e.di);
				}
			}
		}
	} while (!S.Empty());

	return FALSE;
}

Status Maze::FindPath_DFS()
{
	bool* visited;
	int pos;					// 路径块的一维位置

	curpos = start;
	pos = curpos.position(row, col);

	if (Pass(curpos))






	return Status();
}


//------------- 输出 --------------

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
	     
	int num = 0;							// 不含死胡同的步数
	Point *path;
	mazepath e;
	path = new Point[step];

	Stack<mazepath> S2(S);
	while (!S2.Empty())
	{
		e = S2.Pop();

		path[num] = e.pos;
		++num;
	}

	int x, y;
	for (int i = 0; i < num; i++)
	{
		x = path[i].m;
		y = path[i].n;

		++mat[x][y];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mat[i][j] == 2)
				cout << "★";
			else if (mat[i][j] == 1)
				cout << "□";
			else
				cout << "■";
		}
		cout << '\n';
	}
	cout << endl;

	delete path;

	for (int i = 0; i < row; i++)
		delete[] mat[i];
	delete mat;
	mat = NULL;
}

bool Point::operator==(Point & p)
{
	if (this->m == p.m && this->n == p.n)
		return true;
	else
		return false;
}

inline int Point::position(int row, int col)
{
	return m * row + n * col;
}


