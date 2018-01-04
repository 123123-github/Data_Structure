#include "MerchandiseList.h"
#include <cstring>
#include <iostream>
using namespace std;

//-------------------- 商品结构定义 --------------------

void Merchandise::SetMerc(const char * name, int price, int sales)
{
	strcpy_s(this->name, NAMESIZE_MERC, name);
	this->price = price;
	this->salesvolume = sales;
}

void Merchandise::PrintMerc()
{
	cout << "商品名:\t" << this->name << '\n'
		<< "价格:\t" << this->price << '\t'
		<< "销售量:\t" << this->salesvolume << '\n';
}

void MerchandiseNode::SetMercNode(Merchandise m)			// 拷贝结点值
{
	strcpy_s(data.name, m.name);
	data.price = m.price;
	data.salesvolume = m.salesvolume;

	next = NULL;
}


//--------------------- 商品链表 成员函数实现 ---------------------

MercList::MercList()
{
	head = new MerchandiseNode;
	head->SetMercNode();		// 初始化一下
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

	MerchandiseNode *p;		// 指向赋值链
	MerchandiseNode *s;		// 用于分配空间

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
	if (this == &merclist)			// 处理自身的赋值
		return *this;

	this->~MercList();				// 释放原空间

	head = new MerchandiseNode;
	head->SetMercNode();
	head->next = NULL;
	tail = head;

	MerchandiseNode *p;		// 指向赋值链
	MerchandiseNode *s;		// 用于分配空间

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
	MerchandiseNode* s;							// 需要申请空间 而不是定义局部变量
	s = new MerchandiseNode;
	s->SetMercNode(m);

	tail->next = s;
	tail = s;
}

void MercList::DeleteMerc(const char * name)
{
	MerchandiseNode *p, *q;		// p 在前 q 在后
	q = head->next;

	while (q && (strcmp(q->data.name, name) != 0));
	{
		p = q;
		q = q->next;
	}

	if (q)		// 要删除的商品存在时
	{
		p->next = q->next;

		/* 此处输出信息 或处理要删除的结点 */
		delete q;
	}
	else
	{
		cout << "该商品不存在 请重新输入\n";
	}
}

MerchandiseNode * MercList::GetMercNode(const char * name)
{

	return nullptr;
}

