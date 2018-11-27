//������������̰���㷨�Ĺ������������������

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <thread>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;

//���ڼ�¼��ǰ�ַ��ͳ��ִ���
struct word
{
	char a;//�������ַ�ֻ��a����a>=0
	char b;//�����ַ�a��bС��0
	int times;//���ִ���
	string haffman;//����
	int num;//0����1
	int index;//�������е�λ��
	word* left = NULL;
	word* right = NULL;
	//�ȽϺ���
	bool operator >(const word &a)const
	{
		return times > a.times;
	}
};

//vector�в��ұ��ַ�������λ�ã����򷵻�-1
int find(char a, char b);
//��ȱ�������ȡҶ�ӽڵ�haffman����
void getover(string str, word* node);



priority_queue< word, vector<word>, greater<word> > q;
vector<word*> words;
//���·��
fstream fin("haffmanIn.txt");
fstream fout("haffmanOut.txt");
//����·��
//fstream fin("D:\\�γ�ʵ��\\�㷨���\\Algorithm\\������\\haffmanIn.txt");
//fstream fout("D:\\�γ�ʵ��\\�㷨���\\Algorithm\\������\\haffmanOut.txt");

word* head;
string sec;//��ȡ���Ķ������룻



//��ȡ�ļ�����ʼ��words����
void initWords()
{
	char a, b = 0;
	while (fin.peek() != EOF) {
		a = fin.get();
		if (a < 0) {//Ϊ���ģ����ȡһ����
			b = fin.get();
		}
		int index = find(a, b);
		if (index == -1) {//û�г��ֹ�
			word *w = new word();
			w->a = a;
			w->b = b;
			w->times = 1;
			words.push_back(w);
		}
		else
		{
			words[index]->times++;
		}
	}
	for (int i = 0; i < words.size(); i++)
	{
		words[i]->index = i;
	}
}
//vector�в��ұ��ַ�������λ�ã����򷵻�-1
int find(char a, char b) {
	if (words.size() != 0) {
		//������
		if (a >= 0) {
			for (int i = 0; i < words.size(); i++) {
				if (words[i]->a == a) return i;
			}
		}
		//����
		else
		{
			for (int i = 0; i < words.size(); i++) {
				if (words[i]->a == a && words[i]->b == b) return i;
			}
		}
	}
	return -1;
}

//ʹ�����ȶ��й���haffman������
void CreatTree()
{
	//��ȡС����
	for (int i = 0; i < words.size(); i++)
	{
		q.push(*words[i]);
	}

	//���γ��� �����
	while (q.size() != 1)
	{
		word *a;//���ӵ�����
		word *b;

		word *c = new word();//��ӵ�һ��

		a = words[q.top().index];
		q.pop();
		b = words[q.top().index];
		q.pop();

		//������������
		a->num = 0;
		//�����Һ�������
		b->num = 1;

		//���ø��ڵ�
		c->left = a;
		c->right = b;
		c->times = a->times + b->times;

		//���ڵ������� �� ����
		c->index = words.size();
		words.push_back(c);
		if (q.empty())
		{
			head = c;
			break;
		}
		q.push(*c);
	}
	//��ȱ�������ȡҶ�ӽڵ�haffman����
	getover("", head);
}

//��ȱ�������ȡҶ�ӽڵ�haffman����
void getover(string str, word* node)
{
	//�����Ҷ�ӽڵ�
	if (node->left == NULL && node->right == NULL)
	{
		node->haffman.assign(str);
	}
	//�������
	else
	{
		if (node->left != NULL)
		{
			str.append("0");
			getover(str, node->left);
			str.erase(str.length() - 1, 1);
		}
		if (node->right != NULL)
		{
			str.append("1");
			getover(str, node->right);
		}
	}
}

//��ӡ�����ַ��ı���
void paintHaffman() {
	for (int i = 0; i < words.size(); i++) {
		//�����Һ��Ӷ�Ϊ��ʱ����Ҷ�ӽڵ㣨�ַ���
		if (words[i]->left == NULL && words[i]->right == NULL) {
			if (words[i]->a == 10)
			{
				cout << "\\n";
			}
			else if (words[i]->a == 32)
			{
				cout << "space";
			}
			else
			{
				cout << words[i]->a;
			}
			if (words[i]->a < 0)
				cout << words[i]->b;
			cout << "\t" << words[i]->times << "\t" << words[i]->haffman << endl;
		}
	}
}

//���haffman
void OutputTree(word* node) {
	//�����Ҷ�ӽڵ�
	if (node->left == NULL && node->right == NULL)
	{
		if (node->a == 10)
		{
			cout << "\\n";
		}
		else if (node->a == 32)
		{
			cout << "space";
		}
		else
		{
			cout << node->a;
		}
		if (node->a < 0)
			cout << node->b;
		cout << "\t" << node->times << "\t" << node->haffman << endl;
	}
	//�������
	else
	{
		if (node->left != NULL)
		{
			OutputTree(node->left);
		}
		if (node->right != NULL)
		{
			OutputTree(node->right);
		}
	}
}

//������µĶ����Ʊ���
void OutputCode() {
	fin.seekg(0);
	while (fin.peek() != EOF)
	{
		char a, b = 0;
		a = fin.get();
		if (a < 0) {//Ϊ���ģ����ȡһ����
			b = fin.get();
		}
		int index = find(a, b);
		sec.append(words[index]->haffman);
	}
}
//��ֵ����
void getComrAadio() {
	unsigned long long origin = 0;
	unsigned long long  haffman = 0;
	unsigned long long sum = 0;
	for (int i = 0; i < (words.size() + 1) / 2; i++) {
		sum += words[i]->num;
		if (words[i]->a < 0)
		{
			origin += words[i]->num << 4;
		}
		else
		{
			origin += words[i]->num << 3;
		}
		haffman += words[i]->num*words[i]->haffman.length();
	}
	//ƽ���볤
	cout << "ƽ���볤:" << endl;
	cout << "\tԭ�ļ���" << (double)origin / sum << endl;
	cout << "\thaffman��" << (double)haffman / sum << endl;
	//ѹ����
	cout << "ѹ���ʣ�" << (double)haffman / origin << endl;
}

//����
void dehaffman() {
	word* p = head;
	for (int i = 0; i < sec.length(); ) {
		while (p->left != NULL || p->right != NULL)
		{
			char num = sec[i++];
			if (num == '0')
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
		fout << (char)p->a;
		if ((char)p->a < 0)
		{
			fout << (char)p->b;
		}
		p = head;
	}
}

int main() {
	//string filestr;
	//cin >> filestr;
	initWords();
	CreatTree();

	//����¼��˳�����
	/*paintHaffman();
	cout << endl;*/

	//������״���
	OutputTree(head);
	cout << endl;
	

	//���haffman����Ķ������ĵ�
	OutputCode();
	cout << sec;


	//���ѹ����
	cout << endl;
	getComrAadio();

	//��������ļ������ĵ�
	dehaffman();
}