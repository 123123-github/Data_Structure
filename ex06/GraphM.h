#pragma once
// ADT Graph 邻接矩阵存储
// C++

//-----------------------函数结果状态代码--------------------

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;			//Status 为函数类型，值为函数结果状态代码


//-----------------------Graph组成元素定义-----------------------

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

int LocateVex(GraphM G, VexElemType v);	//返回顶点 v 在顶点集向量中的位置

Status CreatGraphM(GraphM &G);			//创建图
Status CreatUDG(GraphM &G);
Status CreatDG(GraphM &G);
Status CreatUDN(GraphM &G);
Status CreatDN(GraphM &G);

Status FirstAdjVex(GraphM G, VexElemType v, VexElemType &adjvex);					//返回 G 中 v 的第一个邻接结点

Status NextAdjVex(GraphM G, VexElemType v, VexElemType w, VexElemType &adjvex);		//返回 G 中 v 在顶点 w 之后的邻接点










//------------辅助检测函数--------------

void PrintVexSet(GraphM G);

void PrintAdjMat(GraphM G);