#include <iostream>
#include <cstring>
#include "GraphM.h"
using namespace std;

//----------------基本元素空间分配---------------

//-----顶点集向量-----

Status VexSetInit(VertexSet  &vexset)			//初始化顶点向量组
{
	vexset.elem = new VexElemType[VEX_INIT_NUM + 1];	//vertex[0]不使用
	if (!vexset.elem)
		return ERROR;

	vexset.maxsize = VEX_INIT_NUM;

	return OK;
}

Status VexSetDestroy(VertexSet &vexset)		//销毁顶点集向量组
{
	delete[] vexset.elem;
	vexset.elem = NULL;

	vexset.maxsize = -1;

	return OK;
}

Status VexSetExtend(VertexSet & vexset, int NEWSIZE)	//将顶点集(无原始数据)空间扩大至NEWSIZE
{
	VexElemType *newbase;
	newbase = new VexElemType[NEWSIZE + 1];		//申请新空间
	if (!newbase)
		return ERROR;

	delete[] vexset.elem;						//释放旧空间

	vexset.elem = newbase;						//指向新空间

	vexset.maxsize = NEWSIZE;					//修改顶点集大小	

	return OK;
}

Status VexSetExtend(VertexSet & vexset)
{
	VexElemType *newbase;
	newbase = new VexElemType[vexset.maxsize + VEX_INCREMENT + 1];		//申请新空间
	if (!newbase)
		return ERROR;

	for (int i = 0; i <= vexset.maxsize; i++)	//复制元素
	{
		strcpy_s(newbase[i], vexset.elem[i]);
	}

	delete[] vexset.elem;						//释放旧空间

	vexset.elem = newbase;						//指向新空间

	vexset.maxsize += VEX_INCREMENT;			//修改顶点集大小	

	return OK;
}

//------邻接矩阵------

Status AdjMatInit(AdjMat &mat)				//初始化图的邻接矩阵
{
	mat.elem = new AdjMatElem*[MAT_INIT_SIZE + 1];	//数组 0 空间不使用 
	if (!mat.elem)
		return ERROR;
	for (int i = 0; i <= MAT_INIT_SIZE; i++)
	{
		mat.elem[i] = new AdjMatElem[MAT_INIT_SIZE + 1];
		if (!mat.elem[i])
			return ERROR;
	}
	//得到了大小为 (MAT_INIT_SIZE + 1) × (MAT_INIT_SIZE + 1) 的二维矩阵

	mat.maxsize= MAT_INIT_SIZE;

	for (int i = 0; i <= MAT_INIT_SIZE; i++)		//为矩阵赋初值
		for (int j = 0; j <= MAT_INIT_SIZE; j++)
			mat.elem[i][j] = { 0,NULL };

	return OK;
}

Status AdjMatDestroy(AdjMat &mat)			//销毁图的邻接矩阵
{
	for (int i = 0; i <= mat.maxsize; i++)
	{
		delete[] mat.elem[i];

	}
	delete[] mat.elem;
	mat.elem = NULL;

	mat.maxsize = -1;

	return OK;
}

Status AdjMatExtend(AdjMat & mat, int NEWSIZE)
{
	AdjMatElem **newbase;

	newbase = new AdjMatElem*[NEWSIZE + 1];			//申请新空间
	if (!newbase)
		return ERROR;
	for (int i = 0; i < NEWSIZE + 1; i++)
	{
		newbase[i] = new AdjMatElem[NEWSIZE + 1];
		if (!newbase[i])
			exit(OVERFLOW);
	}
	for (int i = 0; i <= NEWSIZE; i++)				//为矩阵赋初值
		for (int j = 0; j <= NEWSIZE; j++)
			newbase[i][j] = { 0,NULL };

	for (int i = 0; i <= mat.maxsize; i++)			//释放旧空间
	{
		delete[] mat.elem[i];
	}
	delete[] mat.elem;

	mat.elem = newbase;								//指向新空间

	mat.maxsize = NEWSIZE;							//修改顶点集大小

	return OK;
}

