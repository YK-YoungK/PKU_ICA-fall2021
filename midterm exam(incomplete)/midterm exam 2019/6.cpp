/*
6. 谁能拿到最多的硬币
题目描述
有n个硬币排成一排，每个硬币上用一个数字标识了它的价值。每次要你从最左边或者最右边拿出一个硬币。总共拿k次，写一个算法，使能拿到的硬币的价值和最大。

关于输入
输入包含两行，第一行为n， k；
第二行包含n个数字，表示n个硬币的价值。

1 <= k <= n <= 100000
单个硬币的价值大于0且不超过10000.

关于输出
输出可以拿到的k个硬币最大的价值和。

例子输入
6 3
5 4 3 2 1 6
例子输出
15
提示信息
上面的解法是，从左边取两个，右边取一个硬币。
*/
#include <iostream>
using namespace std;
int main()
{
	int n = 0, k = 0;
	cin >> n >> k;
	int price[100010] = { 0 };
	for (int i = 0; i < n; i++)
	{
		cin >> price[i];
	}

	int num[100010] = { 0 };//记录所有可能
	for (int i = 0; i < k; i++)
	{
		num[0] = num[0] + price[i];
	}
	for (int i=1;i<=k;i++)
	{
		num[i] = num[i - 1] - price[k - i] + price[n - i];
	}

	int max = 0;
	for (int i = 0; i < k; i++)
	{
		if (num[i] > max)
			max = num[i];
	}
	cout << max << endl;
	return 0;
}