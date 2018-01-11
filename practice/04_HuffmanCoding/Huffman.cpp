#include "Huffman.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

Huffman::Huffman()
{
	HT = NULL;
}

Huffman::~Huffman()
{
	SaveHC();
	SaveHT();

	delete[] HT;
}

void Huffman::Select(int n, int & s1, int & s2)
{
	int min1;
	int min2;

	min1 = min2 = INT32_MAX;

	for (int i = 0; i < n; i++)
	{
		if (HT[i].parent != -1)
			continue;

		if (HT[i].weight < min1)
		{
			min2 = min1;
			min1 = HT[i].weight;

			s2 = s1;
			s1 = i;
		}
		else if (HT[i].weight<min2)
		{
			min2 = HT[i].weight;

			s2 = i;
		}
	}
}

void Huffman::FileGetWeight(const char * filename)
{
	int asciilist[256] = { 0 };

	ifstream in;
	in.open(filename);
	
	if (in.fail())
	{
		cout << "文件打开失败！\n";
		return;
	}

	char ch;
	ch = in.get();
	while (!in.eof())
	{
		cout << ch;
		++asciilist[ch];								// 统计有效字符数
		ch=in.get();
	}
	
	in.close();


	// 生成 charlist 

	for (int i = 0;i < 256;++i)
		if (asciilist[i] != 0)
			list.push_back({ char(i),asciilist[i] });	// 将统计结果存入记录表中

	sourcefilename = filename;							// 保存文件名
	/* 
	测试功能内容
	cout << "\n\n\n";

	for (int i = 0; i < 256; i++)
	{
		cout << asciilist[i] << '\t';
	}

	cout << "\n\n\n";

	cout << list.size();
	cout << endl;

	for (auto it = list.begin(); it < list.end(); it++)
	{
		cout << (*it).ch << ' ' << (*it).weight << '\n';
	}
	*/
	cout << "\n\n\n";
}

