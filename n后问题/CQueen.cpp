#include "pch.h"
#include "CQueen.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//保存结果 flag==true or flag==false
CQueen::CQueen(int n)
{
	this->n = n;
	initQueen();//初始化
	getResult();//执行计算并获取结果
}

CQueen::~CQueen()
{
	for (int i = anss.size() - 1; i >= 0; i--)
	{
		delete anss[i];
	}
	anss.clear();
}

void CQueen::initQueen()
{
	ans = new int[n] {-1};
}
//m表示行数 ,y表示位置
bool CQueen::isLocalable(int x, int y) {
	if (x == 0)return true;
	for (int i = 0; i < x; i++)
	{
		if (ans[i] == y || abs(x - i) == abs(y - ans[i]))
		{
			return false;
		}
	}
	return true;
}

void CQueen::findAns(int x)
{
	//当前行的某一列是否可放置
	for (int i = 0; i < n; i++) {
		if (isLocalable(x, i))//可以放置
		{
			ans[x] = i;
			//到达最后一行
			if (x + 1 == n)
			{
				int* p = ans;
				//得到一组解向量
				anss.push_back(p);
				//回溯
				rollBack(x, p);
				return;
			}
			else
			{
				findAns(x + 1);
			}

		}
		//一行到头没有可以放置的地方了 回溯
		if (i == n - 1)
		{
			int* p = ans;
			rollBack(x, p);
			delete p;
		}
	}
}
//x表示当前行数
void CQueen::rollBack(int x, int* ori)
{
	//创建一个新的解向量
	initQueen();
	//获得当前解向量的前一个状态
	for (int i = 0; i < x - 1; i++)
	{
		ans[i] = ori[i];
	}
}
//m表示个数
void CQueen::printFirstM(long long m)
{
	if (sum != 0)
	{
		for (long long j = 0; j < ((m < sum) ? m : sum); j++)
		{
			for (int i = 0; i < this->n; i++)
			{
				if (i == 0)
					cout << "(";
				cout << anss[j][i];
				if (i != n - 1)
					cout << ",";
				else
					cout << ")" << endl;
			}
		}
	}
	else
	{
		cout << "No Answer" << endl;
	}
}

long long CQueen::getSum()
{
	this->sum = anss.size();
	return this->sum;
}

void CQueen::getResult()
{
	findAns(0);
	getSum();
}

int CQueen::getN()
{
	return this->n;
}

void CQueen::printAll()
{
	printFirstM(sum);
}

void CQueen::printFirst()
{
	printFirstM(1);
}
