// 格路问题.cpp 简单格路问题仅仅计算路径数量

#include "pch.h"
#include <iostream>
//#include <>
using namespace std;

struct node
{
	bool up = false, right = false;
};

node** nodes;

int sum;

int x, y;//终点坐标

//初始化节点表格,某单元格的表示为（nodes[y][x]）上为y正方向，右为x正方向
void getform()
{
	nodes = new node*[y + 1];//下标由0到y
	for (int i = 0; i <= y; i++)
	{
		nodes[i] = new node[x + 1];//下标由0到x
		nodes[i][x].right = true;//右边界
	}
	for (int i = 0; i < x + 1; i++)
	{
		nodes[y][i].up = true;//上边界
	}
}

void backTrack()
{
}

void getSum(int a, int b)
{
	if (x == a && y == b)
	{
		sum++; return;
	}
	if (!nodes[b][a].up)
	{
		getSum(a, b + 1);
	}
	if (!nodes[b][a].right)
	{
		getSum(a + 1, b);
	}
}
int main()
{
	cin >> x >> y;
	getform();
	getSum(0, 0);
	cout << sum;
	return 0;
}

