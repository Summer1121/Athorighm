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
	vector<item> *items;//��Ʒ����
	int num;//��Ʒ����
	int carry;//����������
};
struct item
{
	int w, v, num = 1;
	double quantity = 0;//����
};
