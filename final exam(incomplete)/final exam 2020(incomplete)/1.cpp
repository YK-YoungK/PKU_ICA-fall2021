/*
1. 最长连号
题目描述
输入n个正整数，（1<=n<=10000),要求输出最长的连号的长度。（连号指从小到大连续自然数）

关于输入
第一行，一个数n;  第二行，n个正整数，之间用空格隔开。

关于输出
一个数，最长连号中数的个数。

例子输入
10 
3 5 6 2 3 4 5 6 8 9
例子输出
5
提示信息
例子输入中，最长连号是 2 3 4 5 6，其中有5个数。
*/
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int n = 0;
	cin >> n;
	int num[10005] = { 0 };
	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
	}
	int result[10005] = { 0 };
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (num[j] - num[i] == j - i)
				result[i]++;
			else
				break;
		}
	}
	int maxium = 0;
	for (int i = 0; i < n; i++)
		maxium = max(maxium, result[i]);
	cout << maxium << endl;
	return 0;
}