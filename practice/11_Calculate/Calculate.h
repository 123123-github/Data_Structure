#pragma once
#include <stack>
using namespace std;

class Calculate
{
private:
	stack<char> OP;
	stack<char> NUM;
	string expression;			// Ҫ����ı��ʽ
	string expression2;			// �����ı��ʽ

	char opname[7] = { '+' ,'-','*','/', '(', ')','#' };
	char op[7][7] =
	{
	{'>','>','<','<','<','>','>'},
	{'>','>','<','<','<','>','>'},
	{'>','>','>','>','<','>','>'},
	{'>','>','>','>','<','>','>'},
	{'<','<','<','<','<','=','#'},
	{'>','>','>','>','#','>','>'},
	{'<','<','<','<','<','#','='},
	};

public:
	Calculate();
	~Calculate();

	int Locate(char c);
	void GetEx();												// ��ȡ���ʽ
	bool IsOP(char c);											// �Ƿ��������
	char Operate(char a,char theta,char b);
	void Modification();										// �޸�����ԭ���ʽ
	int EvaluateExpression();
	char Precede(char c1, char c2);								// ���ȼ��ж�
};

