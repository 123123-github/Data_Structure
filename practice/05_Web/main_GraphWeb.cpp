#include <iostream>
#include "GraphWeb.h"
#include <fstream>
using namespace std;

int main()
{
	//-------------------------- ���� 1 -----------------------------

	GraphWeb G("data1.txt");

	G.Dijkstra();
	G.PrintShortest("out1.txt");
	


	//-------------------------- ���� 2 -----------------------------

	//�ܺ������^2������ ����ܸı���̾����·��
	//�㷨���� �Ƚ��ڽӾ���ת��Ϊ�洢�ܺ���Ϣ�ľ��� Ϊʹ�����ܺ���Сʹ��Prim�㷨
	//ԭ�Ȳ��ɴ�ĵ���Ȼ���ɴ�

	G.Prim();
	G.PrintLowE("out2.txt");

	system("pause");

	return 0;
}