/*
3. 最小外包矩形
题目描述
最小外包矩形是图形学中一个重要的概念，其定义是能够包围几何对象（可以视为一组点的集合），且平行于x,y轴的最小外接矩形。
想要生成最小外包矩形，只需要统计组成该几何对象所有点的x、y坐标的最大值和最小值即可。最小外包矩形左下角的点x坐标等于所有点的x坐标的最小值，y坐标等于所有点的y坐标的最小值，同样的，右上角的点x坐标等于所有点的x坐标的最大值，y坐标等于所有点的y坐标的最大值。
特别地，如果几何对象为一个点，最小外包矩形变成一个点，可以用4个位置一样的点表示，如果为水平/垂直线段，最小外包矩形变成一条线段，用两对相等的点表示。
请你根据输入的点的信息输出最小外包矩形的信息。

关于输入
第一行为整数，表示所有的点个数。
每一行包含3个整数，从左到右分别是点所属于的几何对象的ID、点的x坐标、点的y坐标。

关于输出
输出的结果每行按照几何体的ID从小到大排序，每一行有5个，从左到右依次是：
几何体ID、左下角点x坐标，左下角点y坐标、右上角点x坐标、右上角点y坐标。

例子输入
10
2 36 191
3 289 107
1 943 265
4 447 806
1 730 371
1 7 102
4 549 630
4 85 955
2 841 967
2 932 309
例子输出
1 7 102 943 371
2 36 191 932 967
3 289 107 289 107
4 85 630 549 955
提示信息
几何体的ID并不是按照顺序输入的。
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

	int n = 0;
	cin >> n;
	int place[100][4] = { 0 };
	int tmp = 0;
	for (int i = 0; i < 100; i++)
	{
		place[i][0] = 1 << 30;
		place[i][1] = 1 << 30;
		place[i][2] = -1 << 30;
		place[i][3] = -1 << 30;
	}

	int x = 0, y = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		cin >> x >> y;
		place[tmp][0] = min(place[tmp][0], x);
		place[tmp][1] = min(place[tmp][1], y);
		place[tmp][2] = max(place[tmp][2], x);
		place[tmp][3] = max(place[tmp][3], y);
	}
	for (int i = 0; i < 100; i++)
	{
		if (place[i][0] != 1 << 30)
		{
			cout << i << " " << place[i][0] << " " << place[i][1] << " " << place[i][2] << " " << place[i][3] << endl;
		}
	}


	return 0;
}