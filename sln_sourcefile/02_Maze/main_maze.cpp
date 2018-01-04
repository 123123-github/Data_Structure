#include "Maze.h"
#include <iostream>
using namespace std;

int main()
{
	Maze M;
	
	char filename[20] = "MazeMap.txt";				// 设置迷宫
	Point start = { 1,1 };
	Point end = { 8,8 };

	M.FileCreatMaze(filename);
	M.PrintMazeMap();
	
	M.SetStart(start);
	M.SetEnd(end);
	
	M.FindMazePath();								// 找到路径

	M.PrintPath();									// 输出路径

	system("pause");

	return 0;
}