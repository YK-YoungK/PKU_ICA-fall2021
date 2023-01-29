/*
6. 装载问题
题目描述
有一批共 n 个集装箱要装上 2 艘载重量分别为 c1和 c2的轮船，其中集装箱 i 的重量为 wi，且Σwi <= c1 + c2. 装载问题要求确定，是否有一个合理的装在方案可将这 n 个集装箱装上这 2 艘轮船。如果有，找出最优装载方案。

关于输入
输入要输入
1、集装箱数量 类型整型
2、集装箱重量数组 类型整型数组
3、两艘轮船的载重量 类型整型数组
输入格式如：
5
67 34 2 69 24
78 158

关于输出
如果能装载的话输出格式如下：
ok,can load it
a way is:
the first trip load:2 69
the second trip load:67 34 24
如果不能装载的话输出如下：
can't find a way to Loading

例子输入
5
67 34 2 69 24
78 158
例子输出
ok,can load it
a way is:
the first trip load:2 69
the second trip load:67 34 24
提示信息
因为算法的复杂度为 O(2^n)，所以建议在测试时不要用 n 太大的数据。
最优装载问题采用算法：尽量将第一艘轮船装满，然后将剩余的集装箱装到第二艘轮船上。
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
int best = 0;
int n = 0;
int weight[100] = { 0 };
int bestchoose[100] = { 0 };
int choose[100] = { 0 };
int c1 = 0, c2 = 0;
void search(int start,int now)
{
	if (start == n)
	{
		if (now > best)
		{
			best = now;
			for (int i = 0; i < n; i++)
			{
				bestchoose[i] = choose[i];
			}
		}
		return;
	}

	choose[start] = 0;
	search(start + 1, now);

	if (now + weight[start] <= c1)
	{
		choose[start] = 1;
		search(start + 1, now + weight[start]);
	}

	
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


	
	cin >> n;
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> weight[i];
		sum = sum + weight[i];
	}

	cin >> c1 >> c2;

	//sort(weight, weight + n);


	/*
	int solution[1000][100] = { 0 };
	for (int i = weight[0]; i <= c1; i++)
	{
		solution[i][0] = weight[0];
	}
	for (int j = 1; j < n; j++)
	{
		for (int i = 0; i <= c1; i++)
		{
			if (i >= weight[j])
				solution[i][j] = max(solution[i][j - 1], solution[i - weight[j]][j - 1] + weight[j]);
			else
				solution[i][j] = solution[i][j - 1];
		}
	}
	*/
	
	search(0, 0);



	if (best + c2 >= sum)
	{
		cout << "ok,can load it" << endl;
		cout << "a way is:" << endl;
		cout << "the first trip load:";
		int tmp = 0;
		for (int i = 0; i < n; i++)
		{
			if (bestchoose[i] == 1)
				tmp++;
		}

		int tmpcount = 0;
		for (int i = 0; i < n; i++)
		{
			if (bestchoose[i] == 1&&tmpcount<tmp-1)
			{
				cout << weight[i] << " ";
				tmpcount++;
			}
			else if (bestchoose[i] == 1 && tmpcount == tmp-1)
			{
				cout << weight[i]<<endl;
			}
		}
		cout << "the second trip load:";
		tmpcount = 0;
		for (int i = 0; i < n; i++)
		{
			if (bestchoose[i] == 0 && tmpcount < n-tmp-1)
			{
				cout << weight[i] << " ";
				tmpcount++;
			}
			else if (bestchoose[i] == 0 && tmpcount == n - tmp-1)
			{
				cout << weight[i]<<endl;
			}
		}
	}
	else
	{
		cout << "can't find a way to Loading" << endl;
	}
	return 0;
}