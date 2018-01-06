#pragma once
#include "Merc.h"

#define INITSIZE 20
#define SIZEINCREMENT 10

class MercList			// ˳���
{
private:
	Merc * mercs;
	int len;
	int size;

public:
	MercList(int maxsize = INITSIZE);
	~MercList();

public:
	bool isIn(const char *name);											// �Ƿ񺬸���Ʒ
	int ListLength();
	Merc & getMerc(const char* name);										// ����������Ʒ������
	void showAllMercs();
	void appendMerc(const char *name, int price, int sale);
	bool deleteMerc(const char *name);
	void InitMercList(ifstream &in);
	void SaveMercList(ofstream &out);
};

