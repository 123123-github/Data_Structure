// ADT List 基本操作
// 顺序实现 (C++结构体)

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

//十二个 基本函数实现：

//构造(初始化)空表
Status InitList_Sq(SqList &L)
{
	L.elem = new int[LIST_INIT_SIZE];
	if (L.elem == NULL)
		exit(OVERFLOW);

	L.length  =  0;
	L.listsize  =  LIST_INIT_SIZE;

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
//将表置为空表
Status ClearList_Sq(SqList &L)
{
	if (L.elem == NULL)
		return ERROR;

	L.length = 0;

	return OK;
}
//表为空返回TRUE，否则返回FALSE
Status ListEmpty_Sq(SqList L)
{
	if (L.elem == NULL)
		return ERROR;

	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}
//返回表的长度
int ListLength_Sq(SqList L)
{
	if (L.elem == NULL)
		return ERROR;

	return L.length;
}
//用e返回L中的第i个值，成功时函数返回OK，否则返回FALSE
Status GetElem_Sq(SqList L, int i, int &e)
{
	if (i < 1 || i>L.length)
		return FALSE;

	e = *(L.elem + i - 1);

	return OK;
}
//返回L中第一个与e相等的元素的位序，不存在时返回0
int LocateElem_Sq(SqList L, int e)
{
	if (L.elem == NULL)
		return ERROR;

	for (int i = 1;i <= L.length;i++)
		if (L.elem[i-1] == e)
			return i;

	return 0;
}
//用 pre_e 返回元素 cur_e 的前驱；操作成功返回OK，否则返回ERROR
Status PriorElem_Sq(SqList L, int cur_e, int &pre_e)
{
	if (L.elem == NULL)
		return ERROR;

	int i = LocateElem_Sq(L, cur_e);
	if (i < 2 || i> L.length)
		return ERROR;

	pre_e = *(L.elem + i - 2);

	return	OK;
}
//用 next_e 返回元素 cur_e 的后继；操作成功返回OK，否则返回ERROR
Status NextElem_Sq(SqList L, int cur_e, int &next_e)
{
	if (L.elem == NULL)
		return ERROR;

	int i = LocateElem_Sq(L, cur_e);
	if (i < 1 || i> L.length - 1)
		return ERROR;

	next_e = *(L.elem + i);

	return	OK;
}
//在线性表的第i个位置插入e;若成功返回OK，否则返回ERROR
Status ListInsert_Sq(SqList &L, int i, int e)
{
	if (i<1 || i> L.length + 1) //判断i是否合法
		return ERROR;

	//若线性表已满，则扩展线性表长度
	if (L.length == L.listsize)
	{
		//申请新空间
		int* newbase;
		newbase = new int[L.length + LISTINCREMENT];
		if (newbase == NULL)
			exit(OVERFLOW);

		//移动元素
		for (int i = 0;i < L.length;i++)
			newbase[i] = L.elem[i];

		//更改线性表数组指针指向,修改线性表长度参数
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}

	//移动元素
	int j;
	for (j = L.length;j >= i;j--)
		*(L.elem + j) = *(L.elem + j - 1);

	//插入元素，并修改线性表长度（长度+1）
	*(L.elem + i - 1) = e;
	L.length++;

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
//遍历(输出)线性表
void ListTraverse_Sq(SqList L)
{

	for (int i = 0; i < L.length; i++)
		cout << L.elem[i] << '\t';
	cout << endl;

	return;
}
//创建线性表
void CreatList_Sq(SqList &L, int n)
{
	//初始化线性表
	InitList_Sq(L);
	//创建时插入的元素定义为e
	int e;

	for (int i = 0;i < n;i++)
	{
		cin >> e;
		ListInsert_Sq(L, L.length + 1, e);
	}

	return;
}

int main()
{
	SqList L;

	int n;
	//1.创建 2.遍历 3.初始化函数 检验
	cout << "请输入元素个数n，及元素\n";
	cin >> n;
	CreatList_Sq(L,n);
	ListTraverse_Sq(L);

	int i, e, pre_e, next_e;

	//4.获取元素函数 检验
	cout << "请输入所要选取元素的位数：\n";
	cin >> i;
	GetElem_Sq(L, i, e);
	cout << "该元素为：" << e << endl;

	//5.前一个 6.后一个 函数检测
	cout << "请输入一个表中的元素\n";
	cin >> e;
	NextElem_Sq(L, e, next_e);
	PriorElem_Sq(L, e, pre_e);
	cout << "该元素前一个为: " << pre_e << endl;
	cout << "该元素后一个为: " << next_e << endl;
	
	//7.长度
	cout << "此时线性表长度为：" << ListLength_Sq(L) << endl;

	//8.插入 9.删除
	cout << "请输入插入元素e，插入位置i\n";
	cin >> e >> i;
	ListInsert_Sq(L,i,e);
	cout << "插入后为：" << endl;
	ListTraverse_Sq(L);

	cout << "请输入删除的元素位置i\n";
	cin >> i;
	ListDelete_Sq(L,i,e);
	cout << "删除的元素为 " << e << endl;
	cout << "删除后为：" << endl;
	ListTraverse_Sq(L);

	//10.定位 11.清空  12.是否为空 13.销毁
	cout << "输入一个元素\n";
	cin >> e;
	cout << "该元素位置为：";
	cout << LocateElem_Sq(L, e);

	//清空线性表
	cout << "清空函数调用\n";
	ClearList_Sq(L);
	ListTraverse_Sq(L);
	
	if (ListEmpty_Sq(L))
		cout << "线性表为空" << endl;

	DestroyList_Sq(L);

	system("pause");

    return 0;
}

