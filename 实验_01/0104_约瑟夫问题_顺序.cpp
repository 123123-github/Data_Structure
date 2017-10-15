//约瑟夫问题
//顺序表实现
#include <iostream>
using namespace std;
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//Status 为函数类型，值为函数结果状态代码
typedef int Status;

//线性表定义
#define LIST_INIT_SIZE 100 //线性表存储空间 初始分配量
#define LISTINCREMENT 10   //线性表存储空间 分配增量	 
struct SqList
{
	int *elem;
	int length;
	int listsize;
};
//顺序表相关函数定义

//构造长度为 n 的线性表 L
Status InitList_Sq(SqList &L,int n)
{
	L.elem = new int[n];
	if (L.elem == NULL)
		exit(OVERFLOW);

	L.length = 0;
	L.listsize = n;

	return OK;
}
//销毁线性表L
Status DestroyList_Sq(SqList &L)
{
	if (L.elem == NULL)
		return ERROR;

	delete[] L.elem;

	return OK;
}
//在线性表的第i个位置删除元素，并用e返回其值;若成功返回OK，否则返回ERROR
Status ListDelete_Sq(SqList &L, int i, int &e)
{
	if (i<1 || i>L.length) //判断i是否合法
		return ERROR;

	//返回第i个元素的值
	e = *(L.elem + i - 1);
	//移动元素并删除
	int j;
	for (j = i + 1;j <= L.length;j++)
		*(L.elem + j - 2) = *(L.elem + j - 1);

	//修改线性表长度（长度-1）
	L.length--;

	return OK;
}

//约瑟夫问题求解 
int main()
{   //初始的输入值
	int n, s, m;

	cout << "请依次输入：圆桌人数n，开始报数人位序s，出列人报数数m.\n";
	cin >> n >> s >> m;
	cout << endl;
	
	//构造长度为 n 的线性表，并存入信息，以初始位序作为每个人的信息
	SqList L;
	InitList_Sq(L,n);
	for (int i = 0;i < n;i++)
	{
		L.elem[i] = i + 1;
		L.length++;
	}

	//d记录每次出列人的相对位序（即在现存队列中的位序）
	//e记录出列人信息
	int d, e=0;

	while (n != 0)
	{
		//计算并修正d的值
		d = (s + m - 1) % n;
		if (d == 0)
			d = n;
		//报到 m 的人出列
		ListDelete_Sq(L, d, e);
		cout << "第"<<n<<"次出列人信息： " << e << endl;
		//修改队列信息
		s = d;
		n--;
	}

	cin.get();
	cin.get();

	return 0;
}