/*
2. 求到最大最小值距离差最小的数
题目描述
给定一组正整数，其中的最大值和最小值分别为max和min，其中的一个数x到max和min的距离差D定义为

abs(abs(x-max) - abs(x-min))。

其中，abs()表示求一个数的绝对值

关于输入
输入第一行为整数n，剩余n行每行一个正整数。(n<=10000)

关于输出
输出仅一行，它的值为使得距离差D最小的x。

例子输入
5
3
1
7
5
9
例子输出
5
提示信息
函数abs()定义在stdlib.h中。
*/
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int n= 0;
	cin >> n;
	int num[10005] = { 0 };
	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
	}
	int maxium = num[0], minium = num[0];
	for (int i = 0; i < n; i++)
	{
		maxium = max(num[i], maxium);
		minium = min(num[i], minium);
	}
	int result = abs(abs(num[0]-maxium)-abs(num[0]-minium));
	int place = num[0];
	for (int i = 0; i < n; i++)
	{
		if (abs(abs(num[i] - maxium) - abs(num[i] - minium)) < result)
		{
			result = abs(abs(num[i] - maxium) - abs(num[i] - minium));
			place = num[i];
		}
	}
	cout << place << endl;
	return 0;
}