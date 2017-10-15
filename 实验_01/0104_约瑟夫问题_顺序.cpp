//Լɪ������
//˳���ʵ��
#include <iostream>
using namespace std;
//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//Status Ϊ�������ͣ�ֵΪ�������״̬����
typedef int Status;

//���Ա���
#define LIST_INIT_SIZE 100 //���Ա�洢�ռ� ��ʼ������
#define LISTINCREMENT 10   //���Ա�洢�ռ� ��������	 
struct SqList
{
	int *elem;
	int length;
	int listsize;
};
//˳�����غ�������

//���쳤��Ϊ n �����Ա� L
Status InitList_Sq(SqList &L,int n)
{
	L.elem = new int[n];
	if (L.elem == NULL)
		exit(OVERFLOW);

	L.length = 0;
	L.listsize = n;

	return OK;
}
//�������Ա�L
Status DestroyList_Sq(SqList &L)
{
	if (L.elem == NULL)
		return ERROR;

	delete[] L.elem;

	return OK;
}
//�����Ա�ĵ�i��λ��ɾ��Ԫ�أ�����e������ֵ;���ɹ�����OK�����򷵻�ERROR
Status ListDelete_Sq(SqList &L, int i, int &e)
{
	if (i<1 || i>L.length) //�ж�i�Ƿ�Ϸ�
		return ERROR;

	//���ص�i��Ԫ�ص�ֵ
	e = *(L.elem + i - 1);
	//�ƶ�Ԫ�ز�ɾ��
	int j;
	for (j = i + 1;j <= L.length;j++)
		*(L.elem + j - 2) = *(L.elem + j - 1);

	//�޸����Ա��ȣ�����-1��
	L.length--;

	return OK;
}

//Լɪ��������� 
int main()
{   //��ʼ������ֵ
	int n, s, m;

	cout << "���������룺Բ������n����ʼ������λ��s�������˱�����m.\n";
	cin >> n >> s >> m;
	cout << endl;
	
	//���쳤��Ϊ n �����Ա���������Ϣ���Գ�ʼλ����Ϊÿ���˵���Ϣ
	SqList L;
	InitList_Sq(L,n);
	for (int i = 0;i < n;i++)
	{
		L.elem[i] = i + 1;
		L.length++;
	}

	//d��¼ÿ�γ����˵����λ�򣨼����ִ�����е�λ��
	//e��¼��������Ϣ
	int d, e=0;

	while (n != 0)
	{
		//���㲢����d��ֵ
		d = (s + m - 1) % n;
		if (d == 0)
			d = n;
		//���� m ���˳���
		ListDelete_Sq(L, d, e);
		cout << "��"<<n<<"�γ�������Ϣ�� " << e << endl;
		//�޸Ķ�����Ϣ
		s = d;
		n--;
	}

	cin.get();
	cin.get();

	return 0;
}