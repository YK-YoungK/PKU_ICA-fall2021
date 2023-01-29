/*
8. 日期串
题目描述
今天是 2021 年 1 月 3 日，定义日期字符串 s 为把从今天开始到 9999 年 12 月 31 日的日期依次写下得到的字符串：

s = 202101032021010420210105...99991231

现在，给出 n 个数字 a[1] ... a[n]，你需要对于每一个数字求出它第一次在 s 中出现的位置（s 的下标从 1 开始）。

关于输入
第一行输入一个整数 n，表示数字的个数 (1 <= n <= 100)。

接下来每行输入一个整数，表示 a[i] (0 <= a[i] <= 100)。

关于输出
输出 n 行，每行一个整数，表示答案。如果 a[i] 在 s 中没有出现，则输出 -1.

例子输入
5
0
5
9
14
97
例子输出
2
24
56
95
222059
提示信息
*/
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;
int runnian(int y)
{
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		return 1;
	else
		return 0;
}
int main()
{
	int n = 0;
	cin >> n;
	int ping2021[13] = { 0,29,28,31,30,31,30,31,31,30,31,30,31 };
	while (n > 0)
	{
		int m = 0;
		cin >> m;
		if (m == 0)
		{
			cout << 2 << endl;
		}
		if (m == 1)
		{
			cout << 4 << endl;
		}
		if (m == 2)
		{
			cout << 1 << endl; 
		}
		if (m == 3)
		{
			cout << 8 << endl;
		}
		if (4<=m&&m<=9)
		{
			cout << 8*(m-2) << endl; 
		}
		if (m == 10)
		{
			cout << 4 << endl;
		}
		if (m == 11)
		{
			cout << 62 << endl;
		}
		if (m == 12)
		{
			cout << 72 << endl;
		}
		if (m == 20)
		{
			cout << 1 << endl;
		}
		if (m == 21)
		{
			cout << 3 << endl;
		}
		if (m == 22)
		{
			cout << 80 << endl;
		}
		if (13 <= m && m <= 31&&m!=20&&m!=21&&m!=22)
		{
			cout << 8 * (m - 2)-1 << endl; 
		}
		if (32 <= m && m <= 99)
		{
			int i = 0, j = 0;
			i = m / 10;
			j = m % 10;
			int so1 = 0, so2 = 0, so3 = 0, so4 = 0;
			
			if (j==0||j==1)
			{
				if (j == 0)
				{
					for (int nian = 2021; nian < 2020 + i; nian++)
					{
						if (runnian(nian))
							so1 = so1 + 8 * 366;
						else
							so1 = so1 + 8 * 365;
					}
					so1 = so1 - 16 + 4;
				}
				else
				{
					for (int nian = 2021; nian < 2020 + i; nian++)
					{
						if (runnian(nian))
							so1 = so1 + 8 * 366;
						else
							so1 = so1 + 8 * 365;
					}
					if (runnian(2020 + i))
						so1 = so1 - 16 + (366 - 92) * 8 + 4;
					else
						so1 = so1 - 16 + (365 - 92) * 8 + 4;
				}
			}

			if (j >= 0 && j <= 3)
			{
				if (j == 0)
				{
					for (int yue = 1; yue < i; yue++)
					{
						so2 = so2 + 8 * ping2021[yue];
					}
					so2 = so2 + 6;
				}
				else
				{
					for (int yue = 1; yue < i; yue++)
					{
						so2 = so2 + 8 * ping2021[yue];
					}
					so2 = so2 + (j*10-1)*8+6;
				}
			}

			if (j == 2)
			{
				so3 = 8 * (i - 2);
			}

			for (int nian = 2021; nian < 2000 + m; nian++)
			{
				if (runnian(nian))
					so4 = so4 + 8 * 366;
				else
					so4 = so4 + 8 * 365;
			}
			so4 = so4 - 16+3;

			if (so1 == 0)
				so1 = 1 << 30;
			if (so2 == 0)
				so2 = 1 << 30;
			if (so3 == 0)
				so3 = 1 << 30;
			if (so4 == 0)
				so4 = 1 << 30;



			int min = so1;
			if (so2 < min)
				min = so2;
			if (so3 < min)
				min = so3;
			if (so4 < min)
				min = so4;
			cout << min << endl;
		}
		if (m == 100)
		{
			cout << 8 * (365 - 92 - 2) + 5 << endl;
		}

		n--;
	}


	return 0;
}