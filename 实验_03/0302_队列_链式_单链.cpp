// ADT Queue ��������
// ��ʽʵ�� (C++�ṹ��)

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

//��ʽ���ж��壬��������
struct QNode
{
	int data;
	QNode *next;
};

struct LinkQueue
{
	QNode *front;
	QNode *rear;
};

typedef QNode *QueuePtr;

//����ֵΪe�Ķ��н��
Status MakeQNode(QueuePtr &s, int e)
{
	s = new QNode;
	if (!s)
		exit(OVERFLOW);

	s->data = e;
	s->next = NULL;

	return OK;
}

//��������ʵ�� ʮ��

//����һ���ն���Q
Status InitQueue(LinkQueue &Q)
{
	Q.front = new QNode;
	if (!Q.front)
		exit(OVERFLOW);

	Q.rear = Q.front;

	return OK;
}
//���ٶ���Q��Q������
Status DestroyQueue(LinkQueue &Q)
{
	QueuePtr p = Q.front;
	QueuePtr q = p->next;

	while (q)
	{
		delete p;
		p = q;
		q = q->next;
	}
	delete p;

	Q.front = NULL;
	Q.rear = NULL;

	return OK;
}
//��Q��Ϊ�ն���
Status ClearQueue(LinkQueue &Q)
{
	QueuePtr p, q;
	p = Q.front->next;

	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	Q.front->next = NULL;
	Q.rear = Q.front;

	return OK;
}
//������Ϊ�գ��򷵻�TRUE�����򷵻�FALSE
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}
//���ض��г���
int QueueLength(LinkQueue Q)
{
	QueuePtr p = Q.front;
	int i = 0;

	while (p != Q.rear)
	{
		p = p->next;
		i++;
	}

	return i;
}
//�����в�Ϊ�գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�FALSE
Status GetHead(LinkQueue Q, int &e)
{
	if (Q.front == Q.rear)
		return FALSE;

	QueuePtr head;
	head = Q.front->next;

	e = head->data;

	return OK;
}
//����Ԫ��eΪQ���µĶ�βԪ��
Status EnQueue(LinkQueue &Q, int e)
{
	QueuePtr s;

	MakeQNode(s, e);

	Q.rear->next = s;
	Q.rear = s;

	return OK;
}
//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ�����e������ֵ��������OK�����򷵻�FALSE
Status DeQueue(LinkQueue &Q, int &e)
{
	if (Q.front == Q.rear)
		return FALSE;

	QueuePtr p;
	p = Q.front->next;

	Q.front->next = p->next;
	e = p->data;
	delete p;

	if (!Q.rear)
		Q.rear = Q.front;

	return OK;
}
//�����������
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p = Q.front->next;

	while (p)
	{
		cout << p->data << '\t';
		p = p->next;
	}
	cout << endl;

	return OK;
}
Status CreatQueue(LinkQueue &Q, int n)
{
	InitQueue(Q);

	int e;

	for (int i = 0;i < n;i++)
	{
		cin >> e;
		EnQueue(Q, e);
	}

	return OK;
}

int main()
{
	LinkQueue Q;

	int n;
	//1.���� 2.���� 3.��ʼ������ ����
	cout << "������Ԫ�ظ���n����Ԫ��\n";
	cin >> n;
	CreatQueue(Q, n);
	QueueTraverse(Q);

	int e;

	//4.��ȡԪ�غ��� ����
	cout << "��ͷԪ��Ϊ\n";
	GetHead(Q, e);
	cout << "��Ԫ��Ϊ��" << e << endl;

	//5.����
	cout << "��ʱ���еĳ���Ϊ��" << QueueLength(Q) << endl;

	//6.��� 7.����
	cout << "���������Ԫ��e\n";
	cin >> e;
	EnQueue(Q, e);
	cout << "�����Ϊ��" << endl;
	QueueTraverse(Q);

	cout << "Ԫ�س���\n";
	DeQueue(Q, e);
	cout << "���ӵ�Ԫ��Ϊ " << e << endl;
	cout << "���Ӻ�Ϊ��" << endl;
	QueueTraverse(Q);

	//8.���  9.�Ƿ�Ϊ�� 10.����

	//��ն���
	cout << "��պ�������\n";
	ClearQueue(Q);
	QueueTraverse(Q);

	if (QueueEmpty(Q))
		cout << "����Ϊ��" << endl;

	DestroyQueue(Q);

	system("pause");

	return 0;
}