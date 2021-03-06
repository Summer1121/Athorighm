// 多机调度.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

struct task
{
	int num, time;
	bool operator<(const task &m)const
	{
		return time < m.time;
	}
};
struct machine
{
	vector<task> tasks;
	int sum_time = 0;
	bool operator>(const machine &m)const
	{
		return sum_time > m.sum_time;
	}
};

//将当前最小时间任务压入总时间最短的处理机，又将此处理机压入
void push_in_machine(priority_queue<machine, vector<machine>, greater<machine> >* machines, priority_queue<task, vector<task>, less<task> >* tasks)
{
	machine m = *const_cast<machine*>(&machines->top());
	task *t = const_cast<task*>(&tasks->top());
	m.sum_time += t->time;
	m.tasks.push_back(*t);
	machines->pop();
	tasks->pop();
	machines->push(m);
}

void print(priority_queue<machine, vector<machine>, greater<machine> >* machines)
{
	int max = 0;
	int m = machines->size();
	for (int i = 0; i < m; i++)
	{
		cout << "处理机" << i << ":\t";
		for (int i = 0; i < machines->top().tasks.size(); i++)
		{
			cout << machines->top().tasks[i].num << "(" << machines->top().tasks[i].time << ")\t";
		}
		max = machines->top().sum_time ? machines->top().sum_time : max;
		machines->pop();
		cout << endl;
	}
	cout << "总时间:" << max << endl;
}
int main()
{
	int  m;//m个处理机
	cin >> m;
	priority_queue<machine, vector<machine>, greater<machine> > machines;
	for (int i = 0; i < m; i++)
	{
		machine m;
		machines.push(m);
	}
	priority_queue<task, vector<task>, less<task> > tasks;//任务列表
	fstream fin("data.txt");
	int i = 0;
	while (fin.peek() != EOF)
	{
		task t;
		fin >> t.time;
		t.num = i++;
		tasks.push(t);
	}
	int n = tasks.size();
	for (int i = 0; i < n; i++)
	{
		push_in_machine(&machines, &tasks);
	}
	print(&machines);

	return 0;
}

