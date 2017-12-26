#include <iostream>
#include "HashTable.h"
using namespace std;

//-------------------- ��ϣ���ຯ��ʵ�� -----------------------

HashTable::HashTable(int size)
{
	count = 0;
	tablesize = size;
	Hash = nullptr;

	elem = new int[size];
	for (int i = 0;i < tablesize;++i)
		elem[i] = NULLKEY;
}

HashTable::HashTable(const HashTable & H)
{
	count = H.count;
	Hash = H.Hash;
	tablesize = H.tablesize;

	elem = new int[tablesize];
	for (int i = 0; i < tablesize; i++)
		elem[i] = H.elem[i];
}

HashTable::~HashTable()
{
	count = -1;
	tablesize = -1;
	Hash = nullptr;

	delete[] elem;
	elem = nullptr;
}


//------------ �������� -----------

Status HashTable::Search(int key, int & p, int & c)
{
	int start;

	p = Hash(key);
	start = p;
	c = 0;

	while (elem[p] != NULLKEY && elem[p] != key)				//1. ���� �� ����� -> �����ͻ
		collision(start, p, ++c);

	if (elem[p] == NULLKEY)										//2. ������ -> ����û���������
		return UNSUCCESS;
	else														//3. ���� �� ��� -> �ҵ�
		return SUCCESS;
}

Status HashTable::Insert(int e)
{
	int p;										// ����λ�� 
	int c = 0;									//��ͻ����

	if (Search(e, p, c))						// �ҵ�˵��Ԫ���ظ�
		return DUPLICATE;
	else										// û���ظ� �ҵ�����λ��
	{
		elem[p] = e;
		count++;

		return OK;
	}
}

void HashTable::SetHash(int(*HashFunc)(int))
{
	Hash = HashFunc;
}

void HashTable::collision(int start, int & p, int c)
{
	int d;

	if (c % 2 == 0)									// ż���γ�ͻ
		d = -c * c / 4;
	else											// �����γ�ͻ
		d = (c + 1)*(c + 1) / 4;

	p = (start + d + tablesize) % tablesize;					// ȷ������λ��
}

void HashTable::PrintHashTable()
{
	for (int i = 0; i < tablesize; i++)
	{
		cout << elem[i] << '\t';
	}
	cout << endl;
}
