#pragma once
#include <fstream>

using namespace std;

class Merc								// 单个商品
{
private:
	char mercName[20];
	int mercPrice;
	int mercSale;

public:
	Merc(const char *name = "", int price = 0, int sale = 0);
	~Merc();
	Merc& operator=(const Merc &m);

public:
	void Show();
	void Print(ofstream &out);
	void setMerc(const char *name, int price, int sale);
	void setPrice(int price);
	void setSale(int changeNum);		// 根据购买的数量 修改售量
	void saveMerc(ofstream &out);

	friend class MercList;
	friend class ShopList;
};

