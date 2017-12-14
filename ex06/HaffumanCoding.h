#pragma once
// Huffman 编码

//-----------------------函数结果状态代码--------------------

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;			//Status 为函数类型，值为函数结果状态代码


//------------------------------------ 赫夫曼树及编码存储结构 -------------------------------------

struct HTNode						//赫夫曼树结点定义
{
	int weight;
	int parent;
	int left, right;
};

typedef HTNode* HuffmanTree;		//存储赫夫曼树

typedef char** HuffmanCode;			//存储编码结果


//-----------------------------------  赫夫曼树相关函数 -----------------------------


//------------------- 相关调用函数 ------------------

Status Select(HuffmanTree p, int n, int & s1, int & s2);			/* parent 不存在下 ； 按照位序选 */


//------------------- 生成 Huffman 树 ------------------

Status CreatHuffmanTree(HuffmanTree & HT, int * w, int n);

void PrintHuffmanTree(HuffmanTree HT, int n);

Status DestroyHuffmanTree(HuffmanTree & HT);


//------------------- 读取编码 ------------------

Status GetHuffmanCode(HuffmanTree & HT, HuffmanCode & HC, int n);

Status DestroyHuffmanCode(HuffmanCode & HC, int n);

void PrintHuffmanCode(HuffmanCode & HC, int n);


//------------------- Huffman 编码 ------------------

Status HuffmanCoding(HuffmanTree & HT, HuffmanCode & HC, int * w, int n);

Status HuffmanCodingDestroy(HuffmanTree & HT, HuffmanCode & HC, int n);