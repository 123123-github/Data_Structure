#include "Calculate.h"
#include <iostream>
using namespace std;

int main()
{
	int result;
	Calculate ex;

	ex.GetEx();								// ԭʼ���ʽ��ȡ
	ex.Modification();						// �ַ�������
	result = ex.EvaluateExpression();		// ����

	cout << result << '\n';

	system("pause");
	return 0;
}