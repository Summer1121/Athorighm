//哈夫曼：基于贪心算法的哈夫曼树与哈夫曼编码

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <thread>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;

//用于记录当前字符和出现次数
struct word
{
	char a;//非中文字符只有a，且a>=0
	char b;//中文字符a、b小于0
	int times;//出现次数
	string haffman;//编码
	int num;//0或者1
	int index;//在数组中的位置
	word* left = NULL;
	word* right = NULL;
	//比较函数
	bool operator >(const word &a)const
	{
		return times > a.times;
	}
};

//vector中查找本字符，返回位置，否则返回-1
int find(char a, char b);
//深度遍历，获取叶子节点haffman编码
void getover(string str, word* node);



priority_queue< word, vector<word>, greater<word> > q;
vector<word*> words;
//相对路径
fstream fin("haffmanIn.txt");
fstream fout("haffmanOut.txt");
//绝对路径
//fstream fin("D:\\课程实验\\算法设计\\Algorithm\\哈夫曼\\haffmanIn.txt");
//fstream fout("D:\\课程实验\\算法设计\\Algorithm\\哈夫曼\\haffmanOut.txt");

word* head;
string sec;//获取到的二进制码；



//读取文件，初始化words数组
void initWords()
{
	char a, b = 0;
	while (fin.peek() != EOF) {
		a = fin.get();
		if (a < 0) {//为中文，多读取一个字
			b = fin.get();
		}
		int index = find(a, b);
		if (index == -1) {//没有出现过
			word *w = new word();
			w->a = a;
			w->b = b;
			w->times = 1;
			words.push_back(w);
		}
		else
		{
			words[index]->times++;
		}
	}
	for (int i = 0; i < words.size(); i++)
	{
		words[i]->index = i;
	}
}
//vector中查找本字符，返回位置，否则返回-1
int find(char a, char b) {
	if (words.size() != 0) {
		//非中文
		if (a >= 0) {
			for (int i = 0; i < words.size(); i++) {
				if (words[i]->a == a) return i;
			}
		}
		//中文
		else
		{
			for (int i = 0; i < words.size(); i++) {
				if (words[i]->a == a && words[i]->b == b) return i;
			}
		}
	}
	return -1;
}

//使用优先队列构建haffman编码树
void CreatTree()
{
	//获取小根堆
	for (int i = 0; i < words.size(); i++)
	{
		q.push(*words[i]);
	}

	//依次出队 再入队
	while (q.size() != 1)
	{
		word *a;//出队的两个
		word *b;

		word *c = new word();//入队的一个

		a = words[q.top().index];
		q.pop();
		b = words[q.top().index];
		q.pop();

		//设置左孩子属性
		a->num = 0;
		//设置右孩子属性
		b->num = 1;

		//设置父节点
		c->left = a;
		c->right = b;
		c->times = a->times + b->times;

		//父节点加入队列 和 数组
		c->index = words.size();
		words.push_back(c);
		if (q.empty())
		{
			head = c;
			break;
		}
		q.push(*c);
	}
	//深度遍历，获取叶子节点haffman编码
	getover("", head);
}

//深度遍历，获取叶子节点haffman编码
void getover(string str, word* node)
{
	//如果是叶子节点
	if (node->left == NULL && node->right == NULL)
	{
		node->haffman.assign(str);
	}
	//如果不是
	else
	{
		if (node->left != NULL)
		{
			str.append("0");
			getover(str, node->left);
			str.erase(str.length() - 1, 1);
		}
		if (node->right != NULL)
		{
			str.append("1");
			getover(str, node->right);
		}
	}
}

//打印所有字符的编码
void paintHaffman() {
	for (int i = 0; i < words.size(); i++) {
		//当左右孩子都为空时才是叶子节点（字符）
		if (words[i]->left == NULL && words[i]->right == NULL) {
			if (words[i]->a == 10)
			{
				cout << "\\n";
			}
			else if (words[i]->a == 32)
			{
				cout << "space";
			}
			else
			{
				cout << words[i]->a;
			}
			if (words[i]->a < 0)
				cout << words[i]->b;
			cout << "\t" << words[i]->times << "\t" << words[i]->haffman << endl;
		}
	}
}

//输出haffman
void OutputTree(word* node) {
	//如果是叶子节点
	if (node->left == NULL && node->right == NULL)
	{
		if (node->a == 10)
		{
			cout << "\\n";
		}
		else if (node->a == 32)
		{
			cout << "space";
		}
		else
		{
			cout << node->a;
		}
		if (node->a < 0)
			cout << node->b;
		cout << "\t" << node->times << "\t" << node->haffman << endl;
	}
	//如果不是
	else
	{
		if (node->left != NULL)
		{
			OutputTree(node->left);
		}
		if (node->right != NULL)
		{
			OutputTree(node->right);
		}
	}
}

//输出文章的二进制编码
void OutputCode() {
	fin.seekg(0);
	while (fin.peek() != EOF)
	{
		char a, b = 0;
		a = fin.get();
		if (a < 0) {//为中文，多读取一个字
			b = fin.get();
		}
		int index = find(a, b);
		sec.append(words[index]->haffman);
	}
}
//数值分析
void getComrAadio() {
	unsigned long long origin = 0;
	unsigned long long  haffman = 0;
	unsigned long long sum = 0;
	for (int i = 0; i < (words.size() + 1) / 2; i++) {
		sum += words[i]->num;
		if (words[i]->a < 0)
		{
			origin += words[i]->num << 4;
		}
		else
		{
			origin += words[i]->num << 3;
		}
		haffman += words[i]->num*words[i]->haffman.length();
	}
	//平均码长
	cout << "平均码长:" << endl;
	cout << "\t原文件：" << (double)origin / sum << endl;
	cout << "\thaffman：" << (double)haffman / sum << endl;
	//压缩率
	cout << "压缩率：" << (double)haffman / origin << endl;
}

//解码
void dehaffman() {
	word* p = head;
	for (int i = 0; i < sec.length(); ) {
		while (p->left != NULL || p->right != NULL)
		{
			char num = sec[i++];
			if (num == '0')
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
		fout << (char)p->a;
		if ((char)p->a < 0)
		{
			fout << (char)p->b;
		}
		p = head;
	}
}

int main() {
	//string filestr;
	//cin >> filestr;
	initWords();
	CreatTree();

	//按照录入顺序输出
	/*paintHaffman();
	cout << endl;*/

	//按照树状输出
	OutputTree(head);
	cout << endl;
	

	//输出haffman编码的二进制文档
	OutputCode();
	cout << sec;


	//输出压缩率
	cout << endl;
	getComrAadio();

	//将解码的文件放入文档
	dehaffman();
}