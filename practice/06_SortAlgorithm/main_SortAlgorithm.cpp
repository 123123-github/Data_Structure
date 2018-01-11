#include <iostream>
#include "List.h"
#include <time.h>
#include <fstream>
using namespace std;

#define SORT_NUM 20000

int main()
{
	List L;
	char initfile[20] = "data0.txt";
	char outfile[20] = "_QuickSort.txt";							//--------------- 修改
	ofstream out;
	ifstream in;
	clock_t start, end;
	double time;

	out.open(outfile);
	out << "排序个数:\t" << SORT_NUM << '\n';
	for (int i = 0; i < 10; i++)
	{
		initfile[4] = i - 0 + '0';		// 读取不同的文件
		in.open(initfile);
		L.ReadFromFile(in);

		if (i == 1)
		{
			L.Clear();
			continue;
		}
		/*-------------------------------*/
		start = clock();

		//-------- 插入排序片段 ---------
		L.QuickSort();										//--------------- 修改
		//-------- 插入排序片段 ---------

		end = clock();
		/*------------------------------*/
		time = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "排序用时:\t" << time << 's' << '\n';

		L.Clear();
		in.close();

		out << "文件:\t" << initfile << '\n';
		L.StatisticsWrite(out, time);
	}
	out.close();
	
	//------------ 排序函数 -----------

	//L.HeapSort();
	//L.BubbleSort();
	//L.ShellSort();
	//L.InsertSort();
	//L.MergeSort();
	//L.QuickSort();
	//L.RadixSort();
	//L.ShellSort();

	//----------- 排序结果输出 ---------

	//cout << "排序结果" << '\n';
	//L.PrintList();

	system("pause");

	return 0;
}