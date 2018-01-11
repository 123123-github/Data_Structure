#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "ShopList.h"
#include "MercList.h"
using namespace std;

#define MENU_NUM 12

int menu_select();													// 菜单选择函数

void screen();														// 菜单选择界面

void appendShop(ShopList &sList);									// 1.商铺-添加商铺

void delShop(ShopList &sList);										// 2.商铺-删除商铺

void showAllShop(ShopList &sList);									// 3.商铺-显示所有商铺

void addMerc(ShopList &sList);										// 4.商品-增加商品

void delMerc(ShopList &sList);										// 5.商品-删除商品

void modMercSale(ShopList &sList);									// 6.商品-修改商品价格

void searchMerc(ShopList &sList);									// 7.商品-查询商品 (双向链表)

void buyMerc(ShopList &sList);										// 8.商品-购买商品

void readFromFile(ShopList &sList);									// 9.商铺-导入商铺信息

void writeToFile(ShopList &sList);									// 10.商铺-导出商铺信息

void appendMercs(ShopList &sList);									// 11.批量输入商铺信息（输入#号结束）

char Quit(ShopList &sList);											// 0.退出


//-------------------- 主函数 ---------------------

int main()
{
	int choice;

	ShopList sList;

	while (true)
	{
		switch (choice = menu_select())
		{
		case 1:
			appendShop(sList);
			system("pause");
			break;
		case 2:
			delShop(sList);
			system("pause");
			break;
		case 3:
			showAllShop(sList);
			system("pause");
			break;
		case 4:
			addMerc(sList);
			system("pause");
			break;
		case 5:
			delMerc(sList);
			system("pause");
			break;
		case 6:
			modMercSale(sList);
			system("pause");
			break;
		case 7:
			searchMerc(sList);
			system("pause");
			break;
		case 8:
			buyMerc(sList);
			system("pause");
			break;
		case 9:
			readFromFile(sList);
			system("pause");
			break;
		case 10:
			writeToFile(sList);
			system("pause");
			break;
		case 11:
			appendMercs(sList);
			system("pause");
			break;
		case 0:
			if (Quit(sList) != 'y')
				continue;
		}
		if (choice == 0)
			break;
	}
	return 0;
}


//-------------------- 菜单函数 ---------------------

int menu_select()
{
	int choice;
	char temp[80];

	while (true)
	{
		screen();
		cin >> choice;

		while (cin.rdstate())
		{
			cin.clear();
			cin.getline(temp, 80);
			cout << temp << "为非法输入\n";
			cout << "请重新输入您的选择：\n";
			cin >> choice;
		}
		if (choice<0 || choice>MENU_NUM)
		{
			cout << "超出输入范围，请重新输入\n";
			system("pause");
		}
		else
			return choice;
	}
}

void screen()
{
	string m[MENU_NUM] =
	{
		" 1.商铺-添加商铺",
		" 2.商铺-删除商铺",
		" 3.商铺-显示所有商铺",
		" 4.商品-增加商品",
		" 5.商品-删除商品",
		" 6.商品-修改商品价格",
		" 7.商品-查询商品",
		" 8.商品-购买商品",
		" 9.商铺-导入商铺信息",
		"10.商铺-导出商铺信息",
		"11.批量输入商铺信息（输入#号结束）",
		" 0.退出"
	};

	system("cls");
	cout << "\n\n********************购物网站信息管理********************\n\n";
	for (int i = 0;i < MENU_NUM;i++)
		cout << "\t\t" << m[i] << '\n';
	cout << "\n****************************************************\n";
	cout << "请输入选择：";
}


//-------------------- 功能函数 ---------------------

void appendShop(ShopList &sList)
{
	char name[20];
	int credit;

	cout << "请依次输入：商铺名，信誉度\n";
	cin >> name >> credit;

	sList.AppendShop(name, credit);
}

void delShop(ShopList & sList)
{
	int num;

	cout << "请输入要删除商铺的编号:\n";
	cin >> num;

	sList.DelShop(num);
}

