#include "ShopList.h"
#include <fstream>
#include<iostream>
using namespace std;

ShopList::ShopList()
{
	head = new SNode;
	tail = head;

	head->next = NULL;
	head->data.num = 0;

	duHead = new DuInfoNode;
	duHead->next = duHead;
	duHead->prior = duHead;
	
	duTail = duHead;
}

ShopList::~ShopList()
{
	SNode *p, *q;
	p = head;
	q = p;

	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	head = tail = NULL;

	
	DuInfoNode *m, *n;
	m = n = duHead->next;

	while (n != duHead)
	{
		m = n->next;
		delete p;
		p = q;
	}

	duHead = NULL;
		
	
}

void ShopList::AppendShop(const char * name, int credit)
{
	SNode *s;

	s = new SNode;
	s->next = NULL;

	int num;
	num = ++(tail->data.num);
	s->data.SetShop(num, name, credit);

	tail->next = s;
	tail = s;

	tail->next = NULL;
}

void ShopList::DelShop(int num)
{
	int i = 1;
	SNode *p, *q;
	p = head;
	q = head->next;

	while (q && i<num)
	{
		p = q;
		q = q->next;
		++i;
	}
	if (i == num)
	{
		if (q == tail)
			tail = p;

		p->next = q->next;
		delete q;
		q = NULL;
	}
}

bool ShopList::Empty()
{
	if (head == tail)
		return true;
	else
		return false;
}

void ShopList::ShowAllShop()
{
	SNode *p;
	p = head->next;

	while (p)
	{
		p->data.ShowShop();
		p = p->next;
	}
}

SNode * ShopList::GetShop(int num)
{
	int i = 1;
	SNode *p;
	p = head->next;

	while (i < num)
	{
		p = p->next;
		++i;
	}

	return p;
}

void ShopList::CreatDuList(const char * name)
{
	SNode *p;
	p = head->next;

	Merc m;
	DuInfoNode *s;

	while (p)
	{
		if (p->data.merclist.isIn(name))		// 如果店铺有该商品 加入双向链表
		{
			m = p->data.merclist.getMerc(name);

			s = new DuInfoNode;
			s->data.SetData
			(
				p->data.num, p->data.name, p->data.credit,
				m.mercName, m.mercPrice, m.mercSale
			);
			s->next = duHead;
			s->prior = duTail;

			duTail->next = s;
			duHead->prior = s;

			duTail = s;
		}
		p = p->next;
	}
}

void ShopList::ShowDuList()
{
}

void ShopList::FileAppendSList(ifstream & in)
{
	SNode *s;
	char shopName[20];
	int shopCredit;
	int shopNum;
	MercList* mListPtr;

	shopNum = tail->data.num;

	in >> shopName;
	while (!in.eof())
	{
		in >> shopCredit;

		s = new SNode;
		s->next = NULL;

		s->data.SetShop(++shopNum, shopName, shopCredit);
		mListPtr = s->data.GetMercList();
		mListPtr->InitMercList(in);

		cout << "追加店铺成功!\n";

		in >> shopName;
	}

	cout << "\n商铺信息读取完毕\n";
}

void ShopList::WriteToFile(ofstream & out)
{
	SNode*p;
	p = head->next;

	while (p)
	{
		out << p->data.num << '\t'
			<< p->data.name << '\t'
			<< p->data.credit << '\n';
		p->data.merclist.SaveMercList(out);

		out << '\n';
		p = p->next;
	}
}

void ShopList::SaveData(const char * filename)
{
	ofstream out;
	out.open(filename);
	if (out.fail())
	{
		cout << "保存数据异常\n";
		return;
	}

	SNode*p;
	p = head->next;

	while (p)
	{
		out << p->data.num << '\t'
			<< p->data.name << '\t'
			<< p->data.credit << '\n';
		p->data.merclist.SaveMercList(out);

		out << '\n';
		p = p->next;
	}
	out.close();
}

void DuData::SetData(int snum, const char * sname, int scredit, const char * mname, int mprice, int msale)
{
	shopNum = snum;
	strcpy_s(shopName, sname);
	credit = scredit;

	strcpy_s(mName, mname);
	price = mprice;
	sale = msale;
}
