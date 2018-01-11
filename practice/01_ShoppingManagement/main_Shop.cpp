#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "ShopList.h"
#include "MercList.h"
using namespace std;

#define MENU_NUM 12

int menu_select();													// �˵�ѡ����

void screen();														// �˵�ѡ�����

void appendShop(ShopList &sList);									// 1.����-�������

void delShop(ShopList &sList);										// 2.����-ɾ������

void showAllShop(ShopList &sList);									// 3.����-��ʾ��������

void addMerc(ShopList &sList);										// 4.��Ʒ-������Ʒ

void delMerc(ShopList &sList);										// 5.��Ʒ-ɾ����Ʒ

void modMercSale(ShopList &sList);									// 6.��Ʒ-�޸���Ʒ�۸�

void searchMerc(ShopList &sList);									// 7.��Ʒ-��ѯ��Ʒ (˫������)

void buyMerc(ShopList &sList);										// 8.��Ʒ-������Ʒ

void readFromFile(ShopList &sList);									// 9.����-����������Ϣ

void writeToFile(ShopList &sList);									// 10.����-����������Ϣ

void appendMercs(ShopList &sList);									// 11.��������������Ϣ������#�Ž�����

char Quit(ShopList &sList);											// 0.�˳�


//-------------------- ������ ---------------------

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


//-------------------- �˵����� ---------------------

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
			cout << temp << "Ϊ�Ƿ�����\n";
			cout << "��������������ѡ��\n";
			cin >> choice;
		}
		if (choice<0 || choice>MENU_NUM)
		{
			cout << "�������뷶Χ������������\n";
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
		" 1.����-�������",
		" 2.����-ɾ������",
		" 3.����-��ʾ��������",
		" 4.��Ʒ-������Ʒ",
		" 5.��Ʒ-ɾ����Ʒ",
		" 6.��Ʒ-�޸���Ʒ�۸�",
		" 7.��Ʒ-��ѯ��Ʒ",
		" 8.��Ʒ-������Ʒ",
		" 9.����-����������Ϣ",
		"10.����-����������Ϣ",
		"11.��������������Ϣ������#�Ž�����",
		" 0.�˳�"
	};

	system("cls");
	cout << "\n\n********************������վ��Ϣ����********************\n\n";
	for (int i = 0;i < MENU_NUM;i++)
		cout << "\t\t" << m[i] << '\n';
	cout << "\n****************************************************\n";
	cout << "������ѡ��";
}


//-------------------- ���ܺ��� ---------------------

void appendShop(ShopList &sList)
{
	char name[20];
	int credit;

	cout << "���������룺��������������\n";
	cin >> name >> credit;

	sList.AppendShop(name, credit);
}

void delShop(ShopList & sList)
{
	int num;

	cout << "������Ҫɾ�����̵ı��:\n";
	cin >> num;

	sList.DelShop(num);
}

void showAllShop(ShopList & sList)
{
	if (sList.Empty())
		cout << "��ʱû�е���\n";
	else
	{
		cout << "�̵���\t" << "�̵���\t" << "������\n";
		sList.ShowAllShop();
	}
}

void addMerc(ShopList & sList)
{
	int shopNum;

	char name[20];
	int price;
	int sale;
	
	cout << "�����������Ʒ�ĵ��̱��\n";
	cin >> shopNum;
	
	cout << "��������Ʒ��Ϣ������ �۸� ����\n";
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

	cout << "�����������Ʒ�ĵ��̱��\n";
	cin >> shopNum;

	cout << "������Ҫɾ������Ʒ����\n";
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

	cout << "�����������Ʒ�ĵ��̱��\n";
	cin >> shopNum;

	cout << "������Ҫ�޸ļ۸���Ʒ�����Ƽ��޸ĺ�ļ۸�\n";
	cin >> name >> newPrice;

	SNode* p;
	MercList *mListPtr;

	p = sList.GetShop(shopNum);
	mListPtr = p->data.GetMercList();
	mListPtr->getMerc(name).setPrice(newPrice);
}

void searchMerc(ShopList & sList)
{
	// 1.����˫��ѭ������
	// 2.��ʾ���
	
	char name[20];

	cout << "��������Ҫ��ѯ����Ʒ����\n";
	cin >> name;

	sList.CreatDuList(name);
	sList.ShowDuList();
}

void buyMerc(ShopList & sList)
{
	int shopNum;

	char name[20];
	int buyNum;

	cout << "�����빺����Ʒ�ĵ��̱��\n";
	cin >> shopNum;

	cout << "��������Ʒ���ƺ͹�������\n";
	cin >> name >> buyNum;

	SNode* p;
	MercList *mListPtr;

	p = sList.GetShop(shopNum);
	mListPtr = p->data.GetMercList();
	mListPtr->getMerc(name).setSale(buyNum);
}

void readFromFile(ShopList & sList)				// ��ȡ��׷����������������
{
	char filename[20] = "ShopData.txt";	 /* �������� */

	ifstream in;
	cout << "�������ļ���\n";
	//cin >> filename;
	
	in.open(filename);
	if (in.fail())
	{
		cout << "�ļ���ʧ��!\n";
		system("pause");
		return;
	}

	sList.FileAppendSList(in);

	in.close();
}

void writeToFile(ShopList & sList)
{
	char filename[20] = "TestWrite.txt";

	cout << "����������ļ���\n";
	//cin >> filename;

	ofstream out;
	out.open(filename);
	if (out.fail())
	{
		cout << "�ļ���ʧ��!\n";
		system("pause");
		return;
	}

	sList.WriteToFile(out);

	out.close();
}

void appendMercs(ShopList & sList)
{
	int shopNum;

	cout << "�����������Ʒ�ĵ��̱��\n";
	cin >> shopNum;

	SNode* p;
	MercList *mListPtr;

	p = sList.GetShop(shopNum);
	mListPtr = p->data.GetMercList();


	cout << "��������Ʒ��Ϣ������ �۸� ���� (#�Ž���)\n";
	
	char name[20];
	int price;
	int sale;
	
	cin >> name;
	while (strcmp(name, "#") != 0)
	{
		cin>> price >> sale;
		mListPtr->appendMerc(name, price, sale);

		cout << "׷����Ʒ�ɹ�\n";

		cin >> name;
	}
}

char Quit(ShopList & sList)
{
	char quit;
	cout << "�Ƿ��˳���������y/n\n";
	cin >> quit;

	sList.SaveData("save.txt");			//  ������Ϣ

	return quit;
}
