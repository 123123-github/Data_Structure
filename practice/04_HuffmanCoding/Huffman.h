// Huffman 编码
// C++ 类
#pragma once
#include <vector>
#include <string>
using namespace std;

struct HTNode
{
	int weight;				// 权重 整数表示
	int parent;				// 存储的是位置
	int left;
	int right;
};
typedef HTNode* HTree;

struct charlistNode			// 字符及其对应的权重
{
	char ch;				// ascii 码字符
	int weight;				// 字符个数
};


class Huffman
{
private:
	vector<charlistNode> list;						// 字符统计表
	HTree HT;										// 存放编码结果数表
	vector<string> HC;								// 存放编码值
	string sourcefilename;

public:
	Huffman();
	~Huffman();

private:
	void Select(int n,int &s1, int &s2);			// 在树前 n 个结点中挑出两个权值最小的结点 (未访问过)
public:
	void FileGetWeight(const char* filename);		// 统计文章 有效字符 及 权重
	void HuffmanCoding();
	void PrintHC();
public:
	void SaveHT();
	void SaveHC();

public:
	void Coding();								// 将压缩后的编码输出
	void Decode(const char* filename = "Decode.txt");

private:
	// 测试函数
	void Setlist();
};

