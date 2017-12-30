//�˻ʺ�����
//ջʵ��
#include <iostream>
using namespace std;

//-------------�����ģ-------------
#define PROBLEM_SIZE 8
int k1[PROBLEM_SIZE + 1];		//���б��λ�ñȽ���Ϣ
int k2[PROBLEM_SIZE + 1];

//-----------ջ����غ���ʵ��-----------
struct Stack
{
	int *base;
	int *top;
	int num;					//ջԪ������ͬʱ��¼�к�
};

int InitStack(Stack &S)
{
	S.base = new int[PROBLEM_SIZE + 1];
	if (!S.base)
		return 0;

	S.top = S.base;
	S.num = 0;

	/* [0] �ռ䲻ʹ�� */
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

	/*���б�߱Ƚ���Ϣ*/
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

//-----------------�����жϺ���--------------

bool ColCurrect(Stack &S,int position)			//�Ƿ�ͬ���޳�ͻ,���ü��ٸ�ֵ����
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

bool KCurrect(Stack &S,int position)				//�Ƿ�б���޳�ͻ
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

//------------������------------

int main()
{
	//��ջ
	Stack S;
	InitStack(S);

	int start = 1;
	cout << "�������һ������λ��\n";
	cin >> start;

	int position;
	while (S.num < PROBLEM_SIZE)			//ÿ��ѭ���ҵ�һ�е�λ�ã��򵯳�һ��Ԫ��
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
			start = *S.top + 1;			//ջȫ�������ͷ��ʼ
		}
	}

	PrintStack(S);

	DestroyStack(S);

	system("pause");

	return 0;
}