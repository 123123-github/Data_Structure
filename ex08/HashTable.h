// ��ϣ��
// ����̽����ɢ�д����ͻ
#pragma once
#include "Status.h"

//-------------------- �궨�� ------------------------

#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

#define NULLKEY 2147483647i32


//-------------------- ��ϣ���� -----------------------

class HashTable
{
private:
	int *elem;														//��ϣ���Ա�
	int count;														//��������
	int tablesize;													//��
	int(*Hash)(int);												//��ϣ����

public:
	HashTable(int size);
	HashTable(const HashTable& H);
	~HashTable();

public:
	Status Search(int key, int &p, int &c);							// key:������Ԫ�� p:δ�ҵ������λ�� c:��ͻ����
	Status Insert(int e);											// ����Ԫ��
	void SetHash(int(*HashFunc)(int));								// ���ù�ϣ����
	void collision(int start, int &p, int c);						//����̽����ɢ��

public:
	void PrintHashTable();											// ������⺯��
};