#include "pch.h"
#include "CQueen.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//������ flag==true or flag==false
CQueen::CQueen(int n)
{
	this->n = n;
	initQueen();//��ʼ��
	getResult();//ִ�м��㲢��ȡ���
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
//m��ʾ���� ,y��ʾλ��
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
	//��ǰ�е�ĳһ���Ƿ�ɷ���
	for (int i = 0; i < n; i++) {
		if (isLocalable(x, i))//���Է���
		{
			ans[x] = i;
			//�������һ��
			if (x + 1 == n)
			{
				int* p = ans;
				//�õ�һ�������
				anss.push_back(p);
				//����
				rollBack(x, p);
				return;
			}
			else
			{
				findAns(x + 1);
			}

		}
		//һ�е�ͷû�п��Է��õĵط��� ����
		if (i == n - 1)
		{
			int* p = ans;
			rollBack(x, p);
			delete p;
		}
	}
}
//x��ʾ��ǰ����
void CQueen::rollBack(int x, int* ori)
{
	//����һ���µĽ�����
	initQueen();
	//��õ�ǰ��������ǰһ��״̬
	for (int i = 0; i < x - 1; i++)
	{
		ans[i] = ori[i];
	}
}
//m��ʾ����
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
