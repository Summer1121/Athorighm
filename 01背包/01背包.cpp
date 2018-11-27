//01背包

#include "pch.h"
#include "Package.h"

int main()
{
	fstream fin("data.txt");
	int carry;
	fin >> carry;
	vector<item>items;
	while (fin.peek() != EOF)
	{
		item i;
		fin >> i.num >> i.weight >> i.value;
		items.push_back(i);
	}
	Package package(items, carry);
	package.getAns();
}
