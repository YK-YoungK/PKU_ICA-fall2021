/*
7. 对角遍历
题目描述
阿福最近在研究矩阵的遍历。给定一个大小为4nx4n的方阵，现在需要将序号0-4nx4n-1依次放入到方阵中。放置方式具体如下：
首先，将4nx4n分成16个4n-1x4n-1的子块，然后按照对角遍历的方式（如下图所示）遍历各个子块；对于每个子块继续划分成16个更小的子块，并按照如下图所示的方式遍历各个子块，..., 以此类推，并将遍历的顺序号依次填入各个1x1方块中。

现在给定非负整数n，一个1x1方块的行号x和列号y,其中0<=x,y<4n,请求出该块遍历的序号。输入保证1<=n<=10。

关于输入
包含多行，每行三个非负整数n,x,y,中间用空格隔开
当n为0时，表示输入结束,该组输入不用处理

关于输出
输出包括多行，每行一个整数，表示输入块按照上述遍历方式得到的序号。

例子输入
2 3 3
4 4 4
5 12 9
0 1 2
例子输出
15
64
210
提示信息
*/
// Submitted by 'Programming Grid' VS Code Extension

#include <iostream>
#include <cmath>
using namespace std;
static int number[5][5] = { {0,2,5,9},{1,4,8,12},{3,7,11,14},{6,10,13,15} };
int minumber[20] = { 0 };
int place(int n, int x, int y)
{
	int result = number[x / minumber[n]][y / minumber[n]];
	if (n == 1)
		return result;
	return result * minumber[n]* minumber[n]  + place(n - 1, x % minumber[n], y % minumber[n]);
}
int main()
{
	int n = 0, x = 0, y = 0;
	minumber[1] = 1;
	for (int i = 2; i <= 12; i++)
	{
		minumber[i] = 4 * minumber[i - 1];
	}
	while (1)
	{
		cin >> n >> x >> y;
		if (n == 0)
			break;
		cout << place(n, x, y) << endl;
	}
	return 0;
}