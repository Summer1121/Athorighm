#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
#include <algorithm>
#include <ctime>
#include <fstream>
using namespace std;
struct result
{
	int sum, start, end;
};
class CMaxSum
{
public:
	CMaxSum();
	CMaxSum(vector<int> nums);
	void BruteForce();
	void BruteForce2();
	result DivideAndConquer(int start, int end);
	void handleResult(result res);
	void DynamicProg();
	~CMaxSum();
	void print();
private:
	vector<int> nums;//数据
	vector<int> maxAns;//最长子段
	int sum;//最长字段和
};

