#include "MercList.h"
#include <cstring>
#include <iostream>
using namespace std;



MercList::MercList(int maxsize)
{
	size = maxsize;
	len = 0;

	mercs = new Merc[size];
}

MercList::~MercList()
{
	delete[] mercs;
	mercs = NULL;

	size = -1;
	len = -1;
}


bool MercList::isIn(const char * name)
{
	for (int i = 0; i < len; i++)
		if (strcmp(mercs[i].mercName, name) == 0)
			return true;

	return false;
}

int MercList::ListLength()
{
	return len;
}

Merc & MercList::getMerc(const char * name)
{
	int i;

	for (i = 0; i < len; i++)
		if (strcmp(mercs[i].mercName, name) == 0)
			break;

	return mercs[i];
}

void MercList::showAllMercs()
{
	for (int i = 0;i < len;++i)
		mercs[i].Show();

	cout << endl;
}

void MercList::appendMerc(const char * name, int price, int sale)
{
	if (len >= size)			// ���Ա�����  ��չ�ռ�
	{
		Merc* newbase;
		newbase = new Merc[size + SIZEINCREMENT];		// �����¿ռ�

		for (int i = 0; i < len; i++)					// ��������
			newbase[i] = mercs[i];

		delete[] mercs;									// �ͷžɿռ�
		
		mercs = newbase;

		size += SIZEINCREMENT;
	}

	mercs[len].setMerc(name, price, sale);
	++len;
}

bool MercList::deleteMerc(const char * name)
{
	if (!isIn(name))
		return false;

	int p;
	for ( p = 0; p < len; p++)
		if (strcmp(mercs[p].mercName, name))
			break;

	for (int i = p; i < len - 1; i++)
		mercs[i] = mercs[i + 1];

	return true;
}

void MercList::InitMercList(ifstream & in)
{
	char name[20];
	int price;
	int sale;

	in >> name;
	while (strcmp(name, "#") != 0)
	{
		in >> price >> sale;
		appendMerc(name, price, sale);
		in >> name;
	}
}

void MercList::SaveMercList(ofstream & out)
{
	for (int i = 0; i < len; i++)
		mercs[i].saveMerc(out);
}



