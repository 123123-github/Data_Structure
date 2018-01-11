// 迷宫问题
// 栈操作实现
#pragma once
#include "Stack.h"
#include "Status.h"


//------------------ 迷宫基本元素定义 -------------------

struct Point			// 点坐标
{
	int m;
	int n;

	bool operator==(Point &p);
	inline int position(int row, int col);
};

struct mazepath			// 入栈元素
{
	int step;								// 步数
	Point pos;								// 位置
	int di;									// 下一步的方向
};


//-------------------- 迷宫类定义 -----------------------

class Maze
{
private:								// 迷宫的基本元素
	int row;
	int col;
	bool **maze;
	Point start;
	Point end;

private:								// 求解路径的基本元素
	int size;
	int step;													// 步数 同时是 足迹数 比 最终路径块 多的是 不通的块
	Point curpos;
	Stack<mazepath> S;											// 路径
	Point *mark;												// 标记
	Point *footpoint;											// 足迹

public:
	Maze();
	~Maze();

public:									// 生成
	Status FileCreatMaze(const char* filename);
	void SetStart(Point p);
	void SetEnd(Point p);

private:									
	bool Pass(Point p);											// 判断当前点是否能通
	Point NextPos(Point p,int di);								// 根据坐标 p 方向 di 计算下一个位置
	void FootPoint(Point p);
	void Mark(Point p);

public:									// 求解
	Status FindMazePath();

public:									// 输出
	void PrintMazeMap();
	void PrintPath();
};
