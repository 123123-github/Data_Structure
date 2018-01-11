#include "Calculate.h"
#include <iostream>
using namespace std;

int main()
{
	int result;
	Calculate ex;

	ex.GetEx();								// 原始表达式获取
	ex.Modification();						// 字符串处理
	result = ex.EvaluateExpression();		// 计算

	cout << result << '\n';

	system("pause");
	return 0;
}