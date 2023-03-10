/*
8. 天平
题目描述
Gigel有一个奇怪的天平，他想要使它平衡。事实上，这个东西与其他普通的天平是不同的。
它有两条重量可以忽略的臂，每条臂的长度是15。臂上有一些挂钩，Gigel想要从他拥有的G个重物中（1 <= G <= 20）挂一些上去，这些重物有着不同的重量，重量范围在1到25之间。Gigel可以把任意的重物放到任意的挂钩上，但他必须全部用完所有重物。
最终，Gigel成功地利用他在全国信息学奥赛中的经验将天平弄平衡了。现在他想知道有多少种方式可以让它平衡。
挂钩的位置和重物的重量是已知的，写一个程序来计算能使天平平衡的所有可能数目。
测试样例保证至少有一种能使之平衡的方案。

关于输入
输入由以下组成：
• 第一行包含整数C(2 <= C <= 20)和整数G(2 <= G <= 20);
• 下一行包含C个整数(这些数字也是互不相同的，按递增排序），范围在-15到15之间，代表挂钩的分配；每个数字代表在X轴上相对天平中心的位置（当没有重物在天平上时，天平沿X轴方向平衡。距离的绝对值代表挂钩与天平中心的距离，数字的符号决定挂钩在哪个臂上：负号代表在左臂，正号代表在右臂）
• 再下一行是G个互不相同的自然数，按递增排序，范围在1到25之间，代表重物的重量值。

关于输出
输出包含一个数M，代表使天平平衡的可能方案个数。

例子输入
2 4
-2 3
3 4 5 8
例子输出
2
提示信息
为了与POJ中保持一致，输出结果在可以用int表示的范围内。
使用动态规划。
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
int weight[25][16000] = { 0 };
int place[25] = { 0 };
int fama[25] = { 0 };
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int c = 0, g = 0;
	cin >> c >> g;
	for (int i = 1; i <= c; i++)
	{
		cin >> place[i];
	}
	for (int j = 1; j <= g; j++)
	{
		cin >> fama[j];
	}
	
	weight[0][7500] = 1;
	for (int i = 1; i <= g; i++)
	{
		for (int m = 0; m < 16000; m++)
		{
			for (int x = 1; x <= c; x++)
			{
				if (m + place[x] * fama[i] >= 0 && m + place[x] * fama[i] < 16000)
				{
					weight[i][m + place[x] * fama[i]] = weight[i][m + place[x] * fama[i]] + weight[i - 1][m];
				}
			}
		}
	}

	cout << weight[g][7500] << endl;
	return 0;
}