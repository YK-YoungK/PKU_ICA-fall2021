/*
2. 病人分类
题目描述
就医时对不同症状的病人分类是非常重要的，这样可以为病人找最专业的医生来就诊。目前一共有n个病人，编号是1~n，最开始每个病人的症状未被分类。每个病人属于一个单独的集合。
现在要进行m个操作，操作共有两种：

“M a b”，由于症状相同，将编号为a和b的两个病人所在集合合并，如果两个病人已经在同一个集合中，则忽略这个操作；

“Q a b”，询问编号为a和b的两个病人是否在同一个集合中；

关于输入
第一行输入整数n和m，1≤n,m≤100

接下来m行，每行包含一个操作指令，指令为“M a b”或“Q a b”中的一种。

关于输出
对于每个询问指令”Q a b”，都要输出一个结果，如果a和b在同一集合内，则输出“Yes”，否则输出“No”。每个结果占一行。

例子输入
4 5
M 1 2
M 3 4
Q 1 2
Q 1 3
Q 3 4
例子输出
Yes
No
Yes
提示信息
*/
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
	int person = 0, m = 0;
	cin >> person >> m;
	int fenzu[150][150] = { 0 };
	int num[150] = { 0 };
	for (int i = 1; i <= person; i++)
	{
		fenzu[i][i] = 1;
		num[i] = 1;
	}
	char ch;
	int a = 0, b = 0;
	while (m > 0)
	{
		cin >> ch >> a >> b;
		if (ch == 'M')
		{
			for (int i = 1; i <= person; i++)
			{
				if (fenzu[a][i] == 1)
					fenzu[b][i] = 1;
				if (fenzu[b][i] == 1)
					fenzu[a][i] = 1;
			}
		}
		else
		{
			if (fenzu[a][b] == 1|| fenzu[b][a] == 1)
				cout << "Yes" << endl;
			else
				cout << "No" << endl;
		}
		m--;
	}

	return 0;
}