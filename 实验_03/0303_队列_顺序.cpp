//SqQueue 循环队列实现
//(C++结构体)

#include "Queue_Sq.h"
//保留数据的个数为 N
#define N 10

//实现获得队列元素最大值
int QueueMaxElem(SqQueue Q)
{
	int n = Q.length;
	int e;
	int max = Q.front[0];

	for (int i = 0; i < n; i++)
	{
		DeQueue_Sq(Q, e);
		if (max<e)
		{
			max = e;
		}
	}

	return max;
}

//主函数
int main()
{
	SqQueue Q;
	InitQueue_Sq(Q);
	
	//队列建立
	int n,e=0;
	cout << "输入元素个数为：\n";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		//只保留最后 N 个数据
		if (Q.length==N)
		{
			DeQueue_Sq(Q, e);
		}
		cin >> e;
		EnQueue_Sq(Q, e);
	}
	cout << "最终数据为：\n";
	QueueTraverse_Sq(Q);
	//得到队列元素最大值
	int max;
	max = QueueMaxElem(Q);
	cout << "最大元素为：" << max << endl;

	//空间释放
	DestroyQueue_Sq(Q);

	system("pause");

	return 0;
}