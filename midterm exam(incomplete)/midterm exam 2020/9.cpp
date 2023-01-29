/*
9. 破解密码
题目描述
考虑一种加密方式，它需要一个任意长度的原文 m 和秘钥 key，其中要求原文和秘钥只包含大写和小写的英文字符。

首先定义字符之间的加密，用字符 a 去加密字符 b 的结果是：
1. 首先把 a 和 b 转成数字 x 和 y。转换的规则是，小写字母 a 到 z 依次对应 0 到 25，大写字母依次对应 26 到 51。
2. 计算 x 和 y 的和 z，对 52 取模，即计算 (x + y) % 52。
3. 返回数字 z 对应的字符。

现在来讲如何用秘钥 key 来加密原文 m：
1. 如果秘钥的 key 的长度小于 m，那么不停重复 key 直到长度不小于 m 为止。举例来说，如果原文是 beijing，秘钥是 PKUSAA，那么秘钥需要被重复称 PKUSAAPKUSAA。
2. 假设原文的长度是 n，那么对于每一个 1~n 的数字 i，都用 key 的第 i 个字符去加密 m 的第 i 个字符。
3. 返回结果。

那么用 PKUSAA 去加密 beijing 的结果就是：QOcbINV

现在火山哥有 n 个字符串，s[1] 到 s[n]，他对这些字符串做了 m 次加密操作：第 i 次加密操作用第 s[x[i]] 去加密 s[y[i]]，并把 s[y[i]] 替换成加密结果。

现在依次给出 m 次加密操作，以及加密操作结束后每一个字符串的模样，你可以还原出这 n 个字符串原来的模样吗？

关于输入
第一行输入两个整数 n,m (1 <= n,m <= 1000)。

接下来 m 行每行输入两个整数 x[i],y[i]，表示依次加密操作，保证 x[i] 不等于 y[i]。

接下来 n 行每行输入一个字符串，表示加密最后的结果。字符串的长度在 1 到 100 之间，只包含大小写英文字符。

关于输出
输出 n 行，每行一个字符串，表示原本的字符串。

例子输入
2 1
1 2
PKUSAA
QOcbINV
例子输出
PKUSAA
beijing
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	char ch[1050][110] = {};
	int change[1050][2] = {};
	for (int i = 0; i < m; i++)
	{
		cin >> change[i][0] >> change[i][1];
	}
	cin.get();
	for (int i = 1; i <= n; i++)
	{
		cin.getline(ch[i], 105);
	}

	//破译
	for (int i = m-1; i >= 0; i--)
	{
		char miyao[330] = {};//存放写了好多次的密钥
		int lenth = 0;//密钥原长
		for (lenth = 0; ch[change[i][0]][lenth] != '\0'; lenth++);
		for (int j = 0; lenth * j < 220; j++)
		{
			for (int k = 0; k < lenth; k++)
			{
				miyao[j * lenth + k] = ch[change[i][0]][k];
			}
		}

		int nummiyao[330] = { 0 };//密钥转化为数字
		for (int j = 0; miyao[j] != '\0'; j++)
		{
			if (miyao[j] >= 'a' &&miyao[j] <= 'z')
				nummiyao[j] = miyao[j] - 'a';
			else
				nummiyao[j] = miyao[j] - 'A' + 26;
		}

		int numjiami[110] = { 0 };//被加密的转化为数字
		for (int j = 0; ch[change[i][1]][j] != '\0'; j++)
		{
			if (ch[change[i][1]][j] >= 'a' && ch[change[i][1]][j] <= 'z')
				numjiami[j] = ch[change[i][1]][j] - 'a';
			else
				numjiami[j] = ch[change[i][1]][j] - 'A'+26;
		}

		//逐位解密
		for (int j = 0; ch[change[i][1]][j] != '\0'; j++)
		{
			if (numjiami[j] >= nummiyao[j])
				numjiami[j] = numjiami[j] - nummiyao[j];
			else
				numjiami[j] = numjiami[j] - nummiyao[j] + 52;
		}

		//转化回去，并且储存回全局字符数组中
		for (int j = 0; ch[change[i][1]][j] != '\0'; j++)
		{
			if (numjiami[j]<=25)
				ch[change[i][1]][j]=numjiami[j]+'z'-25;
			else
				ch[change[i][1]][j] = numjiami[j] + 'Z' - 51;
		}
	}

	//输出
	for (int i = 1; i <= n; i++)
	{
		cout << ch[i] << endl;
	}
	return 0;
}
