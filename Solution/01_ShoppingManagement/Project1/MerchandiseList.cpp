#include "MerchandiseList.h"
#include <cstring>
#include <iostream>
using namespace std;

//-------------------- ��Ʒ�ṹ���� --------------------

void Merchandise::SetMerc(const char * name, int price, int sales)
{
	strcpy_s(this->name, NAMESIZE_MERC, name);
	this->price = price;
	this->salesvolume = sales;
}

void Merchandise::PrintMerc()
{
	cout << "��Ʒ��:\t" << this->name << '\n'
		<< "�۸�:\t" << this->price << '\t'
		<< "������:\t" << this->salesvolume << '\n';
}

void MerchandiseNode::SetMercNode(Merchandise m)			// �������ֵ
{
	strcpy_s(data.name, m.name);
	data.price = m.price;
	data.salesvolume = m.salesvolume;

	next = NULL;
}


//--------------------- ��Ʒ���� ��Ա����ʵ�� ---------------------

MercList::MercList()
{
	head = new MerchandiseNode;
	head->SetMercNode();		// ��ʼ��һ��
	head->next = NULL;

	tail = head;
}

MercList::~MercList()
{
	MerchandiseNode *p, *q;

	p = head;
	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	head = tail = NULL;
}

MercList::MercList(const MercList & list)
{
	head = new MerchandiseNode;
	head->SetMercNode();
	head->next = NULL;
	tail = head;

	MerchandiseNode *p;		// ָ��ֵ��
	MerchandiseNode *s;		// ���ڷ���ռ�

	p = list.head->next;
	while (p)
	{
		s = new MerchandiseNode;
		s->SetMercNode(p->data);

		tail->next = s;
		tail = s;

		p = p->next;
	}
}


MercList & MercList::operator=(const MercList & merclist)
{
	if (this == &merclist)			// ��������ĸ�ֵ
		return *this;

	this->~MercList();				// �ͷ�ԭ�ռ�

	head = new MerchandiseNode;
	head->SetMercNode();
	head->next = NULL;
	tail = head;

	MerchandiseNode *p;		// ָ��ֵ��
	MerchandiseNode *s;		// ���ڷ���ռ�

	p = merclist.head->next;
	while (p)
	{
		s = new MerchandiseNode;
		s->SetMercNode(p->data);

		tail->next = s;
		tail = s;

		p = p->next;
	}

	return *this;
}


void MercList::PrintMercList()
{
	MerchandiseNode* p;
	p = this->head->next;
	
	while (p)
	{
		p->data.PrintMerc();
		p = p->next;
	}
}

void MercList::AppendMerc(Merchandise m)
{
	MerchandiseNode* s;							// ��Ҫ����ռ� �����Ƕ���ֲ�����
	s = new MerchandiseNode;
	s->SetMercNode(m);

	tail->next = s;
	tail = s;
}

void MercList::DeleteMerc(const char * name)
{
	MerchandiseNode *p, *q;		// p ��ǰ q �ں�
	q = head->next;

	while (q && (strcmp(q->data.name, name) != 0));
	{
		p = q;
		q = q->next;
	}

	if (q)		// Ҫɾ������Ʒ����ʱ
	{
		p->next = q->next;

		/* �˴������Ϣ ����Ҫɾ���Ľ�� */
		delete q;
	}
	else
	{
		cout << "����Ʒ������ ����������\n";
	}
}

MerchandiseNode * MercList::GetMercNode(const char * name)
{

	return nullptr;
}

