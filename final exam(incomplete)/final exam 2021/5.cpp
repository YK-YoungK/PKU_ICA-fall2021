/*
5. 城堡问题
题目描述

(图 1)
   #  = Wall
   |  = No wall
   -  = No wall


图1是一个城堡的地形图。请你编写一个程序，计算城堡一共有多少房间，最大的房间有多大。城堡被分割成m*n(m≤50，n≤50)个方块，每个方块可以有0~4面墙。
关于输入
程序从标准输入设备读入数据。第一行是两个整数，分别是南北向、东西向的方块数。在接下来的输入行里，每个方块用一个数字(0≤p≤50)描述。用一个数字表示方块周围的墙，1表示西墙，2表示北墙，4表示东墙，8表示南墙。每个方块用代表其周围墙的数字之和表示。城堡的内墙被计算两次，方块(1,1)的南墙同时也是方块(2,1)的北墙。输入的数据保证城堡至少有两个房间。

关于输出
输出分为两行。城堡的房间数、城堡中最大房间所包括的方块数。结果显示在标准输出设备上。

例子输入
4 7 
11 6 11 6 3 10 6 
7 9 6 13 5 15 5 
1 10 12 7 13 7 5 
13 11 10 8 10 12 13 
例子输出
5
9
提示信息
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
int room[60][60] = { 0 };
int visited[60][60] = { 0 };
int num = 0;
int best = 0;
int nowspace = 0;
void search(int x,int y)
{
	visited[x][y] = 1;
	nowspace++;
	if (nowspace > best)
		best = nowspace;
	if (room[x][y] % 2 == 0 && visited[x][y - 1] == 0)
	{
		search(x, y - 1);
	}
	if ((room[x][y]>>1) % 2 == 0 && visited[x-1][y] == 0)
	{
		search(x-1, y);
	}
	if ((room[x][y] >> 2) % 2 == 0 && visited[x][y + 1] == 0)
	{
		search(x, y + 1);
	}
	if ((room[x][y] >> 3) % 2 == 0 && visited[x + 1][y] == 0)
	{
		search(x + 1, y);
	}
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int x = 0, y = 0;
	cin >> x >> y;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
			cin >> room[i][j];
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (visited[i][j] == 0)
			{
				nowspace = 0;
				num++;
				search(i, j);
			}
		}
	}
	cout << num << endl;
	cout << best << endl;
	return 0;
}