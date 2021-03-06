// 最大子段和.cpp 

#include "pch.h"
#include "CMaxSum.h"
int main()
{
	int n;
	cin >> n;
	vector<int> nums(n);

	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		nums[i] = rand() - (RAND_MAX >> 1);//产生-16383~16384的随机数1
	}

	//fstream fin("data.txt");
	//for (int i = 0; i < n; i++)
	//{
	//	fin >> nums[i];
	//}

	for (int i = 0; i < n; i++)
	{
		cout << nums[i] << "\t";
	}
	cout << endl;


	CMaxSum f(nums);
	double start, end, cast;

	cout << "\n暴力 O(N^3)\n";
	start = clock();
	f.BruteForce();
	end = clock();
	cout << "时间：" << end - start << endl;


	cout << "\n暴力 O(N^2)\n";
	start = clock();
	f.BruteForce2();
	end = clock();
	cout << "时间：" << end - start << endl;

	cout << "\n分治\n";
	start = clock();
	f.handleResult(f.DivideAndConquer(0, nums.size() - 1));
	end = clock();
	cout << "时间：" << end - start << endl;


	cout << "\n动态\n";
	start = clock();
	f.DynamicProg();
	end = clock();
	cout << "时间：" << end - start << endl;

}
