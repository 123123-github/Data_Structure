#include <iostream>
#include "Maze.h"
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

	M.DFS_Search();															// 深度搜索

	M.PrintPath();															// 输出路径

	M.BFS_Search();															// 广度搜索

	M.PrintPath();

	system("pause");

	return 0;
}