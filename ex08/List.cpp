#include "List.h"
#include <iostream>
using namespace std;

//--------------------------- 查找排序表函数实现 ----------------------------

List::List(int size)
{
	length = 0;
	listsize = size;
	order = true;

	elem = new int[size + 1];		// 0 号不存储
}

List::List(const List & L)
{
	length = L.length;
	listsize = L.listsize;
	order = L.order;

	elem = new int[listsize];
	for (int i = 1;i <= listsize;++i)
		elem[i] = L.elem[i];
}

List::~List()
{
	length = -1;
	listsize = -1;
	order = false;

	delete[] elem;
}

//---------- 基本操作 ----------

int List::ListLength()
{
	return length;
}

bool List::IsOrder()
{
	return order;
}

Status List::ListInsert(int e)
{
	/*
	if (length >= listsize)
	{
		listsize += SIZEINCREMENT;
		elem = (int*)realloc(elem, sizeof(int)*(listsize));
	}
	*/
	/*if (length >= listsize)
	{
		listsize += SIZEINCREMENT;
		int *newbase = (int*)realloc(elem, sizeof(int)*(listsize));
		elem = newbase;		// 申请空间大小错误，应为 listsize + 1
	}
	*/
	/*if (length >= listsize)
	{
		int *newbase;
		listsize += SIZEINCREMENT;
		newbase = new int[listsize + 1]; !!!
		for (int i = 1;i <= length;i++)
			newbase[i] = elem[i];
		delete[] elem;
		elem = newbase;
	}
	*/
	if (length >= listsize)
	{
		listsize += SIZEINCREMENT;
		elem = (int*)realloc(elem, sizeof(int)*(listsize + 1));
	}
	length++;
	elem[length] = e;

	order = false;

	return OK;
}

Status List::ListInsert(int e, int p)
{
	if (p<1 || p>length + 1)
		return ERROR;

	if (length >= listsize)
	{
		listsize += SIZEINCREMENT;
		elem = (int*)realloc(elem, sizeof(int)*(listsize));
	}

	for (int i = length; i >= p; i--)
		elem[i + 1] = elem[i];

	elem[p] = e;
	length++;

	order = false;

	return OK;
}

Status List::ListDelete(int e)
{
	if (length <= 0)
		return ERROR;

	int p;
	for (p = 1; p <= length; p++)
		if (elem[p] == e)
			break;

	for (int i = p + 1;i <= length;i++)
		elem[i - 1] = elem[i];

	length--;
	order = false;

	return OK;
}

void List::PrintList()
{
	for (int i = 1; i <= length; i++)
	{
		cout << elem[i] << '\t';
	}
	cout << endl;
}


//---------- 查找 ----------

int List::Search(int key)
{
	elem[0] = key;

	int i = length;
	while (elem[i] != key)
		--i;

	return i;
}

int List::BSearch(int key)
{
	if (!order)
		return -1;

	int low = 1;
	int high = length;
	int m;

	while (low <= high)
	{
		m = (low + high) / 2;

		if (elem[m] == key)
			return m;
		else if (elem[m] < key)
			low = m + 1;
		else
			high = m - 1;
	}

	return 0;
}


//---------- 排序 ----------

void List::BubbleSort()
{
	for (int i = 1; i <= length - 1;++i)
		for (int j = 1; j <= length - i; j++)
			if (elem[j] > elem[j + 1])
			{
				elem[0] = elem[j];
				elem[j] = elem[j + 1];
				elem[j + 1] = elem[0];
			}

	order = true;
}

void List::SelectSort()
{
	int p;
	for (int i = 1; i <= length - 1; i++)
	{
		p = i;
		for (int j = i + 1; j <= length; j++)
			if (elem[p] > elem[j])
				p = j;

		if (p != i)
		{
			elem[0] = elem[i];
			elem[i] = elem[p];
			elem[p] = elem[0];
		}
	}

	order = true;
}

void List::InsertSort()
{
	for (int i = 2;i <= length;++i)
	{
		elem[0] = elem[i];
		int j;
		for (j = i - 1;j > 0 && elem[j] > elem[0];--j)
			elem[j + 1] = elem[j];
		elem[j + 1] = elem[0];
	}

	order = true;
}


void List::ShellInsert(int d)
{
	for (int i = 1 + d; i <= length;++i)
	{
		elem[0] = elem[i];
		int j;
		for (j = i - d;j > 0 && elem[j] > elem[0];j -= d)
			elem[j + d] = elem[j];
		elem[j + d] = elem[0];
	}
}

void List::ShellSort()
{
	int dlta[] = { 5,3,1 };

	for (int i = 0; i < 3; i++)
		ShellInsert(dlta[i]);

	order = true;
}


int List::Partition(int low, int high)
{
	int i = low;
	int j = high;

	int pivotkey = elem[i];						// !!! 是 elem[low] ,不是 elem[1] !!!

	while (i < j)
	{
		while (i < j && elem[j] >= pivotkey)
			--j;
		elem[i] = elem[j];

		while (i < j && elem[i] <= pivotkey)
			++i;
		elem[j] = elem[i];
	}
	elem[i] = pivotkey;

	return i;
}

void List::QSort(int i,int j)
{
	int pivotloc;

	if (i < j)
	{
		pivotloc = Partition(i, j);
		QSort(i, pivotloc - 1);
		QSort(pivotloc + 1, j);
	}
}

