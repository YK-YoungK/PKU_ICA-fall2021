/*
3. 换酒问题
题目描述
小区便利店正在促销，用 a 个空酒瓶可以兑换一瓶新酒。你购入了 b 瓶酒。

如果喝掉了酒瓶中的酒，那么酒瓶就会变成空的。

请你计算最多能喝到多少瓶酒。

关于输入
用空格分开的两个整数，分别为a和b。

1 < a <= 1000000000,
0 <= b <= 1000000000.

关于输出
能喝到多少瓶酒。

例子输入
3 9
例子输出
13
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	long long a = 0, b = 0, sum = 0;
	cin >> a >> b;
	long long rest = 0;//当前剩余的空瓶子数
	long long drink = b;//当前剩余的满的
	long long tmp = 0;
	while (1)
	{
		sum = sum + drink;
		rest = rest + drink;
		if (rest < a)
			break;
		tmp = rest % a;
		drink = (rest - tmp) / a;
		rest = tmp;
	}
	cout << sum << endl;
	return 0;
}