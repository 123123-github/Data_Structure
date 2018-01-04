// 店铺列表

#pragma once
#include "Shop.h"

//-------------------- 店铺结点定义 --------------------

struct ShopNode
{
	Shop data;
	ShopNode* next;
};


//-------------------- 店铺链表定义 --------------------

class ShopList
{
private:
	ShopNode* head;
	ShopNode* tail;

public:
	ShopList();
	ShopList(const ShopList& SL);
	~ShopList();

public:
	void AppendShop(Shop S);
	void DeleteShop(int shopnum);
	Shop* GetShop(int shopnum);				// 找到制定编号的商店
	void PrintShopList();




};

