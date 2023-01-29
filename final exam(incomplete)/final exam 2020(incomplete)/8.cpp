/*
8. 计算字符串的相似度
题目描述
在计算机程序中，往往会大量使用字符串。对于不同的字符串，我们总希望能够有办法判断其相似度。因此，我们定义了一套操作方法来把两个不同的字符串变得相同。

具体可选的操作方法有：
1. 修改一个字符，例如将"a"修改为"b"；
2. 增加一个字符，例如将"abdd"变为"aebdd"
3. 删除一个字符，例如将"travelling"变为"traveling"

例如，对于两个字符串"abcdefg"和"abcdef"两个字符串来说，我们可以通过“将前一个字符串减少一个g”或者“给后一个字符串增加一个g”这两种方式来使得它们相同，这两种方案，都仅需要一次操作。

将修改字符串操作需要的最少的次数定义为两个字符串之间的距离，而相似度等于“距离+1”的倒数。例如，上例中"abcdefg"和"abcdef"的距离为1，则其相似度为1/2=0.5.

给定任意两个字符串(长度20以内)，写出一个程序来求出它们的相似度。

关于输入
第一行有一个整数n。表示测试数据的组数，
接下来共n行，每行两个字符串，用空格隔开。表示要计算距离的两个字符串
字符串长度不超过20。

关于输出
针对每一组测试数据输出两个字符串的相似度，保留小数点后6位。

例子输入
3
abcdefg  abcdef
ab ab
mnklj jlknm
例子输出
0.500000
1.000000
0.200000
提示信息
无
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;
int similar[30][30][30][30] = { 0 };//串1,x-y;串2,z-w
int main()
{
	int n = 0;
	cin >> n;
	while (n > 0)
	{
		char ch1[30] = {}, ch2[30] = {};
		cin >> ch1 >> ch2;
		int len1 = 0, len2 = 0;
		len1 = strlen(ch1);
		len2 = strlen(ch2);

		//初始值设定
		for (int x = 0; x < len1; x++)
		{
			for (int tmp2 = 0; tmp2 < len2; tmp2++)
			{
				for (int z = 0; z + tmp2 < len2; z++)
				{
					int flag = 0;
					for (int k = z; k <= z + tmp2; k++)
					{
						if (ch1[x] == ch2[k])
						{
							flag = 1; break;
						}
					}
					if (flag == 1)
						similar[x][x][z][z + tmp2] = tmp2;
					else
						similar[x][x][z][z + tmp2] = tmp2+1;
				}
			}
		}
		for (int z = 0; z < len2; z++)
		{
			for (int tmp1 = 0; tmp1 < len1; tmp1++)
			{
				for (int x = 0; x + tmp1 < len1; x++)
				{
					int flag = 0;
					for (int k = x; k <= x + tmp1; k++)
					{
						if (ch1[k] == ch2[z])
						{
							flag = 1; break;
						}
					}
					if (flag == 1)
						similar[x][x + tmp1][z][z] = tmp1;
					else
						similar[x][x + tmp1][z][z] = tmp1+1;
				}
			}
		}


		//开始按照串的长度动归
		for (int tmp1=1;tmp1<len1;tmp1++)
		{
			for (int x = 0; x + tmp1 < len1; x++)
			{
				for (int tmp2 = 1; tmp2 < len2; tmp2++)
				{
					for (int z = 0; z + tmp2 < len2; z++)
					{
						similar[x][x + tmp1][z][z + tmp2] = 1 << 30;
						for (int cut1 = x; cut1 < x + tmp1; cut1++)
						{
							for (int cut2 = z; cut2 < z + tmp2; cut2++)
							{
								similar[x][x + tmp1][z][z + tmp2] = min(similar[x][x + tmp1][z][z + tmp2],
									similar[x][cut1][z][cut2] + similar[cut1 + 1][x + tmp1][cut2 + 1][z + tmp2]);
							}
						}
					}
				}
			}
		}

		double result = 0;
		result = 1.0 / (similar[0][len1 - 1][0][len2 - 1] + 1);
		cout << fixed<< setprecision(6)<<result<< endl;

		n--;
	}
	return 0;
}