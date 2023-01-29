/*
6. 自然数列的序列化
题目描述
把自然数的序列（0 1 2 3 4 5 6 7 8 9 10 11 12 ...）按照如下的方式序列化到一个数组中:

每个数字独占用一个数组元素的位置，例如对于上述序列可以放到如下的数组中：a[0]-a[9]分别存放0 - 9，a[10]存放1，a[11]存放0，a[12]存放1，a[13]存放1，a[14]存放1，a[15]存放2，以此类推。

给定一个整数n（0 <= n <= 20000），请你求出下标为n的元素a[n]中存放的数字是什么？

请你编写一个程序，对于给出的多个n，分别求出其对应的数组元素a[n]中存放的数字。

关于输入
输入多行，每行一个整数，对应上述题干中所述的一个 n（0 <= n <= 20000）如：
1
5
13
19

关于输出
输出多行，每行一个整数，对应a[n]中所存储的整数，如：
1
5
1
4

例子输入
例子输出
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	int num[50000] = { 0 };
	int point = 1;
	for (int i = 1; i <= 9; i++)
	{
		num[point] = i;
		point++;
	}
	for (int i = 10; i <= 99; i++)
	{
		num[point] = i / 10;
		point++;
		num[point] = i % 10;
		point++;
	}
	for (int i = 100; i <= 999; i++)
	{
		num[point] = i / 100;
		point++;
		num[point] = (i / 10) % 10;
		point++;
		num[point] = i % 10;
		point++;
	}
	for (int i = 1000; i <= 9999; i++)
	{
		num[point] = i / 1000;
		point++;
		num[point] = (i / 100) % 10;
		point++;
		num[point] = (i / 10) % 10;
		point++;
		num[point] = i % 10;
		point++;
	}
	int n = 0;
	while (1)
	{
		cin >> n;
		if (cin.fail() == 1)
			break;
		cout << num[n] << endl;
	}
}