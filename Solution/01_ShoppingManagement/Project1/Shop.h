//店铺

#pragma once
#include "ProductList.h"


//-------------------- 店铺结构定义 --------------------




class Shop
{
public:
	char num[10];						// 编号
	char name[20];						// 店铺名
	int credit;							// 信誉度
	ProductList merchandiseList;		// 商品列表




public:
	Shop();
	~Shop();
};

