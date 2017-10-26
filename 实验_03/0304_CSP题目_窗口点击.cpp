//csp 窗口点击问题

#include <iostream>
using namespace std;

struct LNode
{
	int x1, y1;
	int x2, y2;
	int name;

	LNode *next;
};

typedef LNode *Link;

struct LinkList
{
	Link head;
};

void MakeNode(Link &s)
{
	s = new LNode;
}

void InsertFirst(LinkList &L, Link s)
{
	s->next = L.head->next;
	L.head->next = s;

	return;
}

void ListDelete(LinkList &L, Link s)
{
	Link p = L.head;

	while (p->next != s)
		p = p->next;

	p->next = s->next;

	return;
}

struct operation
{
	int x, y;
};

int IsInList(operation click, LinkList L, Link &p)
{
	p = L.head->next;

	while (p)
	{
		if (p->x1 <= click.x && click.x <= p->x2 && p->y1 <= click.y && click.y <= p->y2)
			return p->name;

		p = p->next;
	}

	return 0;
}

int main()
{
	LinkList L;
	L.head = new LNode;
	L.head->next = NULL;

	int N, M;
	Link s;


	cin >> N >> M;

	operation *click;
	click = new operation[M];

	for (int i = 0; i < N; i++)
	{
		MakeNode(s);
		cin >> s->x1 >> s->y1 >> s->x2 >> s->y2;
		s->name = i + 1;

		InsertFirst(L, s);
	}

	for (int i = 0; i < M; i++)
	{
		cin >> click[i].x >> click[i].y;
	}



	int name;
	Link window;
	for (int i = 0; i < M; i++)
	{
		name = IsInList(click[i], L, window);

		if (name)
		{
			cout << name << '\n';
			ListDelete(L, window);
			InsertFirst(L, window);
		}
		else
			cout << "IGNORED" << '\n';
	}

	system("pause");

	return 0;
}