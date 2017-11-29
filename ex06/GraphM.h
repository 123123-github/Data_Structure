#pragma once
// ADT Graph 邻接矩阵存储	GraphM
// C++

//-----------------------函数结果状态代码--------------------

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;			//Status 为函数类型，值为函数结果状态代码


//-----------------------Graph组成元素定义-----------------------

#define INFINITY_MY -1			//用在网中，表示两点不相邻

typedef enum { UNDEFINE, UDG, DG, UDN, DN } GraphKind;		//图类型，分别为未定义，无向图，有向图，无向网，有向网

//--------顶点集(顺序表)------

typedef char VexElemType[20];		//顶点类型，定义为一个长度为20字节的字符串

struct VertexSet						//顶点集
{
	VexElemType *elem;
	int maxsize;
};

//-------邻接矩阵(二维的顺序表)------

typedef char InfoType;					//矩阵元素邻接关系信息-->与该边相关的信息

typedef int VRType;						//顶点间关系类型-->边权值类型

struct AdjMatElem						//邻接矩阵基本单元
{
	VRType adj;				//无权图时， adj 取值为 0 或 1
	InfoType *info;
};

struct AdjMat							//邻接矩阵
{
	AdjMatElem **elem;
	int maxsize;			// AdjMat 为方阵
};


//----------------顶点集,邻接矩阵空间分配---------------

#define VEX_INIT_NUM 15
#define VEX_INCREMENT 10
#define MAT_INIT_SIZE 15
#define MAT_INCREMENT 10

Status VexSetInit(VertexSet &vexset);		//初始化顶点集

Status VexSetDestroy(VertexSet &vexset);	//销毁顶点集

Status VexSetExtend(VertexSet &vexset, int NEWSIZE);		//扩大空间至指定长度 NEWSIZE(用于Create)

Status VexSetExtend(VertexSet &vexset);		//重载函数，将空间按增量默认扩大 ( 用于表已满时的扩大 ) 

Status AdjMatInit(AdjMat &mat);				//初始化图的邻接矩阵

Status AdjMatDestroy(AdjMat &mat);			//销毁图的邻接矩阵

Status AdjMatExtend(AdjMat &mat, int NEWSIZE);				//扩大空间至 NEWSIZE

Status AdjMatExtend(AdjMat &mat);			//重载函数，将空间按增量默认扩大

Status SortVexSet(VexElemType *a, int n);	//对含有 n 个顶点的顶点集排序


//-----------------------ADT GraphM 定义---------------------

struct GraphM
{
	GraphKind kind;		
	int vexnum;
	int edgenum;
	VertexSet vexset;	//顶点集
	AdjMat mat;			//邻接矩阵
};


//-----------------------GraphM 基本操作----------------------

Status InitGraphM(GraphM &G);			//初始化为空图

Status DestroyGraphM(GraphM &G);		//销毁图

int LocateVex(GraphM G, VexElemType v);	//返回顶点 v 在顶点集中的位置

Status CreatGraphM(GraphM &G);			//创建图

Status CreatUDG(GraphM &G);

Status CreatDG(GraphM &G);

Status CreatUDN(GraphM &G);

Status CreatDN(GraphM &G);

Status FirstAdjVex(GraphM G, VexElemType v, VexElemType &adjvex);					//返回 G 中 v 的第一个邻接结点

int FirstAdjVex(GraphM G, int v);			//输入返回均为顶点集位序的重载函数

Status NextAdjVex(GraphM G, VexElemType v, VexElemType w, VexElemType &adjvex);		//返回 G 中 v 在顶点 w 之后的邻接点

int NextAdjVex(GraphM G, int v, int w);		//输入返回均为顶点集位序的重载函数

Status InsertVex(GraphM &G, VexElemType v);		//在图中插入顶点 v 

Status DeleteVex(GraphM &G, VexElemType v);		//删除图中的顶点 v 

Status InsertEdge(GraphM &G, VexElemType v, VexElemType w,int value=1);				//在 v w 之间添加边 value 为权值，无向图不需要

Status DeleteEdge(GraphM &G, VexElemType v, VexElemType w);		//在 v w 之间删除边

//------------遍历用队列定义-------------

struct QNode_t			//存放顶点位置的队列
{
	int elem;
	QNode_t *next;
};
typedef QNode_t *Queueptr_t;

Status MakeQueueNode_t(QNode_t* &s, int t);	//分配结点

struct Queue_t			//队列定义
{
	Queueptr_t front;
	Queueptr_t rear;
};

Status InitQueue_t(Queue_t &Q);		//初始化队列

Status DestroyQueue_t(Queue_t &Q);	//销毁队列

bool QueueEmpty_t(Queue_t Q);		//队是否为空

Status EnQueue_t(Queue_t &Q, int t);			//入队

Status DeQueue_t(Queue_t &Q, int &t);			//出队

//-----------遍历用队列定义结束-----------

void DFS(GraphM G, int p);			//从顶点集中的第 p 个顶点开始深度优先搜索

void BFS(GraphM G, int p);			//广度优先搜索

void DFSTraverse(GraphM G);			//深度优先遍历

void BFSTraverse(GraphM G);			//广度优先遍历



//------------辅助检测函数--------------

void PrintGraphMat(GraphM G);