Status AdjMatExtend(AdjMat & mat)
{
	AdjMatElem **newbase;
	int size = mat.maxsize;

	newbase = new AdjMatElem*[size + MAT_INCREMENT + 1];			//申请新空间
	if (!newbase)
		return ERROR;
	for (int i = 0; i < size + MAT_INCREMENT + 1; i++)
	{
		newbase[i] = new AdjMatElem[size + MAT_INCREMENT + 1];
		if (!newbase[i])
			exit(OVERFLOW);
	}
	for (int i = 0; i <= size + MAT_INCREMENT; i++)					//为矩阵赋初值
		for (int j = 0; j <= size + MAT_INCREMENT; j++)
			newbase[i][j] = { 0,NULL };

	for (int i = 0; i <= size; i++)			//复制元素
	{
		for (int j = 0; j <= size; j++)
		{
			newbase[i][j] = mat.elem[i][j];
		}
	}

	for (int i = 0; i <= size; i++)			//释放旧空间
	{
		delete[] mat.elem[i];
	}
	delete[] mat.elem;

	mat.elem = newbase;						//指向新空间

	mat.maxsize += MAT_INCREMENT;			//修改顶点集大小

	return OK;
}

//--------其它--------

Status SortVexSet(VexElemType * a, int n)	//升序排列
{
	int p;
	VexElemType t;
	for (int i = 1; i <= n - 1; i++)
	{
		p = i;
		for (int j = i + 1; j <= n; j++)
		{
			if (strcmp(a[p], a[j]) > 0)
				p = j;
		}
		if (p != i)
		{
			strcpy_s(t, a[p]);
			strcpy_s(a[p], a[i]);
			strcpy_s(a[i], t);
		}
	}
	return OK;
}


//-----------------------GraphM 基本操作----------------------

Status InitGraphM(GraphM & G)
{
	G.kind = UNDEFINE;
	G.vexnum = 0;
	G.edgenum = 0;
	VexSetInit(G.vexset);
	AdjMatInit(G.mat);

	return OK;
}

Status DestroyGraphM(GraphM & G)
{
	G.kind = UNDEFINE;
	G.vexnum = -1;
	G.edgenum = -1;

	VexSetDestroy(G.vexset);
	AdjMatDestroy(G.mat);

	return OK;
}

int LocateVex(GraphM G, VexElemType v)
{
	VexElemType *elem = G.vexset.elem;
	for (int i = 1; i <= G.vexnum; i++)
	{
		if (strcmp(*(elem + i), v) == 0)
			return i;
	}

	return 0;
}

Status CreatGraphM(GraphM & G)		//依据图的类型创建图
{
	cout << "请输入图的类型:\n无向图，有向图，无向网，有向网分别为 1 2 3 4\n";
	int kind;
	cin >> kind;
	G.kind = GraphKind(kind);
	
	switch (G.kind)
	{
	case UNDEFINE:
		return ERROR;
	case UDG:
	{
		CreatUDG(G);
		return OK;
	}
	case DG:
	{
		CreatDG(G);
		return OK;
	}
	case UDN:
	{
		CreatUDN(G);
		return OK;
	}
	case DN:
	{
		CreatDN(G);
		return OK;
	}
	default:
		break;
	}
	return OK;
}

Status CreatUDG(GraphM &G)		//无向图
{
	cout << "请输入图的顶点数及边数:\n";
	cin >> G.vexnum >> G.edgenum;

	//------若空间不足，则在此重新初始化空间------
	if (G.vexnum>G.vexset.maxsize)
	{
		if (!VexSetExtend(G.vexset, G.vexnum))
			return ERROR;
		if (!AdjMatExtend(G.mat, G.vexnum))
			return ERROR;
	}
	//------若空间不足，则在此处扩展空间------

	cout << "请输入顶点集合:\n";					//创建顶点集,创建后排序
	for (int i = 1; i <= G.vexnum; i++)
	{
		cin >> G.vexset.elem[i];
	}
	SortVexSet(G.vexset.elem, G.vexnum);

	cout << "请输入每条边的两端顶点\n";				//创建邻接矩阵
	VexElemType v1, v2;
	int i, j;
	for (int k = 1; k <= G.edgenum; k++)
	{
		cin >> v1 >> v2;

		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.mat.elem[i][j].adj = 1;
		G.mat.elem[j][i].adj = 1;
	}

	return OK;
}

