/*
2. 小于当前数的数
题目描述
给你一个数组 nums，对于其中每个元素 nums[i]，请你统计数组中比它小的所有数字的数目。

换而言之，对于每个 nums[i] 你必须计算出有效的 j 的数量，其中 j 满足 j != i 且 nums[j] < nums[i]。

关于输入
第一行是一个整数 n，表示数组大小。
接下来 n 行，每行表示数组中的一个数。

0 <= n <= 1000, 每个数都在int可以表示的范围内.

关于输出
n 行，每行代表数组中比它小的数的个数。

如果没有要输出的数据，输出"None"。

例子输入
5
8
1
2
2
3
例子输出
4
0
1
1
3
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	int n = 0;
	int num[1010] = { 0 };
	cin >> n;
	if (n == 0)
		cout << "None" << endl;
	else
	{
		for (int i = 0; i < n; i++)
		{
			cin >> num[i];
		}
		int less[1010] = { 0 };
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (num[j] < num[i])
					less[i]++;
			}
			cout << less[i] << endl;
		}
	}
	return 0;
}