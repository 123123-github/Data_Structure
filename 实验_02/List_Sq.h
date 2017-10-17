// ADT List ��������
// ˳��ʵ�� (C++�ṹ��)
#include <iostream>
using namespace std;
//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
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

//ʮ���� ��������ʵ�֣�

//����ձ�L
Status InitList_Sq(SqList &L)
{
	L.elem = new int[LIST_INIT_SIZE];
	if (L.elem == NULL)
		exit(OVERFLOW);

	L.length = 0;
	L.listsize = LIST_INIT_SIZE;

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
//������Ϊ�ձ�
Status ClearList_Sq(SqList &L)
{
	if (L.elem == NULL)
		return ERROR;

	L.length = 0;

	return OK;
}
//��Ϊ�շ���TRUE�����򷵻�FALSE
Status ListEmpty_Sq(SqList L)
{
	if (L.elem == NULL)
		return ERROR;

	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}
//���ر�ĳ���
int ListLength_Sq(SqList L)
{
	if (L.elem == NULL)
		return ERROR;

	return L.length;
}
//��e����L�еĵ�i��ֵ���ɹ�ʱ��������OK�����򷵻�FALSE
Status GetElem_Sq(SqList L, int i, int &e)
{
	if (i < 1 || i>L.length)
		return FALSE;

	e = *(L.elem + i - 1);

	return OK;
}
//����L�е�һ����e��ȵ�Ԫ�ص�λ�򣬲�����ʱ����0
int LocateElem_Sq(SqList L, int e)
{
	if (L.elem == NULL)
		return ERROR;

	for (int i = 0;i <= L.length - 1;i++)
		if (L.elem[i] == e)
			return i + 1;

	return 0;
}
//�� pre_e ����Ԫ�� cur_e ��ǰ���������ɹ�����OK�����򷵻�ERROR
Status PriorElem_Sq(SqList L, int cur_e, int &pre_e)
{
	if (L.elem == NULL)
		return ERROR;

	int i = LocateElem_Sq(L, cur_e);
	if (i < 2 || i> L.length)
		return ERROR;

	pre_e = *(L.elem + i - 2);

	return	OK;
}
//�� next_e ����Ԫ�� cur_e �ĺ�̣������ɹ�����OK�����򷵻�ERROR
Status NextElem_Sq(SqList L, int cur_e, int &next_e)
{
	if (L.elem == NULL)
		return ERROR;

	int i = LocateElem_Sq(L, cur_e);
	if (i < 1 || i> L.length - 1)
		return ERROR;

	next_e = *(L.elem + i);

	return	OK;
}
//�����Ա�ĵ�i��λ�ò���e;���ɹ�����OK�����򷵻�ERROR
Status ListInsert_Sq(SqList &L, int i, int e)
{
	if (i<1 || i> L.length + 1) //�ж�i�Ƿ�Ϸ�
		return ERROR;

	//�����Ա�����������չ���Ա���
	if (L.length == L.listsize)
	{
		//�����¿ռ�
		int* newbase;
		newbase = new int[L.length + LISTINCREMENT];
		if (newbase == NULL)
			exit(OVERFLOW);

		//�ƶ�Ԫ��
		for (int i = 0;i < L.length;i++)
			newbase[i] = L.elem[i];

		//�������Ա�����ָ��ָ��,�޸����Ա��Ȳ���
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}

	//�ƶ�Ԫ��
	int j;
	for (j = L.length;j >= i;j--)
		*(L.elem + j) = *(L.elem + j - 1);

	//����Ԫ�أ����޸����Ա��ȣ�����+1��
	*(L.elem + i - 1) = e;
	L.length++;

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
//�������Ա�
Status ListTraverse_Sq(SqList L)
{

}

