#include "ShopList.h"
#include <string>
#include <iostream>
using namespace std;

#define MENU_NUM 10

int menu_select();		// �˵�����

string menu[10] =
{
	"1.�˵�",
	"1.�˵�",
	"1.�˵�",
	"1.�˵�"
};


int main()
{
	ShopList SL;


	while (true)
	{





		switch (menu_select())
		{
		case 1:


			break;
		case 2:


			break;
		case 3:

			break;
		case 4:


			break;
		case 5:

			break;
		case 0:
			cout << "�˳�";

			system("pause");
			exit(0);
		}
	}


	

	return 0;
}

int menu_select()
{
	int choice;

	do
	{
		system("cls");
		for (int i = 0; i < MENU_NUM; i++)		// ����˵�
			cout << menu[i] << endl;

		cout << "������˵�ѡ��\n";
		cin >> choice;

	} while (choice<0 || choice>MENU_NUM);

	return choice;
}
