/*
5. 有趣的二进制
题目描述
最近北京大学药学院的小晨在计概课上学习到二进制之后对其产生了浓厚的兴趣，在每次操作仅能移动相邻的0和1的前提下，她想知道把一个二进制数转换成另一个二进制数的最小操作数。

关于输入
输入共三行：

第一行为一个整数n (0 < n <= 200)，代表二进制数的位数

第二行为第一个二进制数的每一位

第三行为第二个二进制数的每一位

关于输出
输出将第一个二进制数转换为第二个二进制数的最少操作数，如果答案不存在，则输出-1

例子输入
7
1 1 0 1 0 0 1
0 1 1 0 0 1 1
例子输出
4
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	int n = 0;
	cin >> n;
	int num[2][250] = { 0 };
	int count1 = 0, count2 = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> num[0][i];
		if (num[0][i] == 1)
			count1++;
	}
	for (int i = 0; i < n; i++)
	{
		cin >> num[1][i];
		if (num[1][i] == 1)
			count2++;
	}

	if (count1 != count2)
		cout << "-1" << endl;
	else
	{
		int count = 0;
		int place[2][250] = { 0 };
		int place1 = 0, place2 = 0;
		for (int i = 0; i < n; i++)
		{
			if (num[0][i] == 1)
			{
				place[0][place1] = i;
				place1++;
			}
			if (num[1][i] == 1)
			{
				place[1][place2] = i;
				place2++;
			}
		}

		for (int i = 0; i < count1; i++)
		{
			count = count + abs(place[0][i] - place[1][i]);
		}
		cout << count << endl;
	}
	
	return 0;
}