/*
9. 1123 拨钟问题
题目描述
有9个时钟，排成一个3*3的矩阵。


现在需要用最少的移动，将9个时钟的指针都拨到12点的位置。共允许有9种不同的移动。如右表所示，每个移动会将若干个时钟的指针沿顺时针方向拨动90度。

移动 影响的时钟
1 ABDE
2 ABC
3 BCEF
4 ADG
5 BDEFH
6 CFI
7 DEGH
8 GHI
9 EFHI
(图 2)

关于输入
从标准输入设备读入9个整数，表示各时钟指针的起始位置。0=12点、1=3点、2=6点、3=9点。

关于输出
输出一个最短的移动序列，使得9个时钟的指针都指向12点。按照移动的序号大小，输出结果。

例子输入
3 3 0 
2 2 2 
2 1 2
例子输出
4 5 8 9
提示信息
1166 2814
*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;
int place[3][3] = { 0 };
int turns[9] = { 0 };//each max=3
const int num[9] = { 4,3,4,3,5,3,4,3,4 };
const int turnplace[9][5][2] = { {{0,0}, {0,1}, {1,0}, {1,1} },{{0,0}, {0,1}, {0,2}},
{{0,1}, {0,2}, {1,1}, {1,2} },{{0,0}, {1,0}, {2,0}},{{0,1}, {1,0}, {1,1},{1,2},{2,1} },
{{0,2}, {1,2}, {2,2}},{{1,0},{1,1}, {2,0},{2,1} },{{2,0}, {2,1}, {2,2}},{{1,1},{1,2}, {2,1},{2,2} }
};

int main()
{
	int fixed[3][3] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> fixed[i][j];
		}
	}

	int did[9] = { 0 };
	int sum = 0;
	int best = 1 << 30;
	int bestdid[9] = { 0 };
	for (int i = 0; i < (1 << 18); i++)
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				place[x][y] = fixed[x][y];
			}
		}
		sum = 0;
		for (int j = 0; j < 9; j++)
		{
			did[j] = (i >> 2*(8-j)) % 4;
			sum = sum + did[j];
			for (int k = 0; k < num[j]; k++)
			{
				place[turnplace[j][k][0]][turnplace[j][k][1]] = (place[turnplace[j][k][0]][turnplace[j][k][1]] + did[j]) % 4;
			}
		}
		
		//check
		int flag = 1;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (place[x][y] != 0)
				{
					flag = 0; break;
				}
			}
		}

		if (flag == 1)
		{
			if (sum < best)
			{
				best = sum;
				for (int k = 0; k < 9; k++)
				{
					bestdid[k] = did[k];
				}
			}
		}
	}

	

	int tmp = 0;
	for (int i = 0; i < 9; i++)
	{
		if (bestdid[i] != 0)
		{
			for (int j = 0; j < bestdid[i]; j++)
			{
				if (tmp < best - 1)
				{
					cout << i + 1 << " ";
					tmp++;
				}
				else
				{
					cout << i + 1 << endl;
				}
			}
		}
	}
	cout << endl;
	return 0;
}