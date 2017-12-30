#include "ProductList.h"
#include <cstring>

//-------------------- 商品结构定义 --------------------

void MerchandiseNode::SetMercNode(const char * name, int price, int sales)
{
	strcpy_s(data.name, name);
	data.price = price;
	data.salesvolume = sales;

	next = NULL;
}



//--------------------- 商品链表 函数实现 ---------------------

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
