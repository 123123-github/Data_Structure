// 店铺列表

#pragma once
#include "Shop.h"

//-------------------- 店铺结点定义 --------------------

struct SNode
{
	Shop data;
	SNode* next;
};

struct DuData
{
	int shopNum;
	char shopName[20];
	int credit;
	char mName[20];
	int price;
	int sale;

	void SetData(int snum, const char* sname, int scredit, const char* mname, int mprice, int msale);
	void ShowDuData();
};

struct DuInfoNode
{
	DuData data;
	DuInfoNode* prior;
	DuInfoNode* next;
};

//-------------------- 店铺链表定义 --------------------

class ShopList
{
private:
	SNode* head;
	SNode* tail;

	DuInfoNode* duHead;
	DuInfoNode* duTail;

public:
	ShopList();
	~ShopList();

public:
	void AppendShop(const char* name, int credit);

	void DelShop(int num);

	bool Empty();

	void ShowAllShop();

	SNode* GetShop(int num);

	void CreatDuList(const char* name);				// 建立名称为 name 的商品的双向循环信息链表

	void ShowDuList();								// 显示链表信息

	void FileAppendSList(ifstream &in);

	void WriteToFile(ofstream &out);

	void SaveData(const char* filename);
};
