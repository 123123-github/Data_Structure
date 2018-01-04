#include "ShopList.h"


//--------------------- 店铺链表 函数实现 ---------------------

ShopList::ShopList()
{
	head = new ShopNode;
	head->next = NULL;

	tail = head;

	head->data.SetNum(0);
}

ShopList::ShopList(const ShopList & SL)
{

}

ShopList::~ShopList()
{
	ShopNode *p, *q;

	p = head;
	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	head = tail = NULL;
}



void ShopList::AppendShop(Shop S)
{
	ShopNode* s;
	s = new ShopNode;
	s->data = S;
	s->next = NULL;				// 分配结点

	int num = tail->data.GetNum();
	++num;

	tail->next = s;
	tail = s;

	tail->data.SetNum(num);		// 编号加一
}

void ShopList::DeleteShop(int shopnum)
{
	ShopNode* p, *q;		// p 在前 q 在后
	p = head;
	q = head->next;

	int num;

	while (q)
	{
		num = q->data.GetNum();
		if (num == shopnum)
			break;

		p = q;
		q = q->next;
	}
	if (q)		// 该编号商铺存在时
	{
		/* 可在此处加上删除结点的提示等信息 */

		p->next = q->next;		// 删除该结点
		delete q;
	}
	else
	{
		cout << "该商铺不存在，请重新输入\n";
	}
}

Shop* ShopList::GetShop(int shopnum)
{
	ShopNode* p, *q;		// p 在前 q 在后
	p = head;
	q = head->next;

	int num;

	while (q)
	{
		num = q->data.GetNum();
		if (num == shopnum)
			break;

		p = q;
		q = q->next;
	}
	
	if (q)		// 该编号商铺存在时
	{
		Shop *s;
		s = &(q->data);

		return s;
	}
	else
	{
		return NULL;
	}
}

void ShopList::PrintShopList()
{
	ShopNode *p;
	p = head->next;

	while (p)
	{
		p->data.PrintShop();
		p = p->next;
	}
}
