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

	void PrintMerc();
	void SetMerc(const char *name = "", int price = 0, int sales = 0);			// Ϊ��Ʒ����ʼֵ
};

struct MerchandiseNode		// ��Ʒ���
{
	Merchandise data;
	MerchandiseNode* next;

	void SetMercNode(Merchandise m = { "",0,0 });		// Ϊ��Ʒ��㸳ֵ
};


//--------------------- ��Ʒ���� ---------------------

class MercList			// ��Ʒ����
{
private:
	MerchandiseNode* head;
	MerchandiseNode* tail;

public:
	MercList();
	~MercList();
	MercList(const MercList& list);
	
public:
	MercList & operator=(const MercList &merclist);

public:
	void PrintMercList();								// ��������е�������Ʒ
	
	void AppendMerc(Merchandise m);						// ����׷����Ʒ
	void DeleteMerc(const char* name);					// ɾ��ָ�����Ƶ���Ʒ
	MerchandiseNode* GetMercNode(const char* name);		// ������Ʒ���

};

