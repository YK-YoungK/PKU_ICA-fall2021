/*
7. 过河问题
题目描述
n个人想要过一条河,河上只有一条小船,这条船只能容纳两个人,因此这n个人想要全部过河的话就必须来回很多次.每个人划船的速度有所不同,两个人一起的时候船的速度是划得较慢的人的速度.请你找出一种策略使得他们在尽可能短的时间内过河.

关于输入
第一行包括一个正整数t,表示有t组数据.
每组数据两行,第一行是人数n(n<=1000),第二行是n个人各自过河所需的时间(不大于100).

关于输出
输出最短时间

例子输入
1
4
1 2 5 10
例子输出
17
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	int t = 0;
	cin >> t;
	while (t > 0)
	{
		int n = 0;
		cin >> n;
		int time[1050] = { 0 };
		for (int i = 0; i < n; i++)
		{
			cin >> time[i];
		}

		//排序
		int tmp = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (time[i] > time[j])
				{
					tmp = time[i];
					time[i] = time[j];
					time[j] = tmp;
				}
			}
		}

		//计算总时间
		int sum = 0;
		if (n % 2 == 0)
		{
			for (int i = n-1; i > 1; i=i-2)
			{
				if (time[1] + time[0] + time[i] + time[1] > time[i] + time[i - 1] + 2 * time[0])
					sum = sum + time[i] + time[i - 1] + 2 * time[0];
				else
					sum = sum + time[1] + time[0] + time[i] + time[1];
			}
			sum = sum + time[1];
		}
		else
		{
			for (int i = n-1; i > 2; i = i - 2)
			{
				if (time[1] + time[0] + time[i] + time[1] > time[i] + time[i - 1] + 2 * time[0])
					sum = sum + time[i] + time[i - 1] + 2 * time[0];
				else
					sum = sum + time[1] + time[0] + time[i] + time[1];
			}
			sum = sum + time[0]+time[1]+time[2];
		}

		cout << sum << endl;
		t--;
	}
	return 0;
}