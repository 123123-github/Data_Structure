#include "ProductList.h"
#include <cstring>

//-------------------- ��Ʒ�ṹ���� --------------------

void MerchandiseNode::SetMercNode(const char * name, int price, int sales)
{
	strcpy_s(data.name, name);
	data.price = price;
	data.salesvolume = sales;

	next = NULL;
}



//--------------------- ��Ʒ���� ����ʵ�� ---------------------

ProductList::ProductList()
{
	head = new MerchandiseNode;
	head->SetMercNode();

	tail = head;



}

ProductList::ProductList(const ProductList & list)
{
}


ProductList::~ProductList()
{
}