Status CreatDG(GraphM & G)		//有向图
{
	cout << "请输入图的顶点数及边数:\n";
	cin >> G.vexnum >> G.edgenum;

	//------若空间不足，则在此处扩展空间------
	if (G.vexnum>G.vexset.maxsize)
	{
		if (!VexSetExtend(G.vexset, G.vexnum))
			return ERROR;
		if (!AdjMatExtend(G.mat, G.vexnum))
			return ERROR;
	}
	//------若空间不足，则在此处扩展空间------

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		cin >> G.vexset.elem[i];
	}
	SortVexSet(G.vexset.elem, G.vexnum);

	cout << "请分别输入有向边的起始两端\n";		//创建邻接矩阵
	VexElemType v1, v2;
	int i, j;
	for (int k = 1; k <= G.edgenum; k++)
	{
		cin >> v1 >> v2;

		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.mat.elem[i][j].adj = 1;
	}

	return OK;
}

Status CreatUDN(GraphM & G)		//无向网
{
	cout << "请输入图的顶点数及边数:\n";
	cin >> G.vexnum >> G.edgenum;

	//------若空间不足，则在此处扩展空间------
	if (G.vexnum>G.vexset.maxsize)
	{
		if (!VexSetExtend(G.vexset, G.vexnum))
			return ERROR;
		if (!AdjMatExtend(G.mat, G.vexnum))
			return ERROR;
	}
	//------若空间不足，则在此处扩展空间------

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		cin >> G.vexset.elem[i];
	}
	SortVexSet(G.vexset.elem, G.vexnum);

	cout << "请输入边的两端顶点，及边的权值\n";		//创建邻接矩阵
	
	/*对邻接矩阵重新赋初值*/
	for (int i = 1; i <= G.vexnum; i++)
		for (int j = 1;j <= G.vexnum;j++)
			if (i == j)
				G.mat.elem[i][j].adj = 0;
			else
				G.mat.elem[i][j].adj = INFINITY_MY;
	/*与图中的 0 的意义区别，使用 INFINITY_MY 表示不相邻*/

	VexElemType v1, v2;
	VRType w;
	int i, j;
	for (int k = 1; k <= G.edgenum; k++)
	{
		cin >> v1 >> v2 >> w;

		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.mat.elem[i][j].adj = w;
		G.mat.elem[j][i].adj = w;
	}

	return OK;
}

Status CreatDN(GraphM & G)		//有向网
{
	cout << "请输入图的顶点数及边数:\n";
	cin >> G.vexnum >> G.edgenum;

	//------若空间不足，则在此处扩展空间------
	if (G.vexnum>G.vexset.maxsize)
	{
		if (!VexSetExtend(G.vexset, G.vexnum))
			return ERROR;
		if (!AdjMatExtend(G.mat, G.vexnum))
			return ERROR;
	}
	//------若空间不足，则在此处扩展空间------

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		cin >> G.vexset.elem[i];
	}
	SortVexSet(G.vexset.elem, G.vexnum);

	cout << "请分别输入有向边的两端，及边的权值\n";		//创建邻接矩阵

	/*对邻接矩阵重新赋初值*/
	for (int i = 1; i <= G.vexnum; i++)
		for (int j = 1;j <= G.vexnum;j++)
			if (i == j)
				G.mat.elem[i][j].adj = 0;
			else
				G.mat.elem[i][j].adj = INFINITY_MY;
	/*与图中的 0 的意义区别，使用 INFINITY_MY 表示不相邻*/

	VexElemType v1, v2;
	VRType w;
	int i, j;
	for (int k = 1; k <= G.edgenum; k++)
	{
		cin >> v1 >> v2 >> w;

		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.mat.elem[i][j].adj = w;
	}

	return OK;
}

