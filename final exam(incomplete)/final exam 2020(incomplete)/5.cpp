/*
5. 拼装模型
题目描述
Dzx从日本回来了，并为TN准备了礼物----一个恐龙模型。TN想把它尽快拼好，但是由于模型很庞大，TN又实在比较懒，所以他希望你为他寻找一个最节省时间的拼装方案。

模型是由N个零件组成的，每次TN可以选取两个零件拼装在一起来组成一个新的零件，直到得到完整的模型。由于零件的复杂程度不同，TN每次拼装所需要的时间也是不同的，对于两个零件A和B，假设他们的复杂程度分别为a和b，则TN要将这两个零件拼装在一起所需要的时间为a+b，而这由两个零件所组成的新零件的复杂程度为a+b。

现在TN已经统计出了每个零件的复杂程度，你能告诉他最快的拼装方法需要多少时间么？

关于输入
Line 1： N (1 <= N <= 10000)，零件数目
Line 2： N Integers，表示每个零件的复杂程度

关于输出
最快的拼装方案所需要的时间

例子输入
3
1 2 9
例子输出
15
提示信息
每次都选择当前最小的两个零件。
*/
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	int n = 0;
	cin >> n;
	int time[10005] = { 0 };
	for (int i = 0; i < n; i++)
	{
		cin >> time[i];
	}

	int result = 0;
	for (int i = 0; i < n-1; i++)
	{
		sort(time, time + n);
		time[i + 1] = time[i] + time[i + 1];
		time[i] = -1;
		result = result + time[i + 1];
	}
	cout << result << endl;
	return 0;
}