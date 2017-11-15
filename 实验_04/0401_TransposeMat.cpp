//稀疏矩阵转置
#include "TSMat.h"

int main()
{
	TSMat M,T1,T2,T3;
	//初始化
	InitTSMat(M);
	InitTSMat(T1);
	InitTSMat(T2);
	InitTSMat(T3);

	// 创建及输出检验
	CreatTSMat(M);
	PrintTSMat(M);

	//转置——1
	cout << "转置——1\n";
	TransposeMat_1(T1, M);
	PrintTSMat(T1);
	//转置——2
	cout << "转置——2\n";
	TransposeMat_2(T2, M);
	PrintTSMat(T2);
	//快速转置
	cout << "快速转置\n";
	FastTransposeMat(T3, M);
	PrintTSMat(T3);

	//释放空间
	DestroyTSMat(M);
	DestroyTSMat(T1);
	DestroyTSMat(T2);
	DestroyTSMat(T3);

	system("pause");

	return 0;
}