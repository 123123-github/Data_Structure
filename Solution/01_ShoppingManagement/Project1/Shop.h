//����

#pragma once
#include "MerchandiseList.h"


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
	Shop(const Shop& S);

public:
	int GetNum();						// ����̵���
	void SetNum(int num);				// �����̵���
	void SetShop(const MercList &merclist, int num = 0, const char* name = "", int credit = 0);						// Ϊ�̵���Ϣ����ʼֵ
	void PrintShop();					// ���������Ϣ
};