void Huffman::HuffmanCoding()
{
	int n;			// 需要编码的字符数
	int m;			// Huffman 树大小   0 号单元使用

	n = list.size();
	m = 2 * n - 1;

	HT = new HTNode[m];		// 申请空间
	if (!HT)
		return;

	//--------------------- 建立树 ---------------------

	for (int i = 0;i < n;++i)
		HT[i] = { list[i].weight, -1, 0 ,0 };			// 初始化编码结点			
	for (int i = n;i < m;++i)
		HT[i] = { 0, -1, 0, 0 };						// 初始化未建立结点区域 !!! 此时不能在初始化为 0 因为 0 号单元有使用

	int s1, s2;				// s1 为最小 s2 为次小值的位置
	for (int i = n;i < m;++i)							// 建立 Huffman 树
	{
		Select(i, s1, s2);

		HT[i].left = s1;
		HT[i].right = s2;

		HT[s1].parent = i;
		HT[s2].parent = i;
		
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//--------------------- 取编码 ---------------------
	
	string s = "";
	int q;		// p 的 parent
	for (int i = 0; i < n; i++)
	{
		for (int p = i;HT[p].parent != -1;p = q)
		{
			q = HT[p].parent;							// ！！！！！ 不要写成 if( p == HT[p].left ) ！！！！！

			if (p == HT[q].left)
				s.push_back('0');
			else
				s.push_back('1');
		}
		reverse(s.begin(), s.end());					// 将该串逆置
		HC.push_back(s);
		
		s.clear();
	}
}

void Huffman::PrintHC()
{
	for (int i = 0;i < HC.size();++i)
		cout << list[i].ch << ":\t"
		<< HC[i] << '\n';
}

void Huffman::SaveHT()
{
	char filename[] = "HT.txt";
	int size = list.size();

	ofstream out;
	out.open(filename);

	out << "字符" << "\t\t\t"
		<< "weight" << "\t\t\t"
		<< "parent" << "\t\t\t"
		<< "left" << "\t\t\t"
		<< "right" << '\n';
	for (int i = 0; i < size; i++)
	{
		out << list[i].ch << "\t\t\t"
			<< HT[i].weight << "\t\t\t"
			<< HT[i].parent << "\t\t\t"
			<< HT[i].left << "\t\t\t"
			<< HT[i].right << '\n';
	}

	out.close();
}

void Huffman::SaveHC()
{
	ofstream out;
	out.open("HC.txt");
	if (out.fail())
	{
		cout << "打开失败!\n";
		return;
	}

	out << "编码结果:\n";
	for (int i = 0; i < HC.size(); i++)
		out << list[i].ch << ":\t" << HC[i] << '\n';

	out.close();
}

void Huffman::Coding()
{
	int codeLen[256];
	string codeResult[256];
	for (int i = 0; i < HC.size(); i++)					// 获取对应的编码长度 及编码结果 直接映射
	{
		codeLen[list[i].ch] = HC[i].length();
		codeResult[list[i].ch] = HC[i];
	}


	ifstream in;		// 边读边写
	ofstream out;

	in.open(sourcefilename);
	if (in.fail())
	{
		cout << "源文件无法打开\n";
		system("pause");
		return;
	}
	out.open("outfile.txt", ios::binary);			// !!! 要采用二进制写 !!! 否则直接写入字符会有自动的转换 会导致解码出现问题
	if (out.fail())
	{
		cout << "创建输出文件失败\n";
		system("pause");
		return;
	}

	char ch;										// 读取到的需要编码的字符
	
	unsigned char outch = '\0';						// 存储编码比特信息的字符 存满后输出
	int outcharLen = 0;
	char outchar;
	
	int len;
	string code;									// 存放该字符的编码结果
	
	unsigned char c;								// 存放编码的单个 bit 

	in.get(ch);										// !!! 不能写成 in>>ch
	while (!in.eof())
	{
		len = codeLen[ch];
		code = codeResult[ch];
		for (int i = 0; i < len; ++i)				// 该字符编码全部输出后再读取下一个字符  !!!!!!!! 不要写反
		{
			c = code[i];							// 得到的是 '0' 或 '1' ：00110000 00110001
			c <<= 7;								// 左移 7 位
			c >>= outcharLen;						// 右移已经存储的位数

			outch |= c;								// 再将结果移动至输出串相应位 因为 c 只有一个 1 或者全是 0 所以只会造成一位的影响 用 ^ 也可以
			++outcharLen;							// 现在比之前多存储了一位

			if (outcharLen == 8)					// 存满一个字节后输出
			{
				outchar = outch;
				out.write(&outchar, 1);

				outch = '\0';						// 长度和字符都归零
				outcharLen = 0;
			}
		}
		in.get(ch);
	}
	if (outcharLen != 0)							// 输出最后一个没有编码完全的字符
	{
		outchar = outch;
		out.write(&outchar, 1);
	}

	in.close();
	out.close();
}

void Huffman::Decode(const char* filename)
{
	ofstream out;
	out.open(filename);
	if (out.fail())
	{
		cout << "解码失败！\n";
		return;
	}
	
	ifstream in;
	in.open("outfile.txt", ios::binary);										// 此处修改编码文件位置
	if (in.fail())
	{
		cout << "编码文件打开失败！\n";
		return;
	}

	char inch;
	unsigned char ch;											// 编码文件读取到的字符
	unsigned char dech;
	char outch;
	int r, root;
	root = list.size() * 2 - 1 - 1;								// 对应根在 Huffman 树中的位序
	r = root;

	int count = 0;
	/*
	//------------------ 文件读取会提前终止 ------------------	// 写入了文件结束符 ！！！ 一定要用二进制读的方式
	in.get(inch);
	while (!in.eof())
	{
		count++;
		ch = unsigned char(inch);
		for (int i = 0;i < 8;++i)
		{
			dech = ch << i;										// 取第 i + 1 位
			dech >>= 7;

			switch (dech)
			{
			case '\0':
				r = HT[r].left;
				if (HT[r].left == 0 && HT[r].right == 0)
				{
					outch = list[r].ch;
					r = root;
					out << outch;
				}
				break;
			case '\1':
				r = HT[r].right;
				if (HT[r].left == 0 && HT[r].right == 0)
				{
					outch = list[r].ch;
					r = root;
					out << outch;
				}
				break;
			default:
				cout << "解码过程出错\n";
				break;
			}
		}
		in.get(inch);
	}
	*/

	while (in.read(&inch, 1))
	{
		count++;
		ch = unsigned char(inch);
		for (int i = 0;i < 8;++i)
		{
			dech = ch << i;										// 取第 i + 1 位
			dech >>= 7;

			switch (dech)
			{
			case '\0':
				r = HT[r].left;
				if (HT[r].left == 0 && HT[r].right == 0)
				{
					outch = list[r].ch;
					r = root;
					out << outch;
				}
				break;
			case '\1':
				r = HT[r].right;
				if (HT[r].left == 0 && HT[r].right == 0)
				{
					outch = list[r].ch;
					r = root;
					out << outch;
				}
				break;
			default:
				cout << "解码过程出错\n";
				break;
			}
		}
	}
	out << '\n' << count;

	in.close();
	out.close();
}

void Huffman::Setlist()
{
	list.push_back({ 0,5 });
	list.push_back({ 0,29 });
	list.push_back({ 0,7 });
	list.push_back({ 0,8 });
	list.push_back({ 0,14 });
	list.push_back({ 0,23});
	list.push_back({ 0,3 });
	list.push_back({ 0,11 });
}

