#include "ShopList.h"
#include <string>
#include <iostream>
using namespace std;

#define MENU_NUM 10

int menu_select();		// 菜单界面

string menu[10] =
{
	"1.菜单",
	"1.菜单",
	"1.菜单",
	"1.菜单"
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
			cout << "退出";

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
		for (int i = 0; i < MENU_NUM; i++)		// 输出菜单
			cout << menu[i] << endl;

		cout << "请输入菜单选项\n";
		cin >> choice;

	} while (choice<0 || choice>MENU_NUM);

	return choice;
}
