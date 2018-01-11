#include "Calculate.h"
#include <iostream>
#include <string>
using namespace std;


Calculate::Calculate()
{
	
}

Calculate::~Calculate()
{
}

int Calculate::Locate(char c)
{
	for (int i = 0; i < 7; i++)
		if (c == opname[i])
			return i;

	return -1;
}

void Calculate::GetEx()
{
	expression.clear();
	cout << "��������ʽ��\n";
	cin >> expression;
	cout << "���ʽ�������\n";
	expression.push_back('#');
}

bool Calculate::IsOP(char c)
{
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '=':
	case '#':
	case '(':
	case ')':
		return true;
	default:
		return false;
	}
}

char Calculate::Operate(char a, char theta, char b)
{
	int A, B;
	char result;

	A = a - '0' + 0;
	B = b - '0' + 0;
	switch (theta)
	{
	case '+':
		result = A + B - 0 + '0';
		break;
	case '-':
		result = A - B - 0 + '0';
		break;
	case '*':
		result = A * B - 0 + '0';
		break;
	case '/':
		result = A / B - 0 + '0';
		break;
	}
	return result;
}

void Calculate::Modification()										// ԭʼ���ʽ����
{
	char ch;
	int sum = 0;
	int count = 0;

	for (int i = 0;i < expression.size() - 1;++i)
	{
		ch = expression[i];
		if (IsOP(ch))						// �������ֱ�ӷŽ�
		{
			if (count != 0)
			{
				expression2.push_back(sum + '0');
				sum = 0;
				count = 0;
			}
			expression2.push_back(ch);
		}
		else
		{
			sum = sum * 10 + (ch - '0');
			++count;
		}
	}
	if (sum != 0)
		expression2.push_back(sum + '0');
	expression2.push_back('#');
	expression = expression2;
}

int Calculate::EvaluateExpression()									// ���ʽ����
{
	char ch;			// �������ַ�
	int num = 0;
	char theta;
	char a, b;

	OP.push('#');
	ch = expression.at(num++);

	while (ch != '#' || OP.top() != '#')
	{
		if (!IsOP(ch))
		{
			NUM.push(ch);
			ch = expression.at(num++);
		}
		else
		{
			switch (Precede(OP.top(), ch))
			{
			case '<':
				OP.push(ch);
				ch = expression.at(num++);
				break;
			case '=':
				OP.pop();							// ����һ������
				ch = expression.at(num++);
				break;
			case '>':
				theta = OP.top();
				OP.pop();

				a = NUM.top();
				NUM.pop();

				b = NUM.top();
				NUM.pop();

				NUM.push(Operate(b, theta, a));

				break;
			default:
				cout << "����\n";
				return -1;
				break;
			}
		}
	}
	return NUM.top() - '0';
}

char Calculate::Precede(char c1, char c2)
{
	int m, n;

	m = Locate(c1);
	n = Locate(c2);

	char result;
	result = op[m][n];

	return result;
}
