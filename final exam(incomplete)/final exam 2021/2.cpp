/*
2. 发水果
题目描述
中午是幼儿园水果时间，老师会给每个小朋友发水果。教室为一个矩形区域，共有N 排，每排M个工位。老师通常按照逆时针方向螺旋发水果。已知每个座位有一个数字，表示该小朋友的学号，每个学号各不相同。已知老师从（0, 0）位置开始，按照逆时针螺旋的顺序发水果，请输出收到水果的小朋友的学号序列。

关于输入
第一行 两个数， 数组行列 N，M
接下来 N 行，每行 M 个正整数，表示每个位置的员工工号
1 ≤ N ≤ 15
1 ≤ M ≤ 15

关于输出
发放水果学号序列

例子输入
3 3
1 2 3 
4 5 6 
7 8 9
例子输出
1 4 7 8 9 6 3 2 5
提示信息
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n = 0, m = 0;
	cin >> n >> m;
	int num[15][15] = { 0 };
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cin >> num[i][j];
	}
	int visited[15][15] = { 0 };

	int fangxiang = 0;//右0下1左2上3
	fangxiang = 1;
	int placex = 0, placey = 0;
	cout << num[0][0];
	visited[0][0] = 1;

	for (int i = 1; i < m * n; i++)
	{
		if (fangxiang == 0)
		{
			if (placey == m - 1 || visited[placex][placey + 1] == 1)
			{
				fangxiang = 3;
				placex--;
			}
			else
			{
				placey++;
			}
		}
		else if (fangxiang == 1)
		{
			if (placex == n - 1 || visited[placex + 1][placey] == 1)
			{
				fangxiang = 0;
				placey++;
			}
			else
			{
				placex++;
			}
		}
		else if (fangxiang == 2)
		{
			if (placey == 0 || visited[placex][placey - 1] == 1)
			{
				fangxiang = 1;
				placex++;
			}
			else
			{
				placey--;
			}
		}
		else if (fangxiang == 3)
		{
			if (placex == 0 || visited[placex - 1][placey] == 1)
			{
				fangxiang = 2;
				placey--;
			}
			else
			{
				placex--;
			}
		}
		
		cout << " "<<num[placex][placey];
		visited[placex][placey] = 1;

	}


	return 0;
}