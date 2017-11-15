//稀疏矩阵实现及基本函数定义
//

#include <iostream>
using namespace std;

//------------------函数结果状态代码-----------------
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//Status 为函数类型，值为函数结果状态代码
typedef int Status;

//--------------------稀疏矩阵定义--------------------

#define INITSIZE_TSMAT 100		//宏定义
#define INCREMENT_TSMAT 10

struct Triple					//三元组
{
	int m;
	int n;
	int e;
};

struct TSMat					//稀疏矩阵
{
	int row;
	int col;
	int num;
	int maxsize;
	Triple *data;	//data[0]不使用
};

void SortMatElem(TSMat &M)		//为矩阵中的元素排序，按照行列顺序
{
	Triple *a = M.data;
	Triple t;

	for (int i = 1; i <= M.num - 1; i++)
	{
		int p = i;
		for (int j = i + 1; j <= M.num; j++)
		{
			if (a[p].m > a[j].m)
				p = j;
			else if (a[p].m == a[j].m && a[p].n > a[j].n)
				p = j;
		}
		if (p != i)
		{
			t = a[p];
			a[p] = a[i];
			a[i] = t;
		}
	}

	return;
}

//----------------------基本操作---------------------

Status InitTSMat(TSMat &M)			//初始化为空矩阵，不赋值
{
	M.data = new Triple[INITSIZE_TSMAT + 1];
	if (!M.data)
		return ERROR;

	M.maxsize = INITSIZE_TSMAT;
	M.num = M.row = M.col = 0;

	return OK;
}

Status DestroyTSMat(TSMat &M)		//销毁稀疏矩阵，释放三元组空间
{
	delete[] M.data;
	M.data = NULL;

	M.maxsize = M.num = M.row = M.col = -1;

	return OK;
}

Status CreatTSMat(TSMat &M)			//创建矩阵，为其赋值
{
	cout << "请输入矩阵的非零元数、行数及列数\n";
	cin >> M.num >> M.row >> M.col;

	if (M.num>M.maxsize)		//空间不足时另辟空间
	{
		Triple *newbase;

		newbase = new Triple[M.num + 1];
		if (!newbase)
			return ERROR;

		delete[] M.data;

		M.data = newbase;
		M.maxsize = M.num;
	}

	cout << "请依次输入矩阵非零元素信息 （行+列+值）\n";
	Triple *a = M.data;
	for (int i = 1; i <= M.num; i++)
	{
		cin >> a[i].m >> a[i].n >> a[i].e;
	}

	SortMatElem(M);				//为避免未按顺序输入，对元素按行列进行排序

	return OK;
}

void PrintTSMat(TSMat M)			//输出稀疏矩阵
{
	Triple *a = M.data;

	cout << "非零元个数为:" << M.num << '\n';
	cout << "ROW=" << M.row << '\t' << "COL=" << M.col << '\n';
	for (int i = 1; i <= M.num; i++)
	{
		cout << '(' << a[i].m << ',' << a[i].n << ')'
			<< '\t' << a[i].e << '\n';
	}
	cout << endl;

	return;
}

//-------------稀疏矩阵转置--------------

//将 M 转置后的结果存放在矩阵T中, T 已初始化

//快速转置
Status FastTransposeMat(TSMat &T, TSMat M)
{
	Triple *a, *b;
	a = M.data;
	b = T.data;
	int N = M.num;

	if (T.maxsize < M.num)			// 存储空间不足则为 T 扩展空间
	{
		Triple *newbase;

		newbase = new Triple[M.num + 1];
		if (!newbase)
			return ERROR;

		delete[] T.data;

		T.data = newbase;
		T.maxsize = M.num;
	}

	T.num = M.num;					//基本信息改变
	T.row = M.col;
	T.col = M.row;

	//----------------------快速转置----------------------
	int *num, *cpot;					//两个辅助向量
	num = new int[M.col + 1];
	cpot = new int[M.col + 1];

	for (int i = 1; i <= M.col; i++)	//辅助向量初始化
	{
		num[i] = 0;
	}
	cpot[1] = 1;

	for (int i = 1; i <= N; i++)		//统计 M 每列上元素个数
	{
		num[a[i].n]++;
	}
	for (int i = 2; i <= M.col; i++)	//确定准确位置
	{
		cpot[i] = cpot[i - 1] + num[i - 1];
	}

	int p, q;							//一次循环完成转置
	for (int i = 1; i <= N; i++)
	{
		p = a[i].n;
		q = cpot[p];
		b[q].m = a[i].n;
		b[q].n = a[i].m;
		b[q].e = a[i].e;

		cpot[p]++;
	}

	//释放空间
	delete[] cpot;
	delete[] num;

	return OK;
}

//直接转置后再排序
Status TransposeMat_1(TSMat &T, TSMat M)
{
	Triple *a, *b;
	a = M.data;
	b = T.data;
	int N = M.num;

	if (T.maxsize < M.num)			// 存储空间不足则为 T 扩展空间
	{
		Triple *newbase;

		newbase = new Triple[M.num + 1];
		if (!newbase)
			return ERROR;

		delete[] T.data;

		T.data = newbase;
		T.maxsize = M.num;
	}

	T.num = M.num;					//基本信息改变
	T.row = M.col;
	T.col = M.row;

	for (int i = 1; i <= N; i++)	//元素转置
	{
		b[i].m = a[i].n;
		b[i].n = a[i].m;
		b[i].e = a[i].e;
	}

	/*-----------------------此种方法排序错误--------------------------
	(可能是因为选择排序)
	Triple t;
	for (int i = 1; i <= N - 1; i++)	//按照行排一次序，列不必再排
	{
		int p = i;
		for (int j = i + 1; j <= M.num; j++)
		{
			if (b[p].m > b[j].m)
				p = j;
		}
		if (p != i)
		{
			t = b[p];
			b[p] = b[i];
			b[i] = t;
		}
	}

	-------------------使用按行按列排序后答案正确------------------------
	---------------------------------------------------------------------
	*/
	
	SortMatElem(T);

	return OK;
}

//按列的顺序逐个挑选至新矩阵
Status TransposeMat_2(TSMat &T, TSMat M)
{
	Triple *a, *b;
	a = M.data;
	b = T.data;
	int N = M.num;

	if (T.maxsize < M.num)			// 存储空间不足则为 T 扩展空间
	{
		Triple *newbase;

		newbase = new Triple[M.num + 1];
		if (!newbase)
			return ERROR;

		delete[] T.data;

		T.data = newbase;
		T.maxsize = M.num;
	}

	T.num = M.num;					//基本信息改变
	T.row = M.col;
	T.col = M.row;

	int k = 1;
	for (int col = 1; col <= M.col; col++)
	{
		for (int i = 1; i <= N; i++)
		{
			if (a[i].n == col)
			{
				b[k].m = a[i].n;
				b[k].n = a[i].m;
				b[k].e = a[i].e;
				k++;
			}
		}
	}

	return OK;
}