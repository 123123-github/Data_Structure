//CSP 火车购票
#include <iostream>
using namespace std;

struct Train
{
	int seat_num;
	bool status;
};
//针对单条购票信息打印火车票
void PrintTicksts(int order, Train train[][5], int leftticksts[])
{
	for (int i = 0; i < 20; i++)
	{
		if (leftticksts[i]>=order)
		{
			//出票
			leftticksts[i] -= order;
			//打印座位
			for (int j = 0; j < 5; j++)
			{
				if (order && train[i][j].status)
				{
					cout << train[i][j].seat_num << ' ';
					train[i][j].status = false;
					order--;
				}
			}
			//找到了连座位，打印完车票后返回
			return;
		}
	}
	//找不到连座位
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (order && train[i][j].status)
			{
				cout << train[i][j].seat_num << ' ';
				train[i][j].status = false;
				order--;
			}
			if (order==0)
			{
				return;
			}
		}
	}
}

int main()
{
	Train train[20][5];
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 20; i++)
		{
			train[i][j].seat_num = 5 * i + j + 1;
			train[i][j].status = true;
		}
	}
	int lefttickets[20];
	for (int i = 0; i < 20; i++)
	{
		lefttickets[i] = 5;
	}
	//指令数
	int n;
	cin >> n;
	int *order;
	order = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> order[i];
	}
	//购票
	for (int i = 0; i < n; i++)
	{
		PrintTicksts(order[i], train, lefttickets);
		cout << endl;
	}
	//空间释放
	delete order;

	system("pause");

	return 0;
}