//店铺
#pragma once
#include "MercList.h"

//-------------------- 店铺结构定义 --------------------

class Shop
{
private:
	int num;							// 编号
	char name[20];						// 店铺名
	int credit;							// 信誉度
	MercList merclist;					// 商品列表

public:
	Shop();
	~Shop();

public:
	MercList * GetMercList();
	void SetShop(int num, const char* name, int credit);
	void ShowShop();

	friend class ShopList;
};