Status FirstAdjVex(GraphM G, VexElemType v, VexElemType &adjvex)
{
	int i;								//找到顶点 v 在 G 中的位置
	i = LocateVex(G, v);
	if (i <= 0)
	{
		strcpy_s(adjvex, "NULL");
		return ERROR;
	}
	AdjMatElem **elem;
	elem = G.mat.elem;
	for (int j = 1; j <= G.vexnum; j++)
	{
		if (elem[i][j].adj > 0)			//表示邻接，不是 0 或 INFINITY_MY
		{
			/*和使用strcmp的区别 -> adjvex = G.vexset.elem[j];*/
			strcpy_s(adjvex, G.vexset.elem[j]);
			return OK;
		}
	}

	strcpy_s(adjvex, "NULL");
	return NULL;
}

int FirstAdjVex(GraphM G, int v)
{
	AdjMatElem **elem;
	elem = G.mat.elem;
	for (int j = 1; j <= G.vexnum; j++)
		if (elem[v][j].adj > 0)			//表示邻接，不是 0 或 INFINITY_MY
			return j;

	return 0;
}

Status NextAdjVex(GraphM G, VexElemType v, VexElemType w, VexElemType &adjvex)
{
	int i, start;
	i = LocateVex(G, v);
	start = LocateVex(G, w);
	if (i <= 0 || start <= 0)
	{
		strcpy_s(adjvex, "NULL");
		return ERROR;
	}

	AdjMatElem **elem;
	elem = G.mat.elem;
	for (int j = start+1; j <= G.vexnum; j++)
	{
		if (elem[i][j].adj > 0)
		{
			strcpy_s(adjvex, G.vexset.elem[j]);
			return OK;
		}
	}

	strcpy_s(adjvex, "NULL");
	return NULL;
}

int NextAdjVex(GraphM G, int v, int w)
{
	AdjMatElem **elem;
	elem = G.mat.elem;
	for (int j = w + 1; j <= G.vexnum; j++)
		if (elem[v][j].adj > 0)
			return j;

	return 0;
}

Status InsertVex(GraphM & G, VexElemType v)
{
	if (G.vexnum==G.vexset.maxsize)		//空间已满则扩展空间
	{
		VexSetExtend(G.vexset);
		AdjMatExtend(G.mat);
	}
	
	int n = G.vexnum;
	VexElemType *vexset = G.vexset.elem;
	AdjMatElem **mat = G.mat.elem;

	int p;										//找位置
	for (p = 1; p <= n; p++)			/*此处不可再写为int p = 1 ，否则为局部变量，后续用到的 p 则没有初始化*/
		if (strcmp(vexset[p], v) >= 0)
			break;

	for (int i = n;i >= p;i--)					//移动一维表
		strcpy_s(vexset[i + 1], vexset[i]);		
	
	for (int i = 1;i <= n;i++)					//移动二维表
		for (int j = n; j >= p; j--)
			mat[i][j + 1] = mat[i][j];
	for (int j = 1;j <= n + 1;j++)		/* j <= n + 1 而不是 n - 1 */
		for (int i = n;i >= p;i--)
			mat[i + 1][j] = mat[i][j];

	strcpy_s(vexset[p], v);						//插入顶点，及初始化邻接矩阵空出的空间
	if (G.kind == UDG || G.kind == DG)
	{
		for (int i = 1; i <= n + 1; i++)
			mat[i][p] = { 0,NULL };
		for (int j = 1;j <= n + 1;j++)
			mat[p][j] = { 0,NULL };
	}
	else
	{
		for (int i = 1; i <= n + 1; i++)
			mat[i][p] = { INFINITY_MY,NULL };
		for (int j = 1;j <= n + 1;j++)
			mat[p][j] = { INFINITY_MY,NULL };
	}

	G.vexnum++;									//顶点个数 + 1

	return Status();
}

