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

//--------顶点向量组------

typedef char VertexElemType[20];		//顶点类型，定义为一个大小为20字节的字符串

struct VertexType						//顶点向量组
{
	VertexElemType *elem;
	int vexsize;
};

typedef int VRType;				//顶点间关系类型-->边权值类型

typedef char InfoType;			//矩阵元素邻接关系信息-->与该边相关的信息

//-------邻接矩阵------

struct AdjMatElem			//邻接矩阵基本单元
{
	VRType adj;			//无权图时， adj 取值为 0 或 1
	InfoType *info;
};

struct AdjMat					//AdjMat为二级指针类型，指向的基本元素是邻接矩阵基本单元
{
	AdjMatElem **elem;
	int size;			// AdjMat 为方阵
};


//----------------基本元素空间分配---------------

#define VEX_INIT_NUM 15
#define VEX_INCREMENT 10
#define MAT_INIT_SIZE 15
#define MAT_INCREMENT 10

Status VexInit(VertexType &vertex);		//初始化顶点向量组

Status VexDestroy(VertexType &vertex);	//销毁顶点集向量组

Status AdjMatInit(AdjMat &mat);		//初始化图的邻接矩阵

Status AdjMatDestroy(AdjMat &mat);	//销毁图的邻接矩阵


//-----------------------ADT GraphM 定义---------------------

struct GraphM
{
	GraphKind kind;		
	int vexnum;
	int edgenum;
	VertexType vex;	//顶点集
	AdjMat mat;			//邻接矩阵
};


//-----------------------GraphM 基本操作----------------------

Status InitGraphM(GraphM &G);			//初始化为空图

Status DestroyGraphM(GraphM &G);		//销毁图

int LocateVex(GraphM G, VertexElemType v);	//返回顶点 v 在顶点集向量中的位置

Status CreatGraphM(GraphM &G);			//创建图
Status CreatUDG(GraphM &G);
Status CreatDG(GraphM &G);
Status CreatUDN(GraphM &G);
Status CreatDN(GraphM &G);

