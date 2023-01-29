/*
8. 循环数
题目描述
当一个N位的整数X满足下列条件时，称其为循环数：X与任意一个整数1≤Y ≤ N相乘时，都将产生一个X的“循环”。即：分别将这两个整数的第1位数字与最后1位数字连在一起，可以得到一个相同的数字循环；当然两个整数在该数字循环中的起始位置不同。例如，142857是一个循环数
142857 *1 = 142857
142857 *2 = 285714
142857 *3 = 428571
142857 *4 = 571428
142857 *5 = 714285
142857 *6 = 857142

关于输入
写一个程序判断一个整数是否是循环数。输入文件是一个整数序列，每个整数长度为2~60。注意：每个整数前面的零被看作是该整数的一部分，在计算N时要统计。例如“01”是一个2位的整数，而“1”是一个1位的整数。

关于输出
对每个输入整数，输出一行，说明该整数是否是循环数。

例子输入
142857
142856
142858
01
0588235294117647
例子输出
142857 is cyclic
142856 is not cyclic
142858 is not cyclic
01 is not cyclic
0588235294117647 is cyclic
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	while (1)
	{
		char number[70] = {};
		cin.getline(number, 70);
		if (cin.fail() == 1)
			break;
		int num[70] = { 0 };
		int n = 0;
		for (n = 0; number[n] != '\0'; n++)
		{
			num[n] = number[n] - '0';
		}

		int multi[70][70] = { 0 };
		for (int i = 1; i <= n; i++)
		{
			//计算乘法
			int tmp[70] = { 0 };
			for (int j = 0; j < n; j++)
			{
				tmp[j] = num[j] * i;
			}
			for (int j = n - 1; j >= 1; j--)
			{
				multi[i][j] = tmp[j] % 10;
				tmp[j - 1] = tmp[j - 1] + tmp[j] / 10;
			}
			multi[i][0] = tmp[0];//不管大不大于10，大于10后面比较直接否定
		}

		//构建循环结构
		int cycle[70][70] = { 0 };
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cycle[i][j] = num[(j + i) % n];
			}
		}

		//尝试一一配对
		int flag = 1;
		for (int i = 1; i <= n; i++)
		{
			int flagi = 0;
			for (int j = 1; j <= n; j++)
			{
				int flagij = 1;
				for (int k = 0; k < n; k++)
				{
					if (multi[i][k] != cycle[j][k])
					{
						flagij = 0; break;
					}
				}
				if (flagij == 1)
				{
					flagi = 1; break;
				}
			}
			if (flagi == 0)
			{
				flag = 0; break;
			}
		}

		cout << number;
		if (flag == 1)
			cout << " is cyclic" << endl;
		else
			cout << " is not cyclic" << endl;
	}
	return 0;
}