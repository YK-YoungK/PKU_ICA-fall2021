/*
7. 魔王军队
题目描述
魔王需要带领他的军队从A城堡进攻B城堡。为了追踪他的兵力，他分发了很多观察之石。每颗观察之石的最大有效观察半径R个单位，并且必须被一个士兵携带（观察之石不能处于没有士兵的空中）。帮助魔王计算出为了追踪所有部队所需要的观察之石的最小数量。

关于输入
输入包含多个实例。每个测试实例第一行为两个整数：R，n。R（0<=R<=1000）是观察之石的有效半径，n（1<=n<=1000）为魔王军队的士兵数量。接下来的1行包含n个整数，分别是每个士兵的位置x_1,x_2,…,x_n（0<=x_i<=50000）。如果某个实例输入的R和n 均为-1，则结束。

关于输出
针对每个测试实例，输出一行整数表示所需的最小数量。

例子输入
0 3
10 20 20
10 7
70 30 1 7 15 20 50
-1 -1
例子输出
2
4
提示信息
对于上述的两组数据（输入/输出），在一组中，魔王可以将观察之石放在位置10和20上，注意距离为0的观察之石能够覆盖位置在20的两个士兵。
在第二组中，魔王可以将观察之石放在位置7（覆盖了位置1，7，15的士兵），20（覆盖了位置20，30的士兵），50，70。注意，观察之石不能放在60的空中来同时覆盖位置50，70的士兵。
*/
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
int main()
{
	while (1)
	{
		int r = 0, n = 0;
		cin >> r >> n;
		if (r == -1 && n == -1)
			break;
		int place[1050] = { 0 };
		for (int i = 0; i < n; i++)
		{
			cin >> place[i];
		}
		sort(place, place + n);
		
		int num = 0;
		int point = n - 1;
		while (point>=0)
		{
			int now = point;
			for (now = point - 1; now >= 0; now--)
			{
				if (place[point] - place[now] > r)
					break;
			}
			now++;
			num++;
			int tmp = now;
			for (tmp = now; tmp >= 0; tmp--)
			{
				if (place[now] - place[tmp] > r)
					break;
			}
			point = tmp;
		}
		cout << num << endl;
	}


	return 0;
}