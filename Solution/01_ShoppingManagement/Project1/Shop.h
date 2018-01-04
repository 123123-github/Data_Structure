//店铺

#pragma once
#include "MerchandiseList.h"


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
	Shop(const Shop& S);

public:
	int GetNum();						// 获得商店编号
	void SetNum(int num);				// 设置商店编号
	void SetShop(const MercList &merclist, int num = 0, const char* name = "", int credit = 0);						// 为商店信息赋初始值
	void PrintShop();					// 输出商铺信息
};

