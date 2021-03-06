// 归并排序:编写基于归并排序的算法实现，并与sort函数比较时间

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <thread>
using namespace std;

//用于复制数组
template <typename T>
void copy(vector<T> &a, vector<T> &b, int start);
//分
template <typename T>
void MergeSort(vector<T> &a, int start_index, int end_index);
//治
template <typename T>
void rule(vector<T> &a, int start, int middle, int end);


template <typename T>
void MergeSort(vector<T> &a, int start_index, int end_index) {
	//分
	if (start_index < end_index) {//只剩下一个元素

		int middle = (start_index + end_index) >> 1;
		//左
		MergeSort(a, start_index, middle);
		//l.join();
		//右
		MergeSort(a, middle + 1, end_index);
		//r.join();

		//治
		rule(a, start_index, middle, end_index);
	}
}

//治
template <typename T>
void rule(vector<T> &a, int start, int middle, int end) {
	int i = start, j = middle + 1;
	int n = end - start + 1;//结果位数
	vector<T> result(n);
	int k = 0;
	//将较小项加入结果数组
	while (i <= middle && j <= end)
	{
		if (a[i] <= a[j]) {
			result[k++] = a[i++];
		}
		else if (a[i] > a[j])
		{
			result[k++] = a[j++];
		}
	}
	//如果一方已经全部加入，则将另一方直接放入数组
	while (j <= end)
	{
		result[k++] = a[j++];
	}
	while (i <= middle)
	{
		result[k++] = a[i++];
	}
	for (int i = 0; i < n; i++) {
		a[start + i] = result[i];
	}
	//copy(a, result, start);
}

//将一个vector的数值复制进一个vector的对应位置
//a为原数组，b为取值数组，start为复制入位置
template <typename T>
void copy(vector<T> &a, vector<T> &b, int start) {
	for (int i = 0; i < b.size(); i++) {
		a[start + i] = b[i];
	}
}

//产生随机数
template <class T, class L>
vector<T> getRandomNums(L count, T a) {
	srand((int)time(0));
	vector<T>  res;
	while (count--)
	{
		res.push_back(rand());
	}
	return res;
}

int main()
{
	cout << "输入排序位数：";
	//产生随机数
	long length;
	cin >> length;
	double a = 0;
	vector<double> ints = getRandomNums(length, a);
	vector<double> ints2;
	ints2.assign(ints.begin(), ints.end());
	/*int a = 10;
	while (a--)
	{
		int k;
		cin >> k;
		ints.push_back(k);
	}*/
	double start, end, cost1, cost2;

	//归并算法
	start = clock();
	MergeSort(ints, 0, ints.size() - 1);
	end = clock();
	cost1 = end - start;

	//stl的算法
	start = clock();
	sort(ints2.begin(), ints2.end());
	end = clock();
	cost2 = end - start;

	if (ints == ints2)
	{
		cout << "equal" << endl;
	}
	else
	{
		cout << "not equal" << endl;
	}

	cout << "my algorithm：" << cost1 << endl;
	cout << "stl algorithm：" << cost2 << endl;

	/*for (int i = 0; i < ints.size(); i++) {
		cout << ints[i] << endl;
	}
	cout << endl;
	for (int i = 0; i < ints.size(); i++) {
		cout << ints2[i] << endl;
	}
	cout << endl;*/
	return 0;
}