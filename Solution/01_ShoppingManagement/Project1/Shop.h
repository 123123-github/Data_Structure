//����

#pragma once
#include "ProductList.h"


//-------------------- ���̽ṹ���� --------------------




class Shop
{
public:
	char num[10];						// ���
	char name[20];						// ������
	int credit;							// ������
	ProductList merchandiseList;		// ��Ʒ�б�




public:
	Shop();
	~Shop();
};

