#include "ProductList.h"

int main()
{
	MerchandiseNode *p;

	p = new MerchandiseNode;

	char c[10] = "GO";

	p->SetMercNode();

	cout << p->data.name << p->data.price << '\n';

	delete p;


	system("pause");
	return 0;
}