Status DeleteVex(GraphM & G, VexElemType v)
{
	if (G.vexnum <= 0)							//判断删除是否合法
		return ERROR;
	
	int n = G.vexnum;
	VexElemType *vexset = G.vexset.elem;
	AdjMatElem **mat = G.mat.elem;

	int p;										//找位置
	p = LocateVex(G, v);
	
	for (int i = p; i <= n - 1; i++)			//移动一维表
		strcpy_s(vexset[i], vexset[i + 1]);

	for (int j = 1; j <= n; j++)				//移动二维表
		for (int i = p; i <= n - 1; i++)
			mat[i][j] = mat[i + 1][j];
	for (int i = 1; i <= n - 1; i++)
		for (int j = p; j <= n - 1; j++)
			mat[i][j] = mat[i][j + 1];

	G.vexnum--;									//顶点个数 - 1

	return OK;
}

Status InsertEdge(GraphM & G, VexElemType v, VexElemType w, int value)
{
	int i, j;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if (!i || !j)
		return ERROR;

	G.mat.elem[i][j].adj = value;
	if (G.kind == UDG || G.kind == UDN)			//为无向图或网时，添加对称边
		G.mat.elem[i][j].adj = value;

	return OK;
}

Status DeleteEdge(GraphM & G, VexElemType v, VexElemType w)
{
	int i, j;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if (!i || !j)
		return ERROR;

	switch (G.kind)
	{
	case UDG:
	{
		G.mat.elem[i][j].adj = 0;
		G.mat.elem[j][i].adj = 0;
		return OK;
	}
	case UDN:
	{
		G.mat.elem[i][j].adj = INFINITY_MY;
		G.mat.elem[j][i].adj = INFINITY_MY;
		return OK;
	}
	case DG:
	{
		G.mat.elem[i][j].adj = 0;
		return OK;
	}
	case DN:
	{
		G.mat.elem[i][j].adj = INFINITY_MY;
		return OK;
	}
	default:
		return ERROR;
	}
}

//------------遍历用队列定义------------

Status MakeQueueNode_t(QNode_t* &s, int t)	//分配结点
{
	s = new QNode_t;
	if (!s)
		return ERROR;

	s->next = NULL;
	s->elem = t;

	return OK;
}

Status InitQueue_t(Queue_t &Q)		//初始化队列
{
	Q.front = new QNode_t;
	if (!Q.front)
		return ERROR;

	Q.front->next = NULL;
	Q.rear = Q.front;

	return OK;
}

Status DestroyQueue_t(Queue_t &Q)	//销毁队列
{
	Queueptr_t p, q;
	p = q = Q.front;

	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	Q.front = NULL;
	Q.rear = NULL;

	return OK;
}

bool QueueEmpty_t(Queue_t Q)		//队是否为空
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

Status EnQueue_t(Queue_t &Q, int t)			//入队
{
	QNode_t *s;
	MakeQueueNode_t(s, t);

	Q.rear->next = s;
	Q.rear = s;

	return OK;
}

Status DeQueue_t(Queue_t &Q, int &t)				//出队
{
	if (Q.front == Q.rear)
		return	ERROR;

	Queueptr_t p;
	p = Q.front->next;
	t = p->elem;

	if (p == Q.rear)	//避免队尾指针被删除
		Q.rear = Q.front;

	Q.front->next = p->next;
	delete p;
	p = NULL;

	return OK;
}

//----------遍历树用队列定义结束----------

void DFS(GraphM G, int p)		//非递归栈实现
{
	/* ??? 递归如何设置标志数组 ???*/
}

void BFS(GraphM G, int p)		//队列实现
{

}

void DFSTraverse(GraphM G)
{

}

void BFSTraverse(GraphM G)
{

}

















//------------辅助检测函数--------------

void PrintGraphMat(GraphM G)
{
	VexElemType *v = G.vexset.elem;
	for (int i = 1; i <= G.vexnum; i++)
	{
		cout << '\t' << v[i];
	}
	cout << endl;

	AdjMatElem **mat = G.mat.elem;
	for (int i = 1; i <= G.vexnum; i++)
	{
		cout << v[i] << '\t';
		for (int j = 1; j <= G.vexnum; j++)
		{
			cout << mat[i][j].adj << '\t';
		}
		cout << endl;
	}

	return;
}
