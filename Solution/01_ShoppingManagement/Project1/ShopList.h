// �����б�

#pragma once
#include "Shop.h"

//-------------------- ���̽�㶨�� --------------------

struct ShopNode
{
	Shop data;
	Shop* next;
};


//-------------------- ���������� --------------------

class ShopList
{
public:
	ShopNode* head;
	ShopNode* tail;


public:
	ShopList();
	~ShopList();
};

