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

	for (int i = 0; i <= MAT_INIT_SIZE; i++)
	{
		for (int j = 0; j <= MAT_INIT_SIZE; j++)
		{
			mat.elem[i][j] = { 0,NULL };
		}
	}

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

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		cin >> G.vexset.elem[i];
	}

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
		if (!VexSetExtend(G.vexset))
			return ERROR;
		if (!AdjMatExtend(G.mat))
			return ERROR;
	}
	//------若空间不足，则在此处扩展空间------

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		cin >> G.vexset.elem[i];
	}

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
		if (!VexSetExtend(G.vexset))
			return ERROR;
		if (!AdjMatExtend(G.mat))
			return ERROR;
	}
	//------若空间不足，则在此处扩展空间------

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		cin >> G.vexset.elem[i];
	}

	cout << "请输入边的两端顶点，及边的权值\n";		//创建邻接矩阵
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
		if (!VexSetExtend(G.vexset))
			return ERROR;
		if (!AdjMatExtend(G.mat))
			return ERROR;
	}
	//------若空间不足，则在此处扩展空间------

	cout << "请输入顶点集合:\n";					//创建顶点集
	for (int i = 1; i <= G.vexnum; i++)
	{
		cin >> G.vexset.elem[i];
	}

	cout << "请分别输入有向边的两端，及边的权值\n";		//创建邻接矩阵
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

Status FirstAdjVex(GraphM G, VexElemType v,VexElemType &adjvex)
{
	int i;						//找到顶点 v 在 G 中的位置
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
		if (elem[i][j].adj > 0)
		{
			/*和使用strcmp的区别 -> adjvex = G.vexset.elem[j];*/
			strcpy_s(adjvex, G.vexset.elem[j]);
			return OK;
		}
	}

	strcpy_s(adjvex, "NULL");
	return NULL;
}

Status NextAdjVex(GraphM G, VexElemType v, VexElemType w, VexElemType &adjvex)
{
	int i, start;
	i = LocateVex(G, v);
	start = LocateVex(G, w);
	if (i <= 0 || start<=0)
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

















//------------辅助检测函数--------------

void PrintVexSet(GraphM G)
{
	VexElemType *v = G.vexset.elem;
	for (int i = 1; i <= G.vexnum; i++)
	{
		cout << v[i] << '\t';
	}
	cout << endl;

	return;
}

void PrintAdjMat(GraphM G)
{
	AdjMatElem **mat = G.mat.elem;
	for (int i = 1; i <= G.vexnum; i++)
	{
		for (int j = 1; j <= G.vexnum; j++)
		{
			cout << mat[i][j].adj << '\t';
		}
		cout << endl;
	}

	return;
}