void showAllShop(ShopList & sList)
{
	if (sList.Empty())
		cout << "暂时没有店铺\n";
	else
	{
		cout << "商店编号\t" << "商店名\t" << "信誉度\n";
		sList.ShowAllShop();
	}
}

void addMerc(ShopList & sList)
{
	int shopNum;

	char name[20];
	int price;
	int sale;
	
	cout << "请输入添加商品的店铺编号\n";
	cin >> shopNum;
	
	cout << "请输入商品信息：名称 价格 销量\n";
	cin >> name >> price >> sale;

	SNode* p;
	MercList *mListPtr;

	p = sList.GetShop(shopNum);
	mListPtr = p->data.GetMercList();
	mListPtr->appendMerc(name, price, sale);
}

void delMerc(ShopList & sList)
{
	int shopNum;
	char name[20];

	cout << "请输入添加商品的店铺编号\n";
	cin >> shopNum;

	cout << "请输入要删除的商品名称\n";
	cin >> name;

	SNode* p;
	MercList *mListPtr;

	p = sList.GetShop(shopNum);
	mListPtr = p->data.GetMercList();
	mListPtr->deleteMerc(name);
}

void modMercSale(ShopList & sList)
{
	int shopNum;

	char name[20];
	int newPrice;

	cout << "请输入添加商品的店铺编号\n";
	cin >> shopNum;

	cout << "请输入要修改价格商品的名称及修改后的价格\n";
	cin >> name >> newPrice;

	SNode* p;
	MercList *mListPtr;

	p = sList.GetShop(shopNum);
	mListPtr = p->data.GetMercList();
	mListPtr->getMerc(name).setPrice(newPrice);
}

void searchMerc(ShopList & sList)
{
	// 1.建立双向循环链表
	// 2.显示结果
	
	char name[20];

	cout << "请输入所要查询的商品名称\n";
	cin >> name;

	sList.CreatDuList(name);
	sList.ShowDuList();
}

void buyMerc(ShopList & sList)
{
	int shopNum;

	char name[20];
	int buyNum;

	cout << "请输入购买商品的店铺编号\n";
	cin >> shopNum;

	cout << "请输入商品名称和购买数量\n";
	cin >> name >> buyNum;

	SNode* p;
	MercList *mListPtr;

	p = sList.GetShop(shopNum);
	mListPtr = p->data.GetMercList();
	mListPtr->getMerc(name).setSale(buyNum);
}

void readFromFile(ShopList & sList)				// 读取并追加至现有商铺链表
{
	char filename[20] = "ShopData.txt";	 /* 测试数据 */

	ifstream in;
	cout << "请输入文件名\n";
	//cin >> filename;
	
	in.open(filename);
	if (in.fail())
	{
		cout << "文件打开失败!\n";
		system("pause");
		return;
	}

	sList.FileAppendSList(in);

	in.close();
}

void writeToFile(ShopList & sList)
{
	char filename[20] = "TestWrite.txt";

	cout << "请输入输出文件名\n";
	//cin >> filename;

	ofstream out;
	out.open(filename);
	if (out.fail())
	{
		cout << "文件打开失败!\n";
		system("pause");
		return;
	}

	sList.WriteToFile(out);

	out.close();
}

void appendMercs(ShopList & sList)
{
	int shopNum;

	cout << "请输入添加商品的店铺编号\n";
	cin >> shopNum;

	SNode* p;
	MercList *mListPtr;

	p = sList.GetShop(shopNum);
	mListPtr = p->data.GetMercList();


	cout << "请输入商品信息：名称 价格 销量 (#号结束)\n";
	
	char name[20];
	int price;
	int sale;
	
	cin >> name;
	while (strcmp(name, "#") != 0)
	{
		cin>> price >> sale;
		mListPtr->appendMerc(name, price, sale);

		cout << "追加商品成功\n";

		cin >> name;
	}
}

char Quit(ShopList & sList)
{
	char quit;
	cout << "是否退出？请输入y/n\n";
	cin >> quit;

	sList.SaveData("save.txt");			//  保存信息

	return quit;
}
