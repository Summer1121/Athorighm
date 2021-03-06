// 矩阵连乘.cpp : 

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
//运算表格元素
struct cell
{
	int x = 0, y = 0, sum = 0;
	int posi = 0;//断点位置
};
//矩阵
struct matrix
{
	int a, b;
};

fstream fin("numbers.txt");
cell** form;//运算用的表格
matrix* matrixs;//矩阵数组
int num;//矩阵数量

int mulCount(int a, int b, int c);



//通过传入的参数数组初始化矩阵数组
void getMatrix(vector<int> &dimen) {
	num = dimen.size() - 1;
	matrixs = new matrix[num];
	for (int i = 0; i < num; i++) {
		matrixs[i].a = dimen[i];
		matrixs[i].b = dimen[i + 1];
	}
}


//输出矩阵表达式
void getMatrixs() {
	for (int i = 0; i < num; i++) {
		cout << (matrixs[i].a) << "X" << (matrixs[i].b);
		if (i != num - 1)
		{
			cout << " * ";
		}
		else
		{
			cout << endl;
		}
	}
}

//创建计算表
void create() {
	form = new cell*[num];
	for (int i = 0; i < num; i++) {//外层行遍历 最后一行不需要
		form[i] = new cell[num];
		for (int j = 0; j < num; j++) {//内层列遍历
			//只取右上
			form[i][j].x = i;
			form[i][j].y = j;
			form[i][j].sum = 0;

		}
	}
}
//计算两个向量之间的最小运算量 a<b
int calu(int a, int b)
{
	//如果已经计算过
	if (form[a][b].sum != 0)
	{
		return form[a][b].sum;
	}
	if (a == b)
	{
		return 0;
	}
	//如果是相邻矩阵
	if (a + 1 == b) {
		form[a][b].sum = mulCount(a, a, b);
	}
	//否则
	else
	{
		//找到所有分割里面最少的
		int sum = calu(a, a) + calu(a + 1, b) + mulCount(a, a, b);//初始值;
		int posi = a;
		for (int i = a; i < b; i++) {
			int res = calu(a, i) + calu(i + 1, b) + mulCount(a, i, b);
			if (res < sum)
			{
				sum = res;
				posi = i;
			}
		}
		form[a][b].sum = sum;
		form[a][b].posi = posi;
	}
	return form[a][b].sum;
}
//两个矩阵乘积的运算数 a左矩阵 b中间矩阵 c末尾矩阵  相邻矩阵b=a
int mulCount(int a, int b, int c)
{
	return matrixs[a].a*matrixs[b].b*matrixs[c].b;
}

//输出结果表达式
struct symbol
{
	int leftParent = 0, rightParent = 0;
};
symbol* symbols;

//获取符号位置
void getExpression(int start, int end, symbol* symbols)
{
	if (start == end) {
		return;
	}
	else
	{
		symbols[start].leftParent++;
		symbols[end + 1].rightParent++;
	}
	if (start + 1 == end) {
		return;
	}
	int posi = form[start][end].posi;
	getExpression(start, posi, symbols);
	getExpression(posi + 1, end, symbols);
}
//输出表达式
void paint() {
	symbols = new symbol[num + 1];
	getExpression(0, num - 1, symbols);
	for (int i = 0; i < num; i++)
	{
		int l = symbols[i].leftParent, r = symbols[i].rightParent;
		while (r--)
		{
			cout << ")";
		}
		while (l--)
		{
			cout << "(";
		}
		cout << " " << (matrixs[i].a) << "X" << (matrixs[i].b) << " ";
	}
	int  r = symbols[num].rightParent;
	while (r--)
	{
		cout << ")";
	}
}
int main()
{
	vector<int> nums;
	while (fin.peek() != EOF) {
		int a;
		fin >> a;
		nums.push_back(a);
	}
	//顺序不能变
	//先初始化矩阵信息
	getMatrix(nums);

	//输出矩阵列表
	getMatrixs();

	//创建计算表格
	create();

	//输出计算结果次数结果
	cout << calu(0, nums.size() - 2) << endl;

	//输出结果表达式
	paint();
}