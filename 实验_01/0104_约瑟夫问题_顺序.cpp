//Լɪ������
//˳���ʵ�֣�C++�ṹ�壩

#include <iostream>
#include "List_Sq.h"
using namespace std;

//���庯��ʵ��Լɪ���������
//���룬Χ��Բ�����˵����ģ�����ֱ����λ��
void Fun_Joseohus_Sq(SqList L, int s, int m)
{
	//dΪ�����˵�λ��,nΪ��������г���,delete_elemΪ�����˵���Ϣ
	int d, delete_elem;
	int n = L.length;

	//�����Ȳ�Ϊ0ʱ��Ѱ����һ�����е���
	while (n != 0)
	{
		d = (s + m - 1) % n;
		if (d == 0)
			d = n;

		ListDelete_Sq(L, d, delete_elem);
		cout << delete_elem << '\t';

		s = d;
		n--;
	}
	cout << endl;

	return 0;
}

int main()
{
	//����ĳ�ʼ������ֵ��nΪ��������sΪ��ʼ������λ��mΪ��������������
	int n, s, m;

	cout << "���������룺Բ������n����ʼ������λ��s�������˱�����m.\n";
	cin >> n >> s >> m;
	cout << endl;

	//ʵ����Ϣ�洢
	SqList L;
	cout << "������Χ��Բ�����˵���Ϣ��������λ��" << endl;
	CreatList_Sq(L, n);
	cout << "�����ʼΪ��" << endl;
	ListTraverse_Sq(L);

	//���ý������ĺ���
	cout << "�����˵���Ϣ����Ϊ��" << endl;
	Fun_Joseohus_Sq(L, s, m);

	system("pause");

	return 0;
}