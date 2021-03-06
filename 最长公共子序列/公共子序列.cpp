// 公共子序列.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct node {
	int x, y;
	string str = "";
	node*  pre = NULL;
};

fstream fin("date.txt");
string x, y;
string res;
node** form;

//初始化计算表 纵向为x数组，横向为y数组
void createForm()
{
	form = new node*[x.size()];
	for (int i = 0; i < x.size(); i++)
	{
		form[i] = new node[y.size()];
		for (int j = 0; j < y.size(); j++)
		{
			form[i][j].x = i;
			form[i][j].y = j;
		}
	}
}

void getStr(int a, int b)
{
	//如果是第一个单元格
	if (a == 0 && b == 0)
	{
		if (x[0] != y[0])
			return;
		else
		{
			form[a][b].str = x[a];
			return;
		}
	}
	//如果是第一行
	else if (a == 0)
	{
		form[a][b].pre = &form[a][b - 1];
		//如果前方没有相等
		if (form[a][b].pre->str.length() == 0)
		{
			if (x[a] != y[b])
				return;
			form[a][b].str = y[b];
		}
		else
		{
			form[a][b].str = form[a][b].pre->str;
		}
		return;
	}
	//如果是第一列
	else if (b == 0)
	{
		form[a][b].pre = &form[a - 1][b];
		//如果前方没有相等
		if (form[a][b].pre->str.length() == 0)
		{
			if (x[a] != y[b])
				return;
			form[a][b].str = y[b];
		}
		else
		{
			form[a][b].str = form[a][b].pre->str;
		}
		return;
	}


	if (x[a] == y[b])
	{
		form[a][b].pre = &form[a - 1][b - 1];
		form[a][b].str = form[a - 1][b - 1].str + x[a];
	}
	else
	{
		if (form[a - 1][b].str.length() >= form[a][b - 1].str.length())
		{
			form[a][b].pre = &form[a - 1][b];
		}
		else
		{
			form[a][b].pre = &form[a][b - 1];
		}
		form[a][b].str = form[a][b].pre->str;
	}
}

void getAns()
{
	for (int i = 0; i < x.length(); i++)
	{
		for (int j = 0; j < y.length(); j++)
		{
			getStr(i, j);
		}
	}
}

//输出表格
void paint()
{
	for (int i = 0; i < x.length(); i++)
	{
		for (int j = 0; j < y.length(); j++)
		{
			node n = form[i][j];
			if (i != 0 || j != 0)
			{
				node m = *form[i][j].pre;
				if (n.x - 1 == m.x && n.y - 1 == m.y)
				{
					cout << "↖ ";
				}
				else if (n.x - 1 == m.x)
				{
					cout << "↑ ";
				}
				else if (n.y - 1 == m.y)
				{
					cout << "← ";
				}
			}
			cout << n.str.length() << "\t";

		}
		cout << endl;
	}
}


int main()
{
	fin >> x >> y;
	createForm();
	getAns();
	node* node = &form[x.length() - 1][y.length() - 1];
	cout << "最长子序列：" << node->str << endl;
	cout << "长度为:" << node->str.length() << endl;
	paint();
	return 0;
}
