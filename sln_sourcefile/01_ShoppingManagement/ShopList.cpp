#include "ShopList.h"


//--------------------- �������� ����ʵ�� ---------------------

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
	s->next = NULL;				// ������

	int num = tail->data.GetNum();
	++num;

	tail->next = s;
	tail = s;

	tail->data.SetNum(num);		// ��ż�һ
}

void ShopList::DeleteShop(int shopnum)
{
	ShopNode* p, *q;		// p ��ǰ q �ں�
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
	if (q)		// �ñ�����̴���ʱ
	{
		/* ���ڴ˴�����ɾ��������ʾ����Ϣ */

		p->next = q->next;		// ɾ���ý��
		delete q;
	}
	else
	{
		cout << "�����̲����ڣ�����������\n";
	}
}

Shop* ShopList::GetShop(int shopnum)
{
	ShopNode* p, *q;		// p ��ǰ q �ں�
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
	
	if (q)		// �ñ�����̴���ʱ
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
