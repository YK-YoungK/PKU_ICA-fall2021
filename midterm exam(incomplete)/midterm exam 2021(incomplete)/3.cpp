/*
3. 习题(11-7) 最匹配的矩阵
题目描述
给定一个矩阵A[m,n](100 ≥ m ≥ 1,100 ≥ n ≥ 1) 和另一个矩阵B[r,s],有0 < r ≤ m, 0 < s ≤ n，A、B所有元素值都是小于100的正整数。求A中和B最匹配的矩阵C[r,s]，所谓最匹配是指B和C的对应元素差值的绝对值之和最小，如果有多个最佳匹配只需输出第一个（行号最小，行号相同时，列号最小）。

关于输入
第一行是m和n，以空格隔开
以下m行每行有n个整数，表示A矩阵中的各行
第m+2行为r和s，以空格隔开
以下r行每行有s个整数，表示B矩阵中的各行

关于输出
求出A中和B最匹配的矩阵C并输出之
注意：每一个数字后面都有空格，包括一行中的最后一个数字

例子输入
3 3
3 4 5
5 3 4
8 2 4
2 2
7 3
4 9
例子输出
4 5 
3 4 
提示信息
*/
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
	int m = 0, n = 0;
	cin >> m >> n;
	int juzhen1[150][150] = { 0 };
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> juzhen1[i][j];
		}
	}
	int r = 0, s = 0;
	cin >> r >> s;
	int juzhen2[150][150] = { 0 };
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < s; j++)
		{
			cin >> juzhen2[i][j];
		}
	}

	int min = 1<<30;
	int hang = 0, lie = 0;
	for (int i = 0; i + r - 1 <= m - 1; i++)
	{
		for (int j = 0; j + s - 1 <= n - 1; j++)
		{
			int tmp = 0;
			for (int k = 0; k < r; k++)
			{
				for (int l = 0; l < s; l++)
				{
					tmp = tmp + abs(juzhen1[i + k][j + l] - juzhen2[k][l]);
				}
			}
			if (tmp < min)
			{
				min = tmp;
				hang = i;
				lie = j;
			}
		}
	}

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < s; j++)
		{
			cout << juzhen1[hang + i][lie + j] << " ";
		}
		cout << endl;
	}
	return 0;
}
