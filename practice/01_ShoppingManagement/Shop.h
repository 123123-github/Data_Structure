//����
#pragma once
#include "MercList.h"

//-------------------- ���̽ṹ���� --------------------

class Shop
{
private:
	int num;							// ���
	char name[20];						// ������
	int credit;							// ������
	MercList merclist;					// ��Ʒ�б�

public:
	Shop();
	~Shop();

public:
	MercList * GetMercList();
	void SetShop(int num, const char* name, int credit);
	void ShowShop();

	friend class ShopList;
};

