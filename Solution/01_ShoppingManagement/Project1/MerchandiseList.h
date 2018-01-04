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

	void PrintMerc();
	void SetMerc(const char *name = "", int price = 0, int sales = 0);			// 为商品赋初始值
};

struct MerchandiseNode		// 商品结点
{
	Merchandise data;
	MerchandiseNode* next;

	void SetMercNode(Merchandise m = { "",0,0 });		// 为商品结点赋值
};


//--------------------- 商品链表 ---------------------

class MercList			// 商品链表
{
private:
	MerchandiseNode* head;
	MerchandiseNode* tail;

public:
	MercList();
	~MercList();
	MercList(const MercList& list);
	
public:
	MercList & operator=(const MercList &merclist);

public:
	void PrintMercList();								// 输出链表中的所有商品
	
	void AppendMerc(Merchandise m);						// 链表追加商品
	void DeleteMerc(const char* name);					// 删除指定名称的商品
	MerchandiseNode* GetMercNode(const char* name);		// 返回商品结点

};

