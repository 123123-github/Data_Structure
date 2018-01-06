#include "Shop.h"
#include "MercList.h"
#include <iostream>
using namespace std;

Shop::Shop()
{
}

Shop::~Shop()
{
}

MercList * Shop::GetMercList()
{
	return &merclist;
}

void Shop::SetShop(int num, const char * name, int credit)
{
	this->num = num;
	this->credit = credit;
	strcpy_s(this->name, name);
}

void Shop::ShowShop()
{
	cout << this->num << '\t' << this->name << '\t' << this->credit << '\n';
	this->merclist.showAllMercs();
	cout << '\n';
}
