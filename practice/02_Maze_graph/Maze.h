// 迷宫问题
// 深度搜索 广度搜索
#pragma once
#include "Status.h"

//------------------ 迷宫基本元素定义 -------------------

struct Point
{
	int m;
	int n;

	int pos(int row,int col);		// 返回一维位置
	bool operator==(const Point &p);
};


//-------------------- 迷宫类定义 -----------------------

class Maze
{
private:
	bool **maze;
	int row;
	int col;
	int size;
	Point start;
	Point end;
private:
	int *P;						// 记录搜索路径
	bool *visited;				// 是否已访问
private:
	Point NextPos(Point p, int di);

public:
	Maze();
	~Maze();
public:
	Status FileCreatMaze(const char* filename);
	void SetStart(Point p);
	void SetEnd(Point p);
public:
	Status DFS_Search();
	Status BFS_Search();
public:
	void PrintMazeMap();
	void PrintPath();			// 根据 P 输出路径
};
