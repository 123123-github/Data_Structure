#include "Shop.h"
#include <iostream>
using namespace std;

//------------ ���Բ����� ȱʡ��Ҳ����----------

Shop::Shop():merclist()				// ���ó�Ա��Ĺ��캯��
{
	this->num = 1;					// ���̱�Ŵ� 1 ��ʼ
	strcpy_s(this->name, "");
	this->credit = 0;
}

Shop::~Shop()						// ���Զ����ó�Ա�����������
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
	cout << "���̱��:\t" << this->num << '\n'
		<< "������\t" << this->name << '\t'
		<< "������\t" << this->credit << '\n';
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
	
	this->merclist = ml;		// ���� ��������غ��� !!!!!!!!!
}

