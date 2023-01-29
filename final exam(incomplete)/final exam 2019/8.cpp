/*
8. 小游戏
题目描述
   一天早上，你起床的时候想：“我编程序这么牛，为什么不能靠这个挣点银子呢？”因此你决定编写一个小游戏。
   游戏在一个分割成w * h个长方格子的矩形板上进行。如图所示，每个长方格子上可以有一张游戏卡片，也可以没有。当下面的情况满足时，我们认为两个游戏卡片之间有一条路径相连：
   路径只包含水平或者竖直的直线段。路径不能穿过别的游戏卡片。但是允许路径临时离开矩形板。
   下面是一个例子：


这里在(1, 3)和(4, 4)处的游戏卡片是可以相连的。而在 (2, 3) 和 (3, 4) 处的游戏卡是不相连的，因为连接他们的每条路径都必须要穿过别的游戏卡片。
   你现在要在小游戏里面判断是否存在一条满足题意的路径能连接给定的两个游戏卡片。
关于输入
   输入包括多组数据。一个矩形板对应一组数据。每组数据的第一行包括两个整数w和h (1 <= w, h <= 75)，分别表示矩形板的宽度和高度。下面的h行，每行包括w个字符，表示矩形板上的游戏卡片分布情况。使用‘X’表示这个地方有一个游戏卡片；使用空格表示这个地方没有游戏卡片。之后的若干行，每行包括4个整数x1, y1, x2, y2 (1 <= x1, x2 <= w, 1 <= y1, y2 <= h)，表示两个卡片在矩形板上的位置（注意：矩形板左上角的坐标是(1, 1)）。如果一行上有4个0，则表示这组测试数据的结束。测试数据保证这两个游戏卡片所处的位置是不相同的。
   如果一行上有2个0，那么表示所有的输入结束了。

关于输出
   对每一个矩形板，输出一行“Board #n:”，这里n是输入数据的编号（从1开始）。然后对于每一对需要测试的游戏卡片输出一行。这一行的开头是“Pair m: ”，这里m是测试卡片的编号（对每个矩形板，编号都从1开始）。接下来，如果可以相连，则找到连接这两个卡片的所有路径中包括线段数最少的路径，输出“k segments.”，这里k即是找到的最优路径中包括的线段的数目；如果不能相连，则输出“impossible.”。

   注意：每个矩形板之后须输出一个空行。

例子输入
5 4
XXXXX
X   X
XXX X
 XXX 
2 3 5 3
1 3 4 4
2 3 3 4
0 0 0 0
4 4
XXXX
XXXX
XXXX
XXXX
1 1 2 1
2 2 3 2
1 1 3 1
3 4 4 3
2 1 2 4
1 1 2 2
0 0 0 0
0 0
例子输出
Board #1:
Pair 1: 4 segments.
Pair 2: 3 segments.
Pair 3: impossible.

Board #2:
Pair 1: 1 segments.
Pair 2: 1 segments.
Pair 3: 3 segments.
Pair 4: 4 segments.
Pair 5: 5 segments.
Pair 6: impossible.

提示信息
*/
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
char map[100][100] = {};
int row = 0, column = 0;
int visited[100][100] = { 0 };
int best[100][100] = { 0 };//记得要初始化
int startx = 0, starty = 0, endx = 0, endy = 0;
int flag = 0;
void search(int x, int y, int fangxiang,int times)//右1下2左3上0
{
	if (x == endx && y == endy)
	{
		flag = 1;
		best[x][y] = min(best[x][y], times);
		return;
	}
	if (map[x][y] == 'X'&&(x!=startx||y!=starty))
		return;
	if (visited[x][y] == 1)
		return;
	if (times >= best[x][y])
		return;
	visited[x][y] = 1;
	best[x][y] = times;
	if (fangxiang == 1)
	{
		if (y<=column)
			search(x, y + 1, 1, times);
		if (x<=row)
			search(x + 1, y, 2, times + 1);
		if (y>=1)
			search(x, y - 1, 3, times+1);
		if (x>=1)
			search(x - 1, y, 0, times + 1);
	}
	if (fangxiang == 2)
	{
		if (y <= column)
			search(x, y + 1, 1, times+1);
		if (x <= row)
			search(x + 1, y, 2, times);
		if (y >= 1)
			search(x, y - 1, 3, times + 1);
		if (x >= 1)
			search(x - 1, y, 0, times + 1);
	}
	if (fangxiang == 3)
	{
		if (y <= column)
			search(x, y + 1, 1, times+1);
		if (x <= row)
			search(x + 1, y, 2, times + 1);
		if (y >= 1)
			search(x, y - 1, 3, times);
		if (x >= 1)
			search(x - 1, y, 0, times + 1);
	}
	if (fangxiang == 0)
	{
		if (y <= column)
			search(x, y + 1, 1, times+1);
		if (x <= row)
			search(x + 1, y, 2, times + 1);
		if (y >= 1)
			search(x, y - 1, 3, times + 1);
		if (x >= 1)
			search(x - 1, y, 0, times);
	}
	visited[x][y] = 0;
	return;
}
int main()
{
	for (int num=1;;num++)
	{
		memset(map, '\0', sizeof(map));
		memset(visited, 0, sizeof(visited));
		flag = 0;
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				best[i][j] = 1 << 30;
			}
		}

		cin >> column >> row;
		if (column == 0 && row == 0)
			break;
		cin.get();
		for (int i = 1; i <= row; i++)
		{
			for (int j = 1; j <= column; j++)
			{
				map[i][j] = cin.get();
			}
			cin.get();
		}
		cout << "Board #" << num << ":" << endl;

		for (int times=1;;times++)
		{
			cin >> starty >> startx >> endy >> endx;
			flag = 0;
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < 100; j++)
				{
					best[i][j] = 1 << 30;
				}
			}
			if (startx == 0 && starty == 0 && endx == 0 && endy == 0)
				break;
			search(startx, starty+1, 1, 1);
			search(startx+1, starty, 2, 1);
			search(startx, starty-1, 3, 1);
			search(startx-1, starty, 0, 1);
			if (flag == 1)
				cout << "Pair " << times << ": " << best[endx][endy] << " segments." << endl;
			else
				cout << "Pair " << times << ": impossible."<< endl;
		}
		cout << endl;
	}
	return 0;
}