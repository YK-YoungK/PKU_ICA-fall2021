/*
9. 基因串
题目描述
基因串是由一串有限长度的基因所组成的，其中每一个基因都可以用26个英文大写字母中的一个来表示，不同的字母表示不同的基因类型。一个单独的基因可以生长成为一对新的基因，而可能成长的规则是通过一个有限的成长规则集所决定的。每一个成长的规则可以用三个大写英文字母A1A2A3来描述，这个规则的意思是基因A1可以成长为一对基因A2A3。
用大写字母S来表示一类称作超级基因的基因，因为每一个基因串都是由一串超级基因根据给出的规则所成长出来的。
请写一个程序，读入有限条成长的规则和一些我们想要得到的基因串，然后对于每个基因串，判断它是否可以由一个有限长度的超级基因串成长得出。如果可以，给出可成长为该基因串的最短超级基因串的长度。

关于输入
第一行为正整数n(n<=50)表示规则的数目。
接下来n行，每行一个规则。
最后一行是目标基因串，长度不超过100。

关于输出
输出最短的超级基因串的长度，如果无法生成，请输出-1

例子输入
3
BCA
ABC
SAB
BCCA
例子输出
1
提示信息
S->AB->BCB->BCCA

此题和石子归并问题类似,可以用f[i][j][C]表示从i到j的子串能否由C推导得出,f[i][j][C]=0表示不能,f[i][j][C]=1表示能,则有:
f[i][j][C]=max{f[i][k][A]*f[k+1][j][B]}其中i<=kAB是一条规则.
这样可以计算出每一段能否由一个超级基因S推导得出.
再由一次类似的动态规划过程可以算出每个子串最少由几个S推导得出(比如用g[i][j]表示从i到j的子串至少由几个S推导得出),即得到原问题的解.
*/
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
char ch[150] = {};
int rules[60][3] = { 0 };
int check[110][110][30] = { 0 };//起点，终点，化为某个字母

int main()
{
	int dos = 0;
	cin >> dos;
	char a = 0, b = 0, c = 0;
	for (int i = 0; i < dos; i++)
	{
		cin >> a >> b >> c;
		rules[i][0] = a - 'A';
		rules[i][1] = b - 'A';
		rules[i][2] = c - 'A';
	}
	cin >> ch;
	int len = strlen(ch);

	//初始化
	for (int i = 0; i < len; i++)
	{
		check[i][i][ch[i] - 'A'] = 1;//记录该位置可以由谁生成
	}

	//从长度为2的字串开始递归，看是否能由某个字符生成
	for (int i = 1; i <= len; i++)
	{
		for (int j = 0; j < len - i; j++)//j到j+i
		{
			for (int l = 0; l < dos; l++)//遍历所有规则
			{
				for (int k = j; k <= j + i-1; k++)
				{
					if (check[j][k][rules[l][1]] == 1 && check[k + 1][j + i][rules[l][2]] == 1)
					{
						check[j][j + i][rules[l][0]] = 1;
						break;
					}
				}
			}
		}
	}

	//找最小的长度
	int best[100][100] = { 0 };//非1<<30代表已经生成
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			best[i][j] = 1 << 30;
		}
	}

	//在之前的每个结果里，找到可以由S生成的，标记为1
	for (int i = 0; i < len; i++)
	{
		for (int j = i; j < len; j++)
		{
			if (check[i][j]['S' - 'A'] == 1)
				best[i][j] = 1;
		}
	}

	for (int i = 0; i < len; i++)
	{
		for (int j = i; j < len; j++)
		{
			//遍历所有的规则
			for (int k = 0; k < dos; k++)
			{
				for (int l = i; l < j; l++)
				{
					if (best[i][l] != 1<<30 && best[l + 1][j] != 1<<30)
						best[i][j] = min(best[i][j], best[i][l] + best[l + 1][j]);
				}
			}
		}
	}

	if (best[0][len - 1] == 1<<30)
		cout << "-1" << endl;
	else
		cout << best[0][len - 1] << endl;
	return 0;
}