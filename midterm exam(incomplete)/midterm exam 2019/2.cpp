/*
2. 计数问题
题目描述
试计算在区间 1 到 n 的所有整数中，数字 x(0 ≤ x ≤ 9)共出现了多少次？例如，在 1 到 11 中，即在 1、2、3、4、5、6、7、8、9、10、11 中，数字 1 出现了 4 次，数字2出现了1次。

关于输入
输入共 1 行，包含 2 个整数 n、x，之间用一个空格隔开。

关于输出
输出共 1 行，包含一个整数，表示 x 出现的次数。

例子输入
11 1
例子输出
4
提示信息
对于所有的数据，1≤ n ≤ 10000，0≤ x ≤ 9。
*/
#include <iostream>
using namespace std;
int main()
{
	int n = 0, x = 0;
	cin >> n >> x;
	int count = 0;
	for (int i = 1; i <= n; i++)
	{
		int tmp = i;
		while (tmp > 0)
		{
			if (x == tmp % 10)
				count++;
			tmp = tmp / 10;
		}
	}
	cout << count << endl;
	return 0;
}
