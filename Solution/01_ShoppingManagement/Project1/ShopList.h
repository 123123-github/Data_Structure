// 店铺列表

#pragma once
#include "Shop.h"

//-------------------- 店铺结点定义 --------------------

struct ShopNode
{
	Shop data;
	Shop* next;
};


//-------------------- 店铺链表定义 --------------------

class ShopList
{
public:
	ShopNode* head;
	ShopNode* tail;


public:
	ShopList();
	~ShopList();
};

