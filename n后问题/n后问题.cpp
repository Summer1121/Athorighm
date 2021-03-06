// n后问题.cpp 

#include "pch.h"
#include "CQueen.h"
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	cout << "输入组数m:";
	int m, n;
	cin >> m;
	cout << "输入起始n:";
	cin >> n;
	cout << "组序号\t皇后数\t解数\t第一个解" << endl;
	for (int i = n; i < m + n; i++)
	{
		CQueen *q = new CQueen(i);

		cout << i - n << "\t";
		cout << q->getN() << "\t";
		cout << q->getSum() << "\t";
		q->printFirst();
		cout << "\t" << endl;
		q->~CQueen();
		delete q;
	}
	return 0;
}

