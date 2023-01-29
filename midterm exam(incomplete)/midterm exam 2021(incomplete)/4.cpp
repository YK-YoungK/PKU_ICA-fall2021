/*
4. 节约网费
题目描述
有一款游戏，它按照玩家的游戏时长分 n+1 段收费递增：
1. 玩家游戏的前 a[1] 个小时，收费为每小时 b[1] 元。
2. 从第 a[1]+1 个小时开始到第 a[2] 个小时，收费为每小时 b[2] 元 。
...
3. 从第 a[n-1]+1 个小时开始到第 a[n] 个小时，收费为每小时 b[n] 元。
4. 从第 a[n]+1 个小时开始，收费为每小时 b[n+1] 元。
其中，1 <= a[1] < a[2] < ... < a[n] <= 1000000, 1 <= b[1] < b[2] < ... < b[n+1] <= 1000。

小明打算玩 h 小时个游戏，但是他觉得游戏时长太多的时候，收费太贵，因此他打算开 k 个账号从而减少费用。

具体来说，小明打算选择 k 个非负整数 c[1] ... c[k] 满足 c[1] + c[2] + ... + c[k] = h，并在第 i 个账号上玩 c[i] 个小时。

小明希望你能帮他决定一下 c[1] ... c[k]，使得他花的钱最少。

关于输入
第一行输入两个整数 n,k,h (1<=n,k<=1000,1<=h<=1000000)。

第二行输入 n 个整数，表示 a[i]。第三行输入 n+1 个整数，表示 b[i]。

关于输出
输出一行一个整数，表示最少的花费。

例子输入
1 3 10
1
1 2
例子输出
17
提示信息
*/
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
	int n = 0, k = 0,h = 0;
	cin >> n >> k >> h;
	int timelimit[1500] = { 0 }, fee[1500] = { 0 };
	for (int i = 1; i <= n; i++)
	{
		cin >> timelimit[i];
	}
	for (int i = 0; i <= n; i++)
	{
		cin >> fee[i];
	}

	int sum = 0;
	int point = 0;
	while (h > 0)
	{
		if (point<=n-1&&h >= k * (timelimit[point + 1] - timelimit[point]))
		{
			sum = sum + k * (timelimit[point + 1] - timelimit[point]) * fee[point];
			h = h - k * (timelimit[point + 1] - timelimit[point]);
			point++;
		}
		else
		{
			sum = sum + h * fee[point];
			h = 0;
		}
	}
	cout << sum << endl;

	return 0;
}