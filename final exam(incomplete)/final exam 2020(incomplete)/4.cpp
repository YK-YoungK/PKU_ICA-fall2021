/*
4. DNA排序
题目描述
作为医学生的你，一定对DNA不陌生。DNA可以看作是由字母'A''C''G''T'组成的字符串，现在有一些DNA序列需要你排序，排序的规则是按照DNA序列中逆序对的个数。逆序对的定义就是字符串中，在字母表中靠后的字母排在了字母表中靠前的字母的前面。举例来说，字符串"DAABEC"的逆序对数为5，分别是"D-A""D-A""D-B","D-C"和"E-C"，而"AACEDGG'' 就只有"C-E"这一个逆序对，"ABCDE"就没有逆序对。现在，给你一些DNA序列，请你将它们按照逆序对的个数从小到大排序。

关于输入
第一行是两个整数n和m，0<n<=50，表示字符串的长度，0<m<=100，表示字符串的个数。
接下来是m行，每一行是一个长度为n的字符串。

关于输出
m行，将m个字符串按照逆序对数从小到大的顺序输出。如果有逆序对数相等的字符串，按照它们在输入中的相对顺序输出。

例子输入
9 5
ACCGTTGAC
GGCTACGTA
ATTCGACGT
TGACTGACT
CCACGTACT
例子输出
CCACGTACT
ACCGTTGAC
ATTCGACGT
TGACTGACT
GGCTACGTA
提示信息
*/
// Submitted by 'Programming Grid' VS Code Extension

#include <iostream>
using namespace std;
struct doctor
{
	char xulie[10000] = {};
	int shunxu=0;
	int nixu=0;
}dna[1000],tmp;
int n = 0, m = 0;
int pairs(int row)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (dna[row].xulie[i] > dna[row].xulie[j])
				count++;
		}
	}
	return count;
}
int main()
{
	cin >> n >> m;
	cin.get();
	for (int i = 0; i < m; i++)
	{
		cin >>  dna[i].xulie;
	}
	
	for (int i = 0; i < m; i++)
	{
		dna[i].nixu= pairs(i);
		dna[i].shunxu = i;
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if (dna[i].nixu > dna[j].nixu)
			{
				tmp = dna[i];
				dna[i] = dna[j];
				dna[j] = tmp;
			}
			if (dna[i].nixu == dna[j].nixu&&dna[i].shunxu>dna[j].shunxu)
			{
				tmp = dna[i];
				dna[i] = dna[j];
				dna[j] = tmp;
			}
		}
	}

	for (int i = 0; i < m; i++)
	{
		cout << dna[i].xulie << endl;
	}
	return 0;
}