// �Թ�����
// ������� �������
#pragma once
#include "Status.h"

//------------------ �Թ�����Ԫ�ض��� -------------------

struct Point
{
	int m;
	int n;

	int pos(int row,int col);		// ����һάλ��
	bool operator==(const Point &p);
};


//-------------------- �Թ��ඨ�� -----------------------

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
	int *P;						// ��¼����·��
	bool *visited;				// �Ƿ��ѷ���
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
	void PrintPath();			// ���� P ���·��
};
