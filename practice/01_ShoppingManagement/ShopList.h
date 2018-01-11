// �����б�

#pragma once
#include "Shop.h"

//-------------------- ���̽�㶨�� --------------------

struct SNode
{
	Shop data;
	SNode* next;
};

struct DuData
{
	int shopNum;
	char shopName[20];
	int credit;
	char mName[20];
	int price;
	int sale;

	void SetData(int snum, const char* sname, int scredit, const char* mname, int mprice, int msale);
	void ShowDuData();
};

struct DuInfoNode
{
	DuData data;
	DuInfoNode* prior;
	DuInfoNode* next;
};

//-------------------- ���������� --------------------

class ShopList
{
private:
	SNode* head;
	SNode* tail;

	DuInfoNode* duHead;
	DuInfoNode* duTail;

public:
	ShopList();
	~ShopList();

public:
	void AppendShop(const char* name, int credit);

	void DelShop(int num);

	bool Empty();

	void ShowAllShop();

	SNode* GetShop(int num);

	void CreatDuList(const char* name);				// ��������Ϊ name ����Ʒ��˫��ѭ����Ϣ����

	void ShowDuList();								// ��ʾ������Ϣ

	void FileAppendSList(ifstream &in);

	void WriteToFile(ofstream &out);

	void SaveData(const char* filename);
};
