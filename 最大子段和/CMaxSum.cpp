#include "pch.h"
#include "CMaxSum.h"


CMaxSum::CMaxSum()
{
}

CMaxSum::CMaxSum(vector<int> nums)
{
	this->nums.assign(nums.begin(), nums.end());
}

//暴力O(n3)
void CMaxSum::BruteForce()
{
	maxAns.clear();
	int max = INT32_MIN, index = 0, length = 0;
	for (int i = 1; i <= nums.size(); i++)//长度
	{
		for (int start = 0; start + i - 1 < nums.size(); start++)//起始位置
		{
			int tempSum = 0;
			for (int j = 0; j < i; j++)
			{
				tempSum += nums[start + j];
			}
			if (tempSum > max)
			{
				max = tempSum;
				index = start;
				length = i;
			}
		}
	}
	this->sum = max;
	for (int i = 0; i < length; i++)
	{
		maxAns.push_back(nums[index + i]);
	}
	print();
}

//暴力O(n2)
void CMaxSum::BruteForce2()
{
	maxAns.clear();
	int max = INT32_MIN, sta, end;
	for (int start = 0; start < nums.size(); start++)
	{
		int sum = 0;
		for (int i = start; i < nums.size(); i++)
		{
			sum += nums[i];
			if (sum > max)
			{
				max = sum;
				sta = start;
				end = i;
			}
		}
	}
	for (int i = sta; i <= end; i++)
	{
		maxAns.push_back(nums[i]);
		sum = max;
	}
	print();
}

//分治
result CMaxSum::DivideAndConquer(int start, int end)// 将数字分为两段，则最长子段为前一半或者后一半或者在中间部位组成的最长子段。
{
	result ans;
	if (start == end)
	{
		ans.start = start;
		ans.end = end;
		ans.sum = nums[start];
		return ans;
	}
	int middle = (start + end) >> 1;
	result res1 = DivideAndConquer(start, middle);//左子段
	result res2 = DivideAndConquer(middle + 1, end);//右子段
	result res3{ 0,middle,middle + 1 };//两段中间，找包含middle的最长子段和包含middle+1的最长子段
	int max1 = INT32_MIN, max2 = INT32_MIN;
	int sum = 0;
	for (int i = middle; i >= start; i--)
	{
		sum += nums[i];
		if (sum > max1)
		{
			max1 = sum;
			res3.start = i;
		}
	}
	sum = 0;
	for (int i = middle + 1; i <= end; i++)
	{
		sum += nums[i];
		if (sum > max2)
		{
			max2 = sum;
			res3.end = i;
		}
	}
	res3.sum = max1 + max2;
	if (res1.sum > res2.sum && res1.sum > res3.sum)
	{
		return res1;
	}
	else if (res2.sum > res1.sum && res2.sum > res3.sum)
	{
		return res2;
	}
	else
	{
		return res3;
	}
}

void CMaxSum::handleResult(result res)
{
	maxAns.clear();
	for (int i = res.start; i <= res.end; i++)
	{
		maxAns.push_back(nums[i]);
	}
	sum = res.sum;
	print();
}

//动态规划
void CMaxSum::DynamicProg()
{
	maxAns.clear();
	int max = INT32_MIN, sum = nums[0], start = 0, end = 0;
	for (int i = 1; i < nums.size(); i++)
	{
		//如果前n项和大于0，则将num[i]加入
		if (sum > 0)
		{
			sum += nums[i];
		}
		//sum<=0
		else if (sum < nums[i])
		{
			sum = nums[i];
			if (sum > max)
			{
				start = i;
			}
		}
		if (sum > max)
		{
			max = sum;
			end = i;
		}
	}
	this->sum = max;
	for (int i = start; i <= end; i++)
	{
		maxAns.push_back(nums[i]);
	}
	print();
}

CMaxSum::~CMaxSum()
{
}



void CMaxSum::print()
{
	cout << "最长子段长度：\t" << maxAns.size() << endl;
	cout << "最长子段和：\t" << sum << endl;
	cout << "最长子段：\t";
	for (int i = 0; i < maxAns.size(); i++)
	{
		cout << maxAns[i] << "\t";
	}
	cout << endl;
}
