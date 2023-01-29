/*
7. 求逆序对数
题目描述
对于一个长度为 n 的整数序列 a，i 和 j 分别为序列中元素的下标，对于那些 满足 i < j 且 a[i] > a[j] 的“整数对”(i,j)，称为该整数序列的一个“逆序对”。请编写程序对于给出的整数序列，求出该序列中所有“逆序对”的个数.

关于输入
输入有两行，第一行为整数n(1 <= N <= 200)，第二行为n个整数，表示长度为n的整数序列.

关于输出
输出为一行，输出“逆序对”的个数.

例子输入
8
250 74 659 931 273 545 879 924
例子输出
7
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	int n = 0;
	int num[250] = { 0 };
	int count = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (num[i] > num[j])
				count++;
		}
	}
	cout << count << endl;
}