void List::QuickSort()
{
	QSort(1, length);
}


void List::HeapAdjust(int s, int m)
{
	int r;
	int j;

	r = elem[s];

	for (j = 2 * s; j <= m;j *= 2)
	{
		if (j < m && elem[j] < elem[j + 1])
			++j;
		/* if (elem[s] >= elem[j]) !!! 错误的 !!! */
		if (r >= elem[j])
			break;

		elem[s] = elem[j];
		s = j;
	}

	elem[s] = r;
}

void List::HeapSort()
{
	for (int i = length / 2; i >= 1; --i)			// 调为大顶堆
		HeapAdjust(i, length);

	for (int i = length; i >= 2; --i)				// 取出最大数
	{
		elem[0] = elem[1];
		elem[1] = elem[i];
		elem[i] = elem[0];

		HeapAdjust(1, i - 1);
	}
}


void List::Merge(int s, int m, int n, int * &result)
{
	int i = s;
	int j = m + 1;
	int k = i;						/* !!!  此处 k 初值应为 i  !!! */

	while (i <= m && j <= n)
	{
		if (elem[i] <= elem[j])
			result[k++] = elem[i++];
		else
			result[k++] = elem[j++];		/* 错写为 = result[j++] */
	}

	while (i <= m)
		result[k++] = elem[i++];
	while (j <= n)
		result[k++] = elem[j++];
}

void List::MergeSort()
{
	int *result;
	result = new int[length + 1];				// 为归并排序开辟一个与自身同样大的空间

	int d;
	int s, m, n;

	for (d = 2;d <= length;d *= 2)											// d 个元素一组归并
	{

		for (n = d;n <= length;n += d)			// n 为归并的末尾元素
		{
			s = n - d + 1;
			m = n - d / 2;
			Merge(s, m, n, result);
		}
		if (n - d < length)													// 不足 d 个的也要合并
		{
			s = n - d + 1;			/* 跳出 for 循环后 n 一定大于等于 length , 需要先 - d 再判断 */
			n = length;
			m = s + d / 2 - 1;
			m = m > length ? length : m;
			Merge(s, m, n, result);
		}

		for (int i = 1; i <= length; i++)		// 转存至原空间
			elem[i] = result[i];
	}
	if (d / 2 < length)														// 合并剩余的不完整部分
	{
		s = 1;
		m = d / 2;
		n = length;
		Merge(s, m, n, result);

		for (int i = 1; i <= length; i++)		// 转存至原空间
			elem[i] = result[i];
	}

	delete[] result;
}


void List::RadixSort()
{
	int	 keynum = GetKeynum();			// 1.获得循环次数

	queue Q[10];						// 初始化队列
	for (int i = 0;i < 10;++i)
	{
		Q[i].front = Q[i].tail = new qnode;
		Q[i].tail->next = NULL;
	}
	qnode* Head;						// 2.转换为链表
	ChangeToLink(Head);

	int i, rixnum;
	for (i = 1, rixnum = 1;i <= keynum;++i, rixnum *= 10)		// 3.分配 回收
	{
		Distribute(Head, Q, rixnum);		// 结点分配到相应的队列，依据 rixnum
		Collect(Q, Head);					// 结点回收
	}

	ChangeToList(Head);
}

int List::GetKeynum()
{
	int max = elem[1];						// 获取最大值
	for (int i = 1;i <= length;++i)
		if (max < elem[i])
			max = elem[i];

	int keynum = 1;
	max /= 10;
	while (max != 0)						// 由最大值计算最高位数，即分配回收的趟数
	{
		++keynum;
		max /= 10;
	}

	return keynum;
}

void List::ChangeToLink(qnode* &Head)
{
	qnode *p, *s;

	Head = new qnode;						// 有头结点的链表
	Head->next = NULL;
	p = Head;								// p 在此处类似尾指针

	for (int i = 1; i <= length; i++)
	{
		makenode(s, elem[i]);
		p->next = s;
		p = s;
	}
}

void List::Distribute(qnode* Head, queue* Q, int rixnum)		// rixnum 用于取得相应的位数，第 i 趟取第 i 位
{
	qnode *p, *q;
	int radix = 0;				// 表示该入哪个队列
	int data;

	q = Head;
	for (p = Head->next;p;p = p->next)
	{
		data = p->data;
		radix = data / rixnum % 10;

		Q[radix].tail->next = p;
		Q[radix].tail = p;

		q->next = NULL;
		q = p;
	}
	q->next = NULL;
}

void List::Collect(queue* Q, qnode* Head)
{
	qnode *p;
	qnode *t;						// 作为链表的头尾结点
	t = Head;

	for (int i = 0;i < 10;++i)
	{
		p = Q[i].front->next;
		
		if (p)						// 队列不空，则整条接上
		{
			t->next = p;
			t = Q[i].tail;
		}
	}
}

void List::ChangeToList(qnode *& Head)
{
	qnode *p, *q;		// p 用于释放结点 q 用于遍历
	p = Head;
	q = Head->next;

	for (int i = 1;i <= length;++i)
	{
		elem[i] = q->data;

		delete p;		// 顺便释放链表
		p = q;
		q = q->next;
	}

	delete p;
	p = NULL;
}


//---------- 基数排序用到的辅助结构 ----------


void makenode(qnode* &s, int e)
{
	s = new qnode;
	s->data = e;
	s->next = NULL;
}
