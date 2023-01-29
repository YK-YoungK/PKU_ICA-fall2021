/*
3. 特殊素数序列
题目描述
给丁一对正整数[p,q]，其中，p小于q 且q不大于100000
请按从小到大的顺序输出p和q之间的素数序列，以逗号间隔。输出的素数 a 需满足如下二个条件：
（1）p<=a<=q；
（2）a 的逆序 b 也必须是素数，且 a<=b,同时，p<=b<=q
例如，p=2, q=50,则输出：

2,3,5,7,11,13

注意：13的逆序31也是素数，且都在[2,50]的范围内，13小于31，故只输出 13.

如果没有满足条件的序列，则输出 NULL

关于输入
两个正整数，由逗号间隔，分别表示 p 和 q

关于输出
输出符合条件的素数序列，其间以逗号间隔；如果没有满足条件的序列，则输出 NULL

例子输入
10,50
例子输出
11,13
提示信息
*/
#include <iostream>
using namespace std;
int swap(int t)
{
	int result = 0;
	int num[10] = {0};
	int weishu = 0;
	while (t > 0)
	{
		num[weishu] = t % 10;
		t = t / 10;
		weishu++;
	}
	for (int i = 0; i<weishu; i++)
	{
		result = result * 10 + num[i];
	}
	return result;
}
int prime(int t)//判断是否为素数
{
	if (t == 1)
		return 0;
	if (t == 2 || t == 3)
		return 1;
	for (int i = 2; i * i <= t; i++)
	{
		if (t % i == 0)
			return 0;
	}
	return 1;
}
int main()
{
	int p = 0, q = 0;
	char ch;
	cin >> p >> ch >> q;
	int num = 0;
	for (int i = p; i <= q; i++)
	{
		if (prime(i) == 1)
		{
			int change = swap(i);
			if (prime(change) == 1 && change >= p && change <= q && change >= i)
			{
				if (num == 0)
				{
					cout << i;
					num = 1;
				}
				else
					cout << "," << i;
			}
		}
	}
	if (num == 0)
		cout << "NULL";
	return 0;
}