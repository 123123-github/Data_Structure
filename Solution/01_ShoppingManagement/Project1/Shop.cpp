#include "Shop.h"
#include <iostream>
using namespace std;

//------------ 可以不定义 缺省的也管用----------

Shop::Shop():merclist()				// 调用成员类的构造函数
{
	this->num = 1;					// 店铺编号从 1 开始
	strcpy_s(this->name, "");
	this->credit = 0;
}

Shop::~Shop()						// 会自动调用成员类的析构函数
{
	
}

Shop::Shop(const Shop & S) :merclist(S.merclist)
{
	this->num = S.num;
	strcpy_s(this->name, S.name);
	this->credit = S.credit;
}


void Shop::PrintShop()
{
	cout << "店铺编号:\t" << this->num << '\n'
		<< "店铺名\t" << this->name << '\t'
		<< "信誉度\t" << this->credit << '\n';
	this->merclist.PrintMercList();
}

void Shop::SetNum(int num)
{
	this->num = num;
}

int Shop::GetNum()
{
	return this->num;
}

void Shop::SetShop(const MercList &ml, int num, const char * name, int credit)
{
	this->num = num;
	strcpy_s(this->name, name);
	this->credit = credit;
	
	this->merclist = ml;		// 调用 运算符重载函数 !!!!!!!!!
}

