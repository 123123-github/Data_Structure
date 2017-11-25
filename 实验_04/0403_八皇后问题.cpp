//八皇后问题
//栈实现
#include <iostream>
using namespace std;

//-------------问题规模-------------
#define PROBLEM_SIZE 8
int k1[PROBLEM_SIZE + 1];		//存放斜线位置比较信息
int k2[PROBLEM_SIZE + 1];

//-----------栈及相关函数实现-----------
struct Stack
{
	int *base;
	int *top;
	int num;					//栈元素数，同时记录行号
};

int InitStack(Stack &S)
{
	S.base = new int[PROBLEM_SIZE + 1];
	if (!S.base)
		return 0;

	S.top = S.base;
	S.num = 0;

	/* [0] 空间不使用 */
	*S.top = 0;
	S.top++;

	return 1;
}

void DestroyStack(Stack &S)
{
	delete[] S.base;
	S.base = S.top = NULL;

	S.num = -1;

	return;
}

void Push(Stack &S, int position)
{
	*S.top = position;
	S.num++;
	S.top++;

	/*添加斜线比较信息*/
	k1[S.num] = S.num - position;
	k2[S.num] = PROBLEM_SIZE + 1 - position - S.num;
}

void Pop(Stack &S)
{
	S.top--;
	S.num--;
}

void PrintStack(Stack &S)
{
	int *p = S.base;

	for (int i = 1; i <= 8; i++)
	{
		cout << '(' << i << ',' << p[i] << ')' << '\n';
	}
	cout << endl;
}

//-----------------条件判断函数--------------

bool ColCurrect(Stack &S,int position)			//是否同列无冲突,引用减少赋值过程
{
	int *a;
	a = S.base;

	for (int i = 1; i <= S.num; i++)
	{
		if (a[i] == position)
			return false;
	}

	return true;
}

bool KCurrect(Stack &S,int position)				//是否斜线无冲突
{
	int pk1,pk2;
	pk1 = S.num + 1 - position;
	pk2 = PROBLEM_SIZE + 1 - position - S.num - 1;
	
	for (int i = 1; i <= S.num; i++)
	{
		if (k1[i] == pk1 || k2[i] == pk2)
			return false;
	}

	return true;
}

//------------主函数------------

int main()
{
	//建栈
	Stack S;
	InitStack(S);

	int start = 1;
	cout << "请输入第一个棋子位置\n";
	cin >> start;

	int position;
	while (S.num < PROBLEM_SIZE)			//每次循环找到一行的位置，或弹出一个元素
	{
		for (position = start; position <= PROBLEM_SIZE; position++)
		{
			if (ColCurrect(S, position) && KCurrect(S, position))
			{
				Push(S, position);
				start = 1;
				break;
			}
		}
		if (position > PROBLEM_SIZE)
		{
			Pop(S);
			start = *S.top + 1;			//栈全弹空则从头开始
		}
	}

	PrintStack(S);

	DestroyStack(S);

	system("pause");

	return 0;
}