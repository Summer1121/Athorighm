// 第k小问题.cpp : 

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
int main()
{
	fstream fin("data.txt");
	priority_queue<int, vector<int>, greater<int> > q;
	while (fin.peek() != EOF)
	{
		int num;
		fin >> num;
		q.push(num);
	}
	int k;
	cin >> k;
	if (k > q.size())
	{
		cout << "Not Existed";
		return 0;
	}
	else
	{
		while (--k)
		{
			q.pop();
		}
		cout << q.top();
	}
}
