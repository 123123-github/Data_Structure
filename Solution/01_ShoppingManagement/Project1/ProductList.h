// 店铺商品列表

#pragma once
#include <iostream>
using namespace std;

//-------------------- 商品结构定义 --------------------

#define NAMESIZE_MERC 20

struct Merchandise			// 商品
{
	char name[NAMESIZE_MERC];			// 商品名
	int price;							// 价格
	int salesvolume;					// 销售量
};

struct MerchandiseNode		// 商品结点
{
	Merchandise data;
	Merchandise* next;

	void SetMercNode(const char *name = "", int price = 0, int sales = 0);		// 为商品赋值
};



//--------------------- 商品链表 ---------------------

class ProductList			// 商品链表
{
private:
	MerchandiseNode* head;
	MerchandiseNode* tail;

public:
	ProductList();
	ProductList(const ProductList& list);
	~ProductList();

public:


};

