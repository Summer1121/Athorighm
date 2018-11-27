#pragma once
#include <vector>
using namespace std;
class CQueen {
public:
	CQueen() {};
	~CQueen();
	CQueen(int n);
	void initQueen();
	void printAll();//输出所有解
	void printFirstM(long long m);//输出前m个解
	void printFirst();//输出第一个解
	long long getSum();//获取总解数
	void getResult();
	int getN();
private:
	bool isLocalable(int x, int y);
	void findAns(int x);
	void rollBack(int x, int* ori);
	int n;//皇后数
	long long sum = 0;//总解数
	int* ans;//一个解向量
	vector<int*> anss;//所有解向量
};

