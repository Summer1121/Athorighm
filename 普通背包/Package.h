#pragma once
#include <iostream>
#include <vector>
using namespace std;
struct item;
class Package
{
public:

	Package();
	Package(int carry, vector<item> *items);
	void getAns();
	~Package();
	void print();

private:
	vector<item> *items;//物品数组
	int num;//物品数量
	int carry;//背包总重量
};
struct item
{
	int w, v, num = 1;
	double quantity = 0;//数量
};
