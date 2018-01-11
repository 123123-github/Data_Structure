#pragma once
#include "Merc.h"

#define INITSIZE 20
#define SIZEINCREMENT 10

class MercList			// 顺序表
{
private:
	Merc * mercs;
	int len;
	int size;

public:
	MercList(int maxsize = INITSIZE);
	~MercList();

public:
	bool isIn(const char *name);											// 是否含该商品
	int ListLength();
	Merc & getMerc(const char* name);										// 返回所需商品的引用
	void showAllMercs();
	void appendMerc(const char *name, int price, int sale);
	bool deleteMerc(const char *name);
	void InitMercList(ifstream &in);
	void SaveMercList(ofstream &out);
};

