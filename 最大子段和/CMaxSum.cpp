#include "pch.h"
#include "CMaxSum.h"


CMaxSum::CMaxSum()
{
}

CMaxSum::CMaxSum(vector<int> nums)
{
	this->nums.assign(nums.begin(), nums.end());
}

//����O(n3)
void CMaxSum::BruteForce()
{
	maxAns.clear();
	int max = INT32_MIN, index = 0, length = 0;
	for (int i = 1; i <= nums.size(); i++)//����
	{
		for (int start = 0; start + i - 1 < nums.size(); start++)//��ʼλ��
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

//����O(n2)
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

//����
result CMaxSum::DivideAndConquer(int start, int end)// �����ַ�Ϊ���Σ�����Ӷ�Ϊǰһ����ߺ�һ��������м䲿λ��ɵ���ӶΡ�
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
	result res1 = DivideAndConquer(start, middle);//���Ӷ�
	result res2 = DivideAndConquer(middle + 1, end);//���Ӷ�
	result res3{ 0,middle,middle + 1 };//�����м䣬�Ұ���middle����ӶκͰ���middle+1����Ӷ�
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

//��̬�滮
void CMaxSum::DynamicProg()
{
	maxAns.clear();
	int max = INT32_MIN, sum = nums[0], start = 0, end = 0;
	for (int i = 1; i < nums.size(); i++)
	{
		//���ǰn��ʹ���0����num[i]����
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
	cout << "��Ӷγ��ȣ�\t" << maxAns.size() << endl;
	cout << "��Ӷκͣ�\t" << sum << endl;
	cout << "��ӶΣ�\t";
	for (int i = 0; i < maxAns.size(); i++)
	{
		cout << maxAns[i] << "\t";
	}
	cout << endl;
}
