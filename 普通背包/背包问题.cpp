// 背包问题.cpp 

#include "pch.h"
#include "Package.h""
#include <iostream>
#include <fstream>
int main()
{
	fstream fin("data.txt");
	vector<item> items;
	int carry;
	fin >> carry;
	while (fin.peek() != EOF)
	{
		item i;

		fin >> i.num >> i.w >> i.v;
		items.push_back(i);
	}
	Package package(carry, &items);
	package.print();
	return 0;
}
