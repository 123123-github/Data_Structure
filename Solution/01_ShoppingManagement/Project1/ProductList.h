// ������Ʒ�б�

#pragma once
#include <iostream>
using namespace std;

//-------------------- ��Ʒ�ṹ���� --------------------

#define NAMESIZE_MERC 20

struct Merchandise			// ��Ʒ
{
	char name[NAMESIZE_MERC];			// ��Ʒ��
	int price;							// �۸�
	int salesvolume;					// ������
};

struct MerchandiseNode		// ��Ʒ���
{
	Merchandise data;
	Merchandise* next;

	void SetMercNode(const char *name = "", int price = 0, int sales = 0);		// Ϊ��Ʒ��ֵ
};



//--------------------- ��Ʒ���� ---------------------

class ProductList			// ��Ʒ����
{
private:
	MerchandiseNode* head;
	MerchandiseNode* tail;

public:
	ProductList();
	ProductList(const ProductList& list);
	~ProductList();

public:


};

