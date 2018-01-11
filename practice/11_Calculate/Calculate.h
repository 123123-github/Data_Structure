#pragma once
#include <stack>
using namespace std;

class Calculate
{
private:
	stack<char> OP;
	stack<char> NUM;
	string expression;			// 要计算的表达式
	string expression2;			// 处理后的表达式

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
	void GetEx();												// 读取表达式
	bool IsOP(char c);											// 是否是运算符
	char Operate(char a,char theta,char b);
	void Modification();										// 修改整合原表达式
	int EvaluateExpression();
	char Precede(char c1, char c2);								// 优先级判断
};

