// �����б�

#pragma once
#include "Shop.h"

//-------------------- ���̽�㶨�� --------------------

struct ShopNode
{
	Shop data;
	ShopNode* next;
};


//-------------------- ���������� --------------------

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
	Shop* GetShop(int shopnum);				// �ҵ��ƶ���ŵ��̵�
	void PrintShopList();




};

