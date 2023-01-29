/*
1. 购买纪念品
题目描述
北京大学邀请了一些专家，现在交给你一个任务，到纪念品商店里购买纪念品。已知一份纪念品的价格是 1 元 9 角，而班主任给你的钱是 a 元 b 角，问，你最多能买多少纪念品呢？

关于输入
输入格式：输入只有一行两个整数，分别表示 a 和 b，空格间隔。

关于输出
输出格式：输出一行一个整数，表示你最多能买多少个纪念品。

例子输入
10 3
例子输出
5
提示信息
说明/提示
对于全部的测试点，保证 0 <= a <= 10000 , 0 <= b <= 9
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
	
	int a = 0, b = 0;
	cin >> a >> b;
	double c = 0;
	c = a + 0.1 * b;
	int result = 0;
	result = c / 1.9;
	cout << result << endl;

	return 0;
}