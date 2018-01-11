#include <iostream>
#include "Maze.h"
using namespace std;

int main()
{
	Maze M;

	char filename[20] = "MazeMap.txt";				// �����Թ�
	Point start = { 1,1 };
	Point end = { 8,8 };

	M.FileCreatMaze(filename);
	M.PrintMazeMap();

	M.SetStart(start);
	M.SetEnd(end);

	M.DFS_Search();															// �������

	M.PrintPath();															// ���·��

	M.BFS_Search();															// �������

	M.PrintPath();

	system("pause");

	return 0;
}