#include "..\01背包\Package.h"
#include "pch.h"
#include "Package.h"
#include <algorithm>
#include <iomanip>
Package::Package()
{
}

Package::Package(int carry, vector<item> *items)
{
	this->carry = carry;
	this->items = items;
	this->num = items->size();
	getAns();
}

bool cmp(const item &a, const item &b)
{
	return  ((float)a.v / a.w) > ((float)b.v / b.w);
}
bool cmp2(const item &a, const item &b)
{
	return a.num < b.num;
}

void Package::getAns()
{
	sort(items->begin(), items->end(), cmp);
	int sum = 0;
	for (int i = 0; i < items->size(); i++)
	{
		if ((*items)[i].w + sum > carry)
		{
			(*items)[i].quantity = (float)(carry-sum) / ((*items)[i].w);
			break;
		}
		else
		{
			(*items)[i].quantity = 1;
			sum += (*items)[i].w;
		}
	}
	sort(items->begin(), items->end(), cmp2);
}



Package::~Package()
{

}

void Package::print()
{
	float sum = 0;
	for (int i = 0; i < num; i++)
	{
		if (i == 0)cout << "\t";
		cout << (*items)[i].num << "\t";
	}
	cout << endl;
	for (int i = 0; i < num; i++)
	{
		if (i == 0)cout << "重量\t";
		cout << (*items)[i].w << "\t";
	}
	cout << endl;
	for (int i = 0; i < num; i++)
	{
		if (i == 0)cout << "价值\t";
		cout << (*items)[i].v << "\t";
	}
	cout << endl;
	for (int i = 0; i < num; i++)
	{
		if (i == 0)cout << "数量\t";
		cout << setprecision(3) << (*items)[i].quantity << "\t";
		sum += (*items)[i].quantity*(*items)[i].v;
	}
	cout << setprecision(6) << endl << "总价值：" << sum << endl;
}

