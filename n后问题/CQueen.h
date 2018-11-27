#pragma once
#include <vector>
using namespace std;
class CQueen {
public:
	CQueen() {};
	~CQueen();
	CQueen(int n);
	void initQueen();
	void printAll();//������н�
	void printFirstM(long long m);//���ǰm����
	void printFirst();//�����һ����
	long long getSum();//��ȡ�ܽ���
	void getResult();
	int getN();
private:
	bool isLocalable(int x, int y);
	void findAns(int x);
	void rollBack(int x, int* ori);
	int n;//�ʺ���
	long long sum = 0;//�ܽ���
	int* ans;//һ��������
	vector<int*> anss;//���н�����
};

