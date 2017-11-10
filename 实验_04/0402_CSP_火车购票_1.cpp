//CSP 火车购票
#include <iostream>
using namespace std;

//火车的排数与每排的座位数
#define ROW 20
#define COL 5

//购票指令的反馈结果
struct OrderFeedback
{
	int row;	//买到票的排数
	int left;	//该排买时剩余的票数
	int num;	//买走的票数
};

//购买车票，输入为购票指令，即购买的车票的张数，返回反馈结果
void GetTickets(int train[], int order, OrderFeedback *feedback, int &InsNum)
{
	InsNum = 0;
	//可以买到全连座位
	for (int i = 0; i < ROW; i++)
	{
		if (train[i]>=order)
		{
			feedback[InsNum].left = train[i];
			feedback[InsNum].row = i;
			feedback[InsNum].num = order;

			train[i] -= order;
			InsNum++;
			return;
		}
	}
	//买不到全连座位
	int sum = 0;
	int i = 0;
	InsNum = 0;
	while (sum<order)
	{
		if (train[i]!=0)
		{
			sum += train[i];
			feedback[InsNum].row = i;
			feedback[InsNum].left = train[i];
			feedback[InsNum].num = train[i];
			InsNum++;
		}
		i++;
	}
	//修改最后一次购票的数目
	sum -= train[i - 1];
	train[i - 1] -= order - sum;

	return;
}
//打印单次单排的反馈结果 feedback
void PrintSingleOrder(OrderFeedback feedback)
{
	int start;
	start = COL*feedback.row + (COL - feedback.left + 1);

	for (int i = 0; i < feedback.num; i++)
	{
		cout << start + i << ' ';
	}
	return;
}

int main()
{
	//购票指令输入
	int num_order;
	cin >> num_order;
	int *order;
	order = new int[num_order];
	for (int i = 0; i < num_order; i++)
	{
		cin >> order[i];
	}

	//初始化火车座位
	int train[ROW];
	for (int i = 0; i < ROW; i++)
	{
		train[i] = COL;
	}

	OrderFeedback feedback[5];
	int num_feedback;
	//执行 num_order 条购票指令
	for (int i = 0; i < num_order; i++)
	{
		//获得车票反馈
		GetTickets(train, order[i], feedback, num_feedback);
		//打印车票
		for (int i = 0; i < num_feedback; i++)
		{
			PrintSingleOrder(feedback[i]);
		}
		cout << '\n';
	}

	//释放空间
	delete order;

	system("pause");

	return 